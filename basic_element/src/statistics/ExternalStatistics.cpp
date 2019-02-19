/**
 * Project Gorynych
 * @version 0.1
 */

#define BOOST_LOG_DYN_LINK

#include <boost/log/trivial.hpp>
#include "../../include/statistics/ExternalStatistics.hpp"
#include "../../include/utils/Packet.hpp"

void ExternalStatistics::slotProcessReport(std::shared_ptr<IReport> report) {
    try {
        report_queue_->push(std::move(report));
    } catch (const StopPushException &stop_push_exception) {
        std::cerr << "attempt to push after stopping thread" << std::endl;
    }
}

void ExternalStatistics::connectAndStartSendingLoop() {
    connectToSocket();
    try {
        while (true) {
            sendOneReport();
        }
    } catch (const StopReceptionException &stop_reception_exception) {
        BOOST_LOG_TRIVIAL(trace) << "Exit ExternalStatistics::connectAndStartSendingLoop endless loop.";
    }
}

void ExternalStatistics::startSendingToSocketThread() {
    send_thread_ = std::thread(&ExternalStatistics::connectAndStartSendingLoop, this);
}

ExternalStatistics::ExternalStatistics(const std::string &socket_path, std::unique_ptr<ReportQueue> report_queue)
        : socket_path_(socket_path),
          report_queue_(std::move(report_queue)),
          endpoint_(socket_path_),
          socket_(ioservice_),
          stop_thread_flag(false) {

}

ExternalStatistics::~ExternalStatistics() {
    BOOST_LOG_TRIVIAL(debug) << "ExternalStatistics begin destructor";
    shutdown();
    BOOST_LOG_TRIVIAL(debug) << "ExternalStatistics end destructor";
}

void ExternalStatistics::sendOneReport() {
    auto report = report_queue_->wait_and_pop(); // Wait here
    std::string send_packet = Packet::buildPacket(report->serializeToString());
    try {
        socket_.send(boost::asio::buffer(send_packet));
    } catch (boost::system::system_error &e) {
        std::cerr << "Send error: " << e.what() << std::endl;
    }
}

void ExternalStatistics::connectToSocket() {
    try {
        socket_.connect(endpoint_);
    } catch (boost::system::system_error &e) {
        std::cerr << "Error connecting to " + socket_path_ + ": " << e.what() << std::endl;
    }
}


void ExternalStatistics::shutdown() {
    stop_thread_flag = true;
    report_queue_->shutdown();

    if (send_thread_.joinable()) {
        send_thread_.join();
    }
}
