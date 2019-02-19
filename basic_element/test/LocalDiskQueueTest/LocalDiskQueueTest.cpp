#include <thread>

#define BOOST_LOG_DYN_LINK

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#include "boost/bind.hpp"
#include "gtest/gtest.h"
#include "../meta/timeout.hpp"

#include "../../include/disk_performer/local_disk_queue/LocalDiskQueue.hpp"

const unsigned int threads_test_size = 30000;
// auxiliary functions/classes
std::shared_ptr<DataAtom> generateRandomDataAtom(unsigned long disk_offset, unsigned int disk_length);
std::shared_ptr<SolidData> generateRandomSolidData(unsigned int number_of_atoms);
std::shared_ptr<SolidDataChain> generateRandomSolidDataChain(const std::vector<unsigned> &solid_data_sizes);
class SignalSubscriber {
public:
    bool max_level_flag{false};
    bool min_level_flag{false};

    void raise_max_flag() {max_level_flag = true;}
    void raise_min_flag() {min_level_flag = true;}
    void lower_max_flag() {max_level_flag = false;}
    void lower_min_flag() {min_level_flag = false;}
};

//Test 1. Check thread safety of the method push, solid data sizes are checked indirectly in process

TEST(localDiskQueueTests, threadSafePush) {
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::warning);
    LocalDiskQueue localDiskQueue(std::make_shared<EntityStatisticsBuffer>(EntityStatisticsBuffer(threads_test_size)), 10, 100);
    std::vector<std::shared_ptr<SolidDataChain>> chains(threads_test_size);
    std::vector<unsigned int> atoms_location({5, 2, 4});
    for(unsigned i = 0; i < threads_test_size; i++) {
        chains[i] = generateRandomSolidDataChain(atoms_location); // each chain has 3 solid datas
    }
    std::vector<std::thread> test_threads(threads_test_size);
    int count = 0;
    for(auto &it: test_threads) {
        it = std::thread(&LocalDiskQueue::putSolidDataChainInQueue, &localDiskQueue, chains[count++]);
    }
    for(auto &it: test_threads) {
        it.join();
    }
    // if more elements are taken than put, infinite waiting shall happen
    TEST_TIMEOUT_BEGIN
    unsigned int number_of_solid_datas = threads_test_size * 3; // 3 is number of solid datas in each chain
    for(unsigned i = 0; i < number_of_solid_datas; i++) {
        std::shared_ptr<SolidData> sd = localDiskQueue.waitAndPopSolidData();
        EXPECT_TRUE(std::find(atoms_location.begin(), atoms_location.end(), sd->data_atoms.size()) != atoms_location.end());
    }
    TEST_TIMEOUT_FAIL_END(60000)
}

//Test 2. Check infinite waiting on wait and pop if no elements present
//        solid data sizes are checked indirectly in process

TEST(localDiskQueueTests, longWaitOnNoElements) {
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::warning);
    LocalDiskQueue localDiskQueue(std::make_shared<EntityStatisticsBuffer>(EntityStatisticsBuffer(threads_test_size)), 10, 100);
    std::vector<std::shared_ptr<SolidDataChain>> chains(threads_test_size);
    std::vector<unsigned int> atoms_location({2, 3, 4, 5});
    for(unsigned i = 0; i < threads_test_size; i++) {
        chains[i] = generateRandomSolidDataChain(atoms_location); // each chain has 4 solid datas
    }
    std::vector<std::thread> test_threads(threads_test_size);
    int count = 0;
    for(auto &it: test_threads) {
        it = std::thread(&LocalDiskQueue::putSolidDataChainInQueue, &localDiskQueue, chains[count++]);
    }
    for(auto &it: test_threads) {
        it.join();
    }
    // if more elements are taken than put, infinite waiting shall happen
    TEST_TIMEOUT_BEGIN
    // 4 is number of solid datas in each chain, + 1 to take more than it was put
    unsigned int number_of_solid_datas = threads_test_size * 4 + 1;
    for(unsigned i = 0; i < number_of_solid_datas; i++) {
        std::shared_ptr<SolidData> sd = localDiskQueue.waitAndPopSolidData();
        EXPECT_TRUE(std::find(atoms_location.begin(), atoms_location.end(), sd->data_atoms.size()) != atoms_location.end());
    }
    TEST_TIMEOUT_SUCCESS_END(60000)
}

//Test 3. Check min-max signals direct work

TEST(localDiskQueueTests, minMaxSignalsDirect) {
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::warning);
    for(unsigned j = 0; j < 10000; j++) {
        unsigned int min_size = 10;
        unsigned int max_size = 20;
        unsigned int test_size = max_size + 1;
        LocalDiskQueue localDiskQueue(std::make_shared<EntityStatisticsBuffer>(EntityStatisticsBuffer(test_size)),
                                      min_size, max_size);
        std::vector<std::shared_ptr<SolidDataChain>> chains(test_size);
        std::vector<unsigned int> atoms_location({1}); // one solid data per chain
        for(unsigned i = 0; i < test_size; i++) {
            chains[i] = generateRandomSolidDataChain(atoms_location);
        }
        SignalSubscriber signalSubscriber;
        signalSubscriber.min_level_flag = localDiskQueue.min_level_flag;
        signalSubscriber.max_level_flag = localDiskQueue.max_level_flag;
        EXPECT_TRUE(signalSubscriber.min_level_flag); // number of chains == 0
        EXPECT_FALSE(signalSubscriber.max_level_flag);
        localDiskQueue.sig_max_level_above.connect(boost::bind(&SignalSubscriber::raise_max_flag, &signalSubscriber));
        localDiskQueue.sig_max_level_below.connect(boost::bind(&SignalSubscriber::lower_max_flag, &signalSubscriber));
        localDiskQueue.sig_min_level_above.connect(boost::bind(&SignalSubscriber::lower_min_flag, &signalSubscriber));
        localDiskQueue.sig_min_level_below.connect(boost::bind(&SignalSubscriber::raise_min_flag, &signalSubscriber));
        std::vector<std::thread> test_threads(test_size);
        for(unsigned i = 0; i < min_size - 1; i++) {
            test_threads[i] = std::thread(&LocalDiskQueue::putSolidDataChainInQueue, &localDiskQueue, chains[i]);
        }
        for(unsigned i = 0; i < min_size - 1; i++) {
            test_threads[i].join();
        }
        EXPECT_TRUE(signalSubscriber.min_level_flag); // number of chains == min_size - 1
        EXPECT_FALSE(signalSubscriber.max_level_flag);
        test_threads[min_size - 1] = std::thread(&LocalDiskQueue::putSolidDataChainInQueue, &localDiskQueue,
                                                 chains[min_size]);
        test_threads[min_size - 1].join();
        EXPECT_FALSE(signalSubscriber.min_level_flag); // number of chains == min_size
        EXPECT_FALSE(signalSubscriber.max_level_flag);
        for(unsigned i = min_size; i < max_size; i++) {
            test_threads[i] = std::thread(&LocalDiskQueue::putSolidDataChainInQueue, &localDiskQueue, chains[i]);
        }
        for(unsigned i = min_size; i < max_size; i++) {
            test_threads[i].join();
        }
        EXPECT_FALSE(signalSubscriber.min_level_flag); // number of chains == max_size
        EXPECT_FALSE(signalSubscriber.max_level_flag);
        test_threads[max_size] = std::thread(&LocalDiskQueue::putSolidDataChainInQueue, &localDiskQueue,
                                             chains[min_size]);
        test_threads[max_size].join();
        EXPECT_FALSE(signalSubscriber.min_level_flag);
        EXPECT_TRUE(signalSubscriber.max_level_flag); // number of chains == max_size + 1
    }
}

//Test 4. Check min-max signals reverse work

TEST(localDiskQueueTests, minMaxSignalsReverse) {
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::warning);
    for(unsigned j = 0; j < 10000; j++) {
        unsigned int min_size = 10;
        unsigned int max_size = 20;
        unsigned int test_size = max_size + 1;
        LocalDiskQueue localDiskQueue(std::make_shared<EntityStatisticsBuffer>(EntityStatisticsBuffer(test_size)),
                                      min_size, max_size);
        std::vector<std::shared_ptr<SolidDataChain>> chains_direct(test_size);
        std::vector<unsigned int> atoms_location({1}); // one solid data per chain
        for(unsigned i = 0; i < test_size; i++) {
            chains_direct[i] = generateRandomSolidDataChain(atoms_location);
        }
        SignalSubscriber signalSubscriber;
        localDiskQueue.sig_max_level_above.connect(boost::bind(&SignalSubscriber::raise_max_flag, &signalSubscriber));
        localDiskQueue.sig_max_level_below.connect(boost::bind(&SignalSubscriber::lower_max_flag, &signalSubscriber));
        localDiskQueue.sig_min_level_above.connect(boost::bind(&SignalSubscriber::lower_min_flag, &signalSubscriber));
        localDiskQueue.sig_min_level_below.connect(boost::bind(&SignalSubscriber::raise_min_flag, &signalSubscriber));
        std::vector<std::thread> test_threads_direct(test_size);
        for(unsigned i = 0; i < test_size; i++) {
            test_threads_direct[i] = std::thread(&LocalDiskQueue::putSolidDataChainInQueue, &localDiskQueue,
                                                 chains_direct[i]);
        }
        for(unsigned i = 0; i < test_size; i++) {
            test_threads_direct[i].join();
        }
        EXPECT_FALSE(signalSubscriber.min_level_flag); // number of chains == max_size + 1
        EXPECT_TRUE(signalSubscriber.max_level_flag);
        std::vector<std::thread> test_threads_reverse(test_size);
        test_threads_reverse[max_size] = std::thread(&LocalDiskQueue::waitAndPopSolidData, &localDiskQueue);
        test_threads_reverse[max_size].join();
        EXPECT_FALSE(signalSubscriber.min_level_flag); // number of chains == max_size
        EXPECT_FALSE(signalSubscriber.max_level_flag);
        for(unsigned i = max_size - 1; i >= min_size; i--) {
            test_threads_reverse[i] = std::thread(&LocalDiskQueue::waitAndPopSolidData, &localDiskQueue);
        }
        for(unsigned i = max_size - 1; i >= min_size; i--) {
            test_threads_reverse[i].join();
        }
        EXPECT_FALSE(signalSubscriber.min_level_flag); // number of chains == min_size
        EXPECT_FALSE(signalSubscriber.max_level_flag);
        test_threads_reverse[min_size - 1] = std::thread(&LocalDiskQueue::waitAndPopSolidData, &localDiskQueue);
        test_threads_reverse[min_size - 1].join();
        EXPECT_TRUE(signalSubscriber.min_level_flag); // number of chains == min_size - 1
        EXPECT_FALSE(signalSubscriber.max_level_flag);
        for(unsigned i = min_size - 1; i != 0; i--) {
            test_threads_reverse[i] = std::thread(&LocalDiskQueue::waitAndPopSolidData, &localDiskQueue);
        }
        for(unsigned i = min_size - 1; i != 0; i--) {
            test_threads_reverse[i].join();
        }
        EXPECT_TRUE(signalSubscriber.min_level_flag); // number of chains == 0
        EXPECT_FALSE(signalSubscriber.max_level_flag);
    }
}

//Test 5. Check wait until ready to receive work on empty

TEST(localDiskQueueTests, waitUntilReadyToReceiveEmpty) {
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::warning);
    LocalDiskQueue localDiskQueue(std::make_shared<EntityStatisticsBuffer>(EntityStatisticsBuffer(10)), 10, 100);
    TEST_TIMEOUT_BEGIN
    localDiskQueue.waitUntilReadyToReceive(); // must be immediate: less than min_size (exactly 0) chains enqueued
    TEST_TIMEOUT_FAIL_END(1000)
}

//Test 6. Check wait until ready to receive work on full

TEST(localDiskQueueTests, waitUntilReadyToReceiveFull) {
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::warning);
    unsigned int test_size = 100;
    LocalDiskQueue localDiskQueue(std::make_shared<EntityStatisticsBuffer>(EntityStatisticsBuffer(test_size)), 10, test_size);
    std::vector<std::shared_ptr<SolidDataChain>> chains(test_size);
    std::vector<unsigned int> atoms_location({1});
    for(unsigned i = 0; i < test_size; i++) {
        chains[i] = generateRandomSolidDataChain(atoms_location);
    }
    std::vector<std::thread> test_threads(test_size);
    int count = 0;
    for(auto &it: test_threads) {
        it = std::thread(&LocalDiskQueue::putSolidDataChainInQueue, &localDiskQueue, chains[count++]);
    }
    for(auto &it: test_threads) {
        it.join();
    }
    std::thread thread([&](){
        sleep(5);
        localDiskQueue.waitAndPopSolidData();
    });
    TEST_TIMEOUT_BEGIN
    localDiskQueue.waitUntilReadyToReceive(); // must be right after thread awakes
    TEST_TIMEOUT_FAIL_END(10000)
    thread.join();
}

std::shared_ptr<DataAtom> generateRandomDataAtom(unsigned long disk_offset, unsigned int disk_length) {
    unsigned int raid_id = 42;
    unsigned int raid_disk_number = 14;
    PhysicalRegion physical_region(raid_id, raid_disk_number, disk_offset, disk_length);
    unsigned int magic_offset = 100;
    payload_data_vector data(disk_length + magic_offset * 2); // offset from both sides
    RawDataWrite temp(disk_length);
    temp.data = std::move(data);
    std::shared_ptr<RawDataWrite> raw_data_ptr = std::make_shared<RawDataWrite>(std::move(temp));
    return std::make_shared<DataAtom>(DataAtom(magic_offset, physical_region, raw_data_ptr));
}

std::shared_ptr<SolidData> generateRandomSolidData(unsigned int number_of_atoms) {
    std::vector<std::shared_ptr<DataAtom>> data_atoms(number_of_atoms);
    unsigned int basic_disk_offset = 20564875;
    unsigned int disk_length = 505;
    for(unsigned i = 0; i < number_of_atoms; i++) {
        // data atoms are allocated with no disk space in between
        data_atoms[i] = generateRandomDataAtom(basic_disk_offset + i * disk_length, disk_length);
    }
    return std::make_shared<SolidData>(SolidData(std::move(data_atoms)));
}

std::shared_ptr<SolidDataChain> generateRandomSolidDataChain(const std::vector<unsigned> &solid_data_sizes) {
    std::vector<std::shared_ptr<SolidData>> solid_datas(solid_data_sizes.size());
    for(unsigned i = 0; i < solid_data_sizes.size(); i++) {
        solid_datas[i] = generateRandomSolidData(solid_data_sizes[i]);
    }
    return std::make_shared<SolidDataChain>(SolidDataChain(std::move(solid_datas)));
}
