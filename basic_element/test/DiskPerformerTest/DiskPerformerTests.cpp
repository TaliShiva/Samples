#define BOOST_LOG_DYN_LINK

#include <gtest/gtest.h>
#include <thread>
#include <fstream>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#include "../../include/disk_performer/DiskPerformer.hpp"
#include "../../include/statistics/report/SensorsReport.hpp"


std::shared_ptr<SolidData>
getSolidData(unsigned long long offset, size_t length, unsigned char fill = '0', size_t data_atom_count = 1) {
    std::vector<std::shared_ptr<DataAtom>> data_atoms_vector;
    for (unsigned long i = 0; i < data_atom_count; i++) {
        unsigned int raid_id = 42;
        unsigned int raid_disk_number = 42;
        unsigned long long disk_offset = offset;
        size_t disk_length = length;
        PhysicalRegion physical_region(raid_id, raid_disk_number, disk_offset, disk_length);

        auto raw_data_write_ptr = std::make_shared<RawDataWrite>(payload_data_vector(length, fill));
        unsigned long long int raw_data_offset = 0;

        auto data_atom = std::make_shared<DataAtom>(raw_data_offset, physical_region, raw_data_write_ptr);
        data_atoms_vector.push_back(data_atom);
    }

    return std::make_shared<SolidData>(std::move(data_atoms_vector));
}

void createEmptyFile(const std::string &filename){
    std::ofstream createfile(filename);
    createfile << "" << std::endl;
    createfile.close();
}

/**
 * Check correct writing data to disk
 */
TEST(DiskPerformerIntegrationTests, correctWriteToDisk) {

    //Set log level
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::warning);

    for(auto k = 0; k <20; k++) {
        std::string file_path = "/tmp/tt-be7ohroTheiw3ong5hawz"+std::to_string(k)+"p";
        const unsigned sector_size = 512;
        const unsigned sector_count = 1;
        constexpr unsigned one_write_size = sector_size * sector_count;
        const unsigned char fill = 'M';
        const unsigned buffer_count = 4;
        constexpr unsigned summ_write_bytes = one_write_size * buffer_count;
        const unsigned solid_data_chain_count = 1000;

        std::remove(file_path.c_str());
        createEmptyFile(file_path);

        auto disk_port = std::unique_ptr<DiskPort>(new DiskPort(file_path));
        auto entityStatisticsBuffer = std::make_shared<EntityStatisticsBuffer>(10);
        auto mirror_buffer = std::unique_ptr<HWQueueMirrorBuffer>(new HWQueueMirrorBuffer());
        auto local_disk_queue = std::unique_ptr<LocalDiskQueue>(
                new LocalDiskQueue(std::move(entityStatisticsBuffer), 14, 18));

        auto disk_performer = new DiskPerformer(0, 16, std::move(local_disk_queue), std::move(mirror_buffer),
                                                std::unique_ptr<EntityStatisticsBuffer>(new EntityStatisticsBuffer(1)),
                                                std::move(disk_port));
        disk_performer->startReceiveResponseThread();
        disk_performer->startSendRequestThread();
        for (auto i = 0; i < solid_data_chain_count; i++) {
            auto next_solid_data_chain = std::make_shared<SolidDataChain>(std::vector<std::shared_ptr<SolidData>>{
                    getSolidData(i * summ_write_bytes, one_write_size, fill, buffer_count)});
            disk_performer->waitUntilReadyToReceive();
            BOOST_LOG_TRIVIAL(debug) << "send next iter: "<<k << " data: " <<i;
            disk_performer->pushSolidDataChain(next_solid_data_chain);
        }
        delete disk_performer;
        std::ifstream t(file_path);
        t.seekg(0, std::ios::end);
        long file_total_size = t.tellg();
        std::remove(file_path.c_str());

        EXPECT_EQ(file_total_size, summ_write_bytes * solid_data_chain_count);
    }
}

/**
 * Check that method DiskPerformer::calculateSensorsStatistics correct calculate statistics
 */
TEST(DiskPerformerTests, correctCalculateSensorsStatistics) {
    //Set log level
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
    const std::string file_path = "/tmp/tt-be7ohroTheiw3ong5hawd";

    std::remove(file_path.c_str());
    createEmptyFile(file_path);

    auto disk_port = std::unique_ptr<DiskPort>(new DiskPort(file_path));
    auto entityStatisticsBuffer = std::make_shared<EntityStatisticsBuffer>(10);
    auto mirror_buffer = std::unique_ptr<HWQueueMirrorBuffer>(new HWQueueMirrorBuffer());
    auto solid_buffer = new EntityStatisticsBuffer(1);
    solid_buffer->push({std::chrono::microseconds{100},100});
    solid_buffer->push({std::chrono::microseconds{52},10});
    solid_buffer->push({std::chrono::microseconds{10},11});

    auto local_disk_queue = std::unique_ptr<LocalDiskQueue>(new LocalDiskQueue(std::shared_ptr<EntityStatisticsBuffer>(solid_buffer), 4, 8));
    auto disk_performer = new DiskPerformer(0, 16, std::move(local_disk_queue), std::move(mirror_buffer),
                                            std::unique_ptr<EntityStatisticsBuffer>(solid_buffer),
                                             std::move(disk_port));
    auto i_report = disk_performer->calculateSensorsStatistics();
    auto sensor_report = dynamic_cast<SensorsReport*>(i_report.get());
    EXPECT_EQ(40, sensor_report->average_size_sd);
    EXPECT_EQ(54, sensor_report->average_latency_sd);
    EXPECT_EQ(40, sensor_report->average_size_sd_chain);
    EXPECT_EQ(54, sensor_report->average_latency_sd_chain);
}

/**
 * Check calling signal DiskPerformer::signal_on_sensor_report
 */
TEST(DiskPerformerTests, correctSignalSensorsReportCall) {
    //Set log level
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);

    const std::string file_path = "/tmp/tt-be7ohroTheiw3ong5hawd";
    const std::chrono::milliseconds statistic_interval = std::chrono::milliseconds(1000);

    std::atomic_uint signal_call_count;
        signal_call_count.store(0);
    const unsigned expected_call_count = 33; // Sleep seconds
    const unsigned sleep_microsecond = 1000 * 1000 * expected_call_count + 500;

    std::remove(file_path.c_str());
    createEmptyFile(file_path);
    auto disk_port = std::unique_ptr<DiskPort>(new DiskPort(file_path));
    auto entityStatisticsBuffer = std::make_shared<EntityStatisticsBuffer>(10);
    auto mirror_buffer = std::unique_ptr<HWQueueMirrorBuffer>(new HWQueueMirrorBuffer());
    auto local_disk_queue = std::unique_ptr<LocalDiskQueue>(
            new LocalDiskQueue(std::move(entityStatisticsBuffer), 4, 8));

    auto disk_performer = new DiskPerformer(0, 16,
                                            std::move(local_disk_queue),
                                            std::move(mirror_buffer),
                                            std::unique_ptr<EntityStatisticsBuffer>(new EntityStatisticsBuffer(1)),
                                            std::move(disk_port),
                                            statistic_interval);
    disk_performer->signal_on_sensor_report.connect([&signal_call_count](std::shared_ptr<IReport> const& report) {
        signal_call_count++;
    });
    disk_performer->startSensorsProcessingThread();
    usleep(sleep_microsecond);
    EXPECT_EQ(expected_call_count, signal_call_count);
    delete disk_performer;
    std::remove(file_path.c_str());

}

