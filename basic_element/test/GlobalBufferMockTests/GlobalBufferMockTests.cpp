#include <gtest/gtest.h>
#include <boost/signals2.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/crc.hpp>
#include <thread>
#include <fstream>
#include <random>

#include "../../include/statistics/report/IReport.hpp"
#include "../../include/disk_performer/local_disk_queue/LocalDiskQueue.hpp"
#include "../../include/disk_performer/hw_queue_mirror/HWQueueMirrorBuffer.hpp"
#include "../../include/load/LoadProfile.hpp"
#include "../../include/load/LoadParameters.hpp"
#include "../meta/timeout.hpp"
#include "../../include/disk_performer/statistics/EntityStatisticsBuffer.hpp"
#include "../../include/disk_performer/DiskPort.hpp"


/**
 * mock of DiskPerformer
 */
namespace  {

    #include "../../include/disk_performer/DiskPerformer.hpp"



    static int waitUntilReadyToReceive_call_counter = 0;
    static int pushSolidDataChain_call_counter = 0;

    DiskPerformer::DiskPerformer(unsigned int atomic_hw_count, unsigned int hw_queue_max,
                                 std::unique_ptr<LocalDiskQueue> local_disk_queue,
                                 std::unique_ptr<HWQueueMirrorBuffer> hw_queue_mirror_buffer,
                                 std::unique_ptr<EntityStatisticsBuffer> statistics_buffer_solid_data,
                                 std::unique_ptr<DiskPort> disk_port,
                                 std::chrono::milliseconds statistic_interval)
            :
            statistics_buffer_solid_data_(std::move(statistics_buffer_solid_data)) {
        this->atomic_hw_count_ = atomic_hw_count;
        this->hw_queue_max_ = hw_queue_max;
        this->local_disk_queue_ = std::move(local_disk_queue);
        this->hw_queue_mirror_buffer_ = std::move(hw_queue_mirror_buffer);
    }
    DiskPerformer::~DiskPerformer() {}

    void DiskPerformer::sendRequestToKernelThread() {}
    void DiskPerformer::receiveAnswerFromKernelThread() {}
    void DiskPerformer::sensorsProcessingThread() {}
    void DiskPerformer::waitUntilReadyToReceive() {waitUntilReadyToReceive_call_counter++;}
    void DiskPerformer::pushSolidDataChain(std::shared_ptr<SolidDataChain> solidDataChain) {
        pushSolidDataChain_call_counter++;
    }




#include "../../src/global_buffer/GlobalBufferMock.cpp"

}

/**
 * Test verifies that reinitialization with exposed is_global_buffer_mock_init flag is not allowed.
 * Reinitialization with discarded is_global_buffer_mock_init is allowed
 */
TEST(loadParametersTests, correctExceptionHandling) {


    unsigned int atomic_hw_count = 1;
    unsigned int hw_queue_max = 1;

    auto disk_performer = std::make_shared<DiskPerformer>(atomic_hw_count, hw_queue_max,
                                                          nullptr,
                                                          nullptr,
                                                          nullptr,
                                                          nullptr);

    GlobalBufferMock global_buffer_mock(disk_performer);

    boost::property_tree::ptree json_tree;
    boost::property_tree::read_json("../test/GlobalBufferMockTests/ConfigFiles/good_config1.json",
                                    json_tree);
    LoadParameters load_parameters(json_tree);

    //initialization by correct load profile
    EXPECT_NO_THROW(global_buffer_mock.initTestData(load_parameters));

    //reinitialization without flag
    EXPECT_THROW(global_buffer_mock.initTestData(load_parameters), std::logic_error);
}



TEST(improvedGlobalBufferMock, correctNumberOfFunctionsCalls) {
    unsigned int atomic_hw_count = 1;
    unsigned int hw_queue_max = 1;
    auto disk_performer = std::make_shared<DiskPerformer>(atomic_hw_count,
                                                          hw_queue_max,
                                                          nullptr,
                                                          nullptr,
                                                          nullptr,
                                                          nullptr);

    GlobalBufferMock global_buffer_mock(disk_performer);

    boost::property_tree::ptree json_tree;
    boost::property_tree::read_json("../test/GlobalBufferMockTests/ConfigFiles/good_config2.json",
                                    json_tree);
    LoadParameters load_parameters(json_tree);

    global_buffer_mock.initTestData(load_parameters);

    unsigned long counter_of_functions_call = 0;

    for (auto &it: load_parameters.vector_of_load_templates) {
        counter_of_functions_call += it.first * it.second.size();
    }

    global_buffer_mock.waitAndPushInDiskPerformerQueue();

    EXPECT_EQ(counter_of_functions_call, waitUntilReadyToReceive_call_counter);
    EXPECT_EQ(counter_of_functions_call, pushSolidDataChain_call_counter);

}

//Test 4. Correct working time of waitAndPushInDiskPerformerQueue considering pauses

TEST(improvedGlobalBufferMock, correctWorkingTimeOf_waitAndPushInDiskPerformerQueue) {
    unsigned int atomic_hw_count = 1;
    unsigned int hw_queue_max = 1;
    auto disk_performer = std::make_shared<DiskPerformer>(atomic_hw_count,
                                                          hw_queue_max,
                                                          nullptr,
                                                          nullptr,
                                                          nullptr,
                                                          nullptr);

    GlobalBufferMock global_buffer_mock(disk_performer);

    boost::property_tree::ptree json_tree;
    boost::property_tree::read_json("../test/GlobalBufferMockTests/ConfigFiles/good_config1.json",
                                    json_tree);
    LoadParameters load_parameters(json_tree);


    global_buffer_mock.initTestData(load_parameters);

    std::chrono::milliseconds min_work_time{0};

    for (auto &load: load_parameters.vector_of_load_templates) {
        for (auto &temp: load.second) {
            min_work_time += load.first * temp.length_of_pause;
        }
    }

    TEST_TIMEOUT_BEGIN
    global_buffer_mock.waitAndPushInDiskPerformerQueue();
    TEST_TIMEOUT_SUCCESS_END(min_work_time)
}


