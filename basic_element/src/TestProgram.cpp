/**
 * Project Gorynych
 * @version 0.1
 */


#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include "../include/TestProgram.hpp"
#include "../include/statistics/report/StartReport.hpp"
#include "../include/statistics/report/StopReport.hpp"

using json_parser_error =
boost::exception_detail::clone_impl<boost::exception_detail::
error_info_injector<boost::property_tree::json_parser::json_parser_error>>;

TestProgram::TestProgram(std::string path_to_device,
                         std::string path_to_socket,
                         std::string path_to_config,
                         unsigned hw_queue_depth,
                         unsigned min_level_size,
                         unsigned max_level_size,
                         std::chrono::milliseconds work_time): path_to_device_(path_to_device),
                                                               path_to_socket_(path_to_socket),
                                                               path_to_config_(path_to_config),
                                                               hw_queue_depth_(hw_queue_depth),
                                                               min_level_size_(min_level_size),
                                                               max_level_size_(max_level_size),
                                                               work_time_(work_time) {

}


void TestProgram::run() {


    ExternalStatistics external_statistics(path_to_socket_);

    external_statistics.startSendingToSocketThread();

    std::unique_ptr<EntityStatisticsBuffer>
            statistics_buffer_solid_data(new EntityStatisticsBuffer(0));
    auto solid_data_chain_statistics_buffer = std::make_shared<EntityStatisticsBuffer>(0);
    std::unique_ptr<LocalDiskQueue> local_disk_queue(new LocalDiskQueue(std::move(solid_data_chain_statistics_buffer),
                                                                        min_level_size_,
                                                                        max_level_size_));
    std::unique_ptr<HWQueueMirrorBuffer> hw_queue_mirror_buffer(new HWQueueMirrorBuffer);

    std::unique_ptr<DiskPort> disk_port(new DiskPort(path_to_device_));

    auto disk_performer = std::make_shared<DiskPerformer>(0,
                                                          hw_queue_depth_,
                                                          std::move(local_disk_queue),
                                                          std::move(hw_queue_mirror_buffer),
                                                          std::move(statistics_buffer_solid_data),
                                                          std::move(disk_port));

    disk_performer->startSensorsProcessingThread();
    disk_performer->startReceiveResponseThread();
    disk_performer->startSendRequestThread();

    GlobalBufferMock global_buffer_mock(disk_performer);

    start_signal.connect(boost::bind(&ExternalStatistics::slotProcessReport, &external_statistics, _1));
    stop_signal.connect(boost::bind(&ExternalStatistics::slotProcessReport, &external_statistics, _1));
    disk_performer->signal_on_sensor_report.connect(
            boost::bind(&ExternalStatistics::slotProcessReport, &external_statistics, _1));

    boost::property_tree::ptree json_tree;
    try {
        boost::property_tree::read_json(path_to_config_,
                                        json_tree);

    } catch (const json_parser_error &e) {
        std::cerr << "config file not found" << std::endl;
        abort();
    }

    LoadParameters load_parameters(json_tree);
    global_buffer_mock.initTestData(load_parameters);

    checksum_ = global_buffer_mock.getCheckSum();

    start_signal(std::make_shared<StartReport>(std::chrono::system_clock::now()));

    global_buffer_mock.startPushInDiskPerformerQueue();

    std::this_thread::sleep_for(work_time_);

    stop_signal(std::make_shared<StopReport>(std::chrono::system_clock::now()));
}

boost::crc_32_type::value_type TestProgram::getCheckSum() {
    return checksum_;
}