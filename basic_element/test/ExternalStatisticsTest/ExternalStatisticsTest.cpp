#include "gtest/gtest.h"

#include "../meta/timeout.hpp"
#include "../../include/utils/Packet.hpp"
#include "../../include/statistics/ExternalStatistics.hpp"
#include "../../include/statistics/report/SensorsReport.hpp"
#include "../../include/statistics/report/StartReport.hpp"
#include "../../include/statistics/report/StopReport.hpp"


/**
 * @brief Listening UNIX-socket and receive only one Packet desribed in Packet class
 * @see Packet
 * @param socket_path path to UNIX-socket
 * @param callback function to handling packet data
 */
void ServerReceiveOnePacket(std::string socket_path, std::function<void(std::string packet)> callback) {
    using namespace boost::asio;
    io_service service_;
    std::remove(socket_path.c_str());
    local::stream_protocol::acceptor acceptor(service_, local::stream_protocol::endpoint(socket_path));
    char buff[Packet::MAX_PACKET_SIZE];
    local::stream_protocol::socket sock(service_);
    acceptor.accept(sock);
    size_t bytes = read(sock, buffer(buff), boost::bind(Packet::packet_read_complete, buff, _1, _2));
    std::string request(buff, bytes);
    std::string request_data = Packet::parsePacket(request);
    callback(request_data);
    sock.close();
    std::remove(socket_path.c_str());
}

/**
 * Check SensorsReport correct convert to protouf-coded string
 */
TEST(SensorsReportTest, correctConvertToProtobuf) {
    SensorsReport report(1, 1, 4096, 4096, 100, 100, std::chrono::system_clock::now());
    EXPECT_NE(report.serializeToString(), "");
}

/**
 * Check StartReport correct convert to protouf-coded string
 */
TEST(StartReportTest, correctConvertToProtobuf) {
    StartReport report(std::chrono::system_clock::now());
    EXPECT_NE(report.serializeToString(), "");
}

/**
 * Check StopReport correct convert to protouf-coded string
 */
TEST(StopReportTest, correctConvertToProtobuf) {
    StopReport report(std::chrono::system_clock::now());
    EXPECT_NE(report.serializeToString(), "");
}

/**
 * Check Push work correct in concurrent threads
 */
TEST(ReportQueueTest, correctPush) {
    const unsigned test_size = 30000;
    ReportQueue test_queue;
    std::vector<std::thread> test_threads(test_size);
    for (auto &it : test_threads) {
        it = std::thread([&test_queue]() {
            test_queue.push(
                    std::make_shared<SensorsReport>(1, 1, 4096, 4096, 100, 100, std::chrono::system_clock::now()));
        });
    }
    for (auto &it : test_threads) {
        it.join();
    }

    EXPECT_EQ(test_size, test_queue.size());
}

/**
 * Check Pop work correct in concurrent threads
 */
TEST(ReportQueueTest, correctPop) {
    const unsigned test_size = 30000;
    ReportQueue test_queue;
    for (unsigned i = 0; i < test_size; i++) {
        test_queue.push(std::make_shared<SensorsReport>(1, 1, 4096, 4096, 100, 100, std::chrono::system_clock::now()));
    }
    std::vector<std::thread> test_threads(test_size);
    for (auto &it : test_threads) {
        it = std::thread([&test_queue]() { test_queue.wait_and_pop(); });
    }
    for (auto &it : test_threads) {
        it.join();
    }

    EXPECT_EQ(0, test_queue.size());
}

/**
 * Check that slotProcessReport add IReport to internal buffer in ExternalStatistics
 */
TEST(ExternalStatisticsTest, correctWaitOnEmptyInternalQueue) {
    TEST_TIMEOUT_BEGIN
    const std::string socket_path = "/tmp/test-file-not-needed";
    ExternalStatistics stat(socket_path);
    stat.sendOneReport();
    TEST_TIMEOUT_SUCCESS_END(10000)
}


/**
 * Check that slotProcessReport add IReport to internal buffer in ExternalStatistics
 */
TEST(ExternalStatisticsTest, correctSlotProcessReport) {
    const std::string socket_path = "/tmp/test-file-not-needed";

    ExternalStatistics stat(socket_path);
    auto orig_report = new SensorsReport(1, 1, 4096, 4096, 100, 100, std::chrono::system_clock::now());
    std::unique_ptr<SensorsReport> report(orig_report);

    ASSERT_NO_THROW(stat.slotProcessReport(std::move(report)));
    EXPECT_EQ(1, stat.report_queue_->size());
}

/**
 * Checking that ExternalStatistics correct sent protobuf-coded message throw socket
 */
TEST(ExternalStatisticsIntegrationTest, correctSendProtobufThrowSocket) {
    const std::string socket_path = "/tmp/test-sock-Mem5jaofegingoyaitei";
    auto client = [socket_path]() {
        ExternalStatistics ext(socket_path);
        ext.startSendingToSocketThread();
        ext.slotProcessReport(std::unique_ptr<SensorsReport>(
                new SensorsReport(1, 1, 4096, 4096, 100, 100, std::chrono::system_clock::now())));

    };
    bool result = false;
    auto server = [socket_path, &result]() {
        using namespace boost::asio;
        io_service service_;
        std::remove(socket_path.c_str());
        local::stream_protocol::acceptor acceptor(service_, local::stream_protocol::endpoint(socket_path));
        char buff[Packet::MAX_PACKET_SIZE];
        local::stream_protocol::socket sock(service_);
        acceptor.accept(sock);
        size_t bytes = read(sock, buffer(buff), boost::bind(Packet::packet_read_complete, buff, _1, _2));
        std::string request(buff, bytes);
        std::string request_data = Packet::parsePacket(request);
        gorynych::protobuf::Report protobuf_report;
        result = protobuf_report.ParseFromString(request_data);
        sock.close();
        std::remove(socket_path.c_str());
    };

    std::thread server_thread = std::thread(server);
    usleep(100000);
    std::thread client_thread = std::thread(client);
    server_thread.join();
    client_thread.detach();
    EXPECT_TRUE(result);

}

/**
 * Checking that ExternalStatistics correct sent SensorReport throw socket
 */
TEST(ExternalStatisticsIntegrationTest, correctSendSensorReportThrowSocket) {
    const std::string socket_path = "/tmp/test-sock-ieph5iesaiHiubongoov";
    SensorsReport sensor_report = SensorsReport(1, 1, 4096, 4096, 100, 100, std::chrono::system_clock::now());
    auto client = [socket_path, sensor_report]() {
        ExternalStatistics ext(socket_path);
        ext.startSendingToSocketThread();
        ext.slotProcessReport(std::unique_ptr<SensorsReport>(new SensorsReport(sensor_report)));
    };
    gorynych::protobuf::Report protobuf_report;
    auto check_packet = [&protobuf_report](std::string packet_data) {
        protobuf_report.ParseFromString(packet_data);
    };
    std::thread server_thread = std::thread(ServerReceiveOnePacket, socket_path, check_packet );
    usleep(100000);
    std::thread client_thread = std::thread(client);
    server_thread.join();
    client_thread.detach();
    EXPECT_EQ(protobuf_report.type(), gorynych::protobuf::Report::REPORT_STATISTICS);
    EXPECT_EQ(protobuf_report.report_statistics().average_size_sd(), sensor_report.average_size_sd);
    EXPECT_EQ(protobuf_report.report_statistics().average_size_sd_chain(),sensor_report.average_size_sd_chain);
    EXPECT_EQ(protobuf_report.report_statistics().average_latency_sd(), sensor_report.average_latency_sd);
    EXPECT_EQ(protobuf_report.report_statistics().average_latency_sd_chain(), sensor_report.average_latency_sd_chain);
    EXPECT_EQ(protobuf_report.report_statistics().sd_count(), sensor_report.sd_count);
    EXPECT_EQ(protobuf_report.report_statistics().sd_chain_count(), sensor_report.sd_chain_count);
    EXPECT_EQ(protobuf_report.report_statistics().timestamp(), std::chrono::time_point_cast<std::chrono::microseconds>(sensor_report.timestamp).time_since_epoch().count());
}

/**
 * Checking that ExternalStatistics correct sent StartReport throw socket
 */
TEST(ExternalStatisticsIntegrationTest, correctSendStartReportThrowSocket) {
    const std::string socket_path = "/tmp/test-sock-ieph5iesaiHiubongoov";
    StartReport start_report = StartReport(std::chrono::system_clock::now());
    auto client = [socket_path, start_report]() {
        ExternalStatistics ext(socket_path);
        ext.startSendingToSocketThread();
        ext.slotProcessReport(std::unique_ptr<StartReport>(new StartReport(start_report)));
    };
    gorynych::protobuf::Report protobuf_report;
    auto check_packet = [&protobuf_report](std::string packet_data) {
        protobuf_report.ParseFromString(packet_data);
    };
    std::thread server_thread = std::thread(ServerReceiveOnePacket, socket_path, check_packet );
    usleep(100000);
    std::thread client_thread = std::thread(client);
    server_thread.join();
    client_thread.detach();
    EXPECT_EQ(protobuf_report.type(), gorynych::protobuf::Report::REPORT_START);
    EXPECT_EQ(protobuf_report.report_start().start_time(), std::chrono::time_point_cast<std::chrono::microseconds>(start_report.start_time).time_since_epoch().count());

}

/**
 * Checking that ExternalStatistics correct sent StopReport throw socket
 */
TEST(ExternalStatisticsIntegrationTest, correctSendStopReportThrowSocket) {
    const std::string socket_path = "/tmp/test-sock-ieph5iesaiHiubongoov";
    StopReport stop_report = StopReport(std::chrono::system_clock::now());
    auto client = [socket_path, stop_report]() {
        ExternalStatistics ext(socket_path);
        ext.startSendingToSocketThread();
        ext.slotProcessReport(std::unique_ptr<StopReport>(new StopReport(stop_report)));
    };
    gorynych::protobuf::Report protobuf_report;
    auto check_packet = [&protobuf_report](std::string packet_data) {
        protobuf_report.ParseFromString(packet_data);
    };
    std::thread server_thread = std::thread(ServerReceiveOnePacket, socket_path, check_packet);
    usleep(100000);
    std::thread client_thread = std::thread(client);
    server_thread.join();
    client_thread.detach();
    EXPECT_EQ(protobuf_report.type(), gorynych::protobuf::Report::REPORT_STOP);
    EXPECT_EQ(protobuf_report.report_stop().stop_time(), std::chrono::time_point_cast<std::chrono::microseconds>(stop_report.stop_time).time_since_epoch().count());
}


/**
 * Test verifies that it can not be pushed if the reception of requests is stopped
 */
TEST(KillableThreadOfReportQueueTests, correctHandlingOfPushWithStoppedReception) {

    ReportQueue report_queue;
    report_queue.push(std::make_shared<StartReport>(std::chrono::system_clock::now()));
    report_queue.shutdown();

    EXPECT_THROW(report_queue.push(nullptr), StopPushException);
}


/**
 * Test verifies that locked conditional_variable can be unlocked by shutdown method
 */
TEST(KillableThreadOfReportQueueTests, correctHandlingOfWaitAndPophWithStoppedReception) {

    ReportQueue report_queue;

    unsigned long long size = 5000000;
    for (unsigned long long i = 0; i < size; i++) {

        report_queue.push(std::make_shared<StartReport>(std::chrono::system_clock::now()));
    }
    while (!report_queue.empty()) {

        report_queue.wait_and_pop();
    }

    report_queue.shutdown();

    EXPECT_THROW(report_queue.wait_and_pop(), StopReceptionException);
}


/**
 * Test verifies that you can kill blocked thread using method stopThread
 */
TEST(KillableThreadOfExternalStatisticsTests, CorrectThreadStop) {

    std::unique_ptr<ReportQueue> report_queue(new ReportQueue);

    std::string socket_path = "/tmp/test-file=no-need";
    ExternalStatistics external_statistics(socket_path, std::move(report_queue));

    external_statistics.startSendingToSocketThread();

    std::this_thread::sleep_for(std::chrono::milliseconds(10000));

    EXPECT_TRUE(external_statistics.send_thread_.joinable());

    external_statistics.shutdown();

    EXPECT_FALSE(external_statistics.send_thread_.joinable());

}

/**
 * Test checks that after stop rest of the queue is correctly processed
 */
TEST(KillableThreadOfExternalStatisticsTests, correctProcessingOfQueueAfterStop) {

    std::unique_ptr<ReportQueue> report_queue(new ReportQueue);
    unsigned long size = 500000;
    for (unsigned long i = 0; i < size; i++) {

        report_queue->push(std::make_shared<StartReport>(std::chrono::system_clock::now()));
    }

    std::string socket_path = "/tmp/test-file=no-need";
    ExternalStatistics external_statistics(socket_path, std::move(report_queue));

    external_statistics.startSendingToSocketThread();
    external_statistics.shutdown();

    EXPECT_EQ(external_statistics.report_queue_->size(), 0);
}


/**
 * A simple test verifying that with the stop flag the inner loop ceases to be infinite
 */
TEST(KillableThreadOfExternalStatisticsTests, SimpleStopThread) {

    std::unique_ptr<ReportQueue> report_queue(new ReportQueue);
    report_queue->push(std::make_shared<StartReport>(std::chrono::system_clock::now()));


    std::string socket_path = "/tmp/test-file=no-need";
    ExternalStatistics external_statistics(socket_path, std::move(report_queue));
    external_statistics.shutdown();
    TEST_TIMEOUT_BEGIN
                external_statistics.connectAndStartSendingLoop();
    TEST_TIMEOUT_FAIL_END(10)
}

