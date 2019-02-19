#include <thread>
#include <gtest/gtest.h>

#include "../../include/disk_performer/statistics/EntityStatisticsBuffer.hpp"



//Test 1. Check thread safety of the method push

/**
 * Test verifies that all threads are correctly written in EntityStatisticsBuffer object.
 * It is checked that all the elements are written, i.e. size of EntityStatisticsBuffer equal to number of pushing
 * EntityStatistics objects.
 */
TEST(entityStatisticsBufferTests, correctPushSize) {
    const unsigned long test_size = 30000;
    EntityStatisticsBuffer test_buffer(test_size);
    std::vector<std::thread> test_threads(test_size);
    for (auto & it : test_threads) {
        std::chrono::microseconds time{0};
        size_t size = 0;
        EntityStatistics entity_statistics_element(time, size);
        it = std::thread(&EntityStatisticsBuffer::push, &test_buffer, entity_statistics_element);
    }

    for (auto & it : test_threads) {
        it.join();
    }
    EXPECT_EQ(test_size, test_buffer.getCopyAndClear().size());
}


//Test 2. Check thread safety of the method getCopyAndClear

/**
 * @brief Thread's function that push EntityStatistics object into EntityStatisticsBuffer object
 * @param buffer - EntityStatisticsBuffer object
 * @param size - The total length of all EntityStatisticsBuffer vectors that are displaced by the method getCopyAndClear
 * Function use method getCopyAndClear of EntityStatisticsBuffer object. The length of the displaced vector is added
 * to the variable size.
 */


void getCopyAndClear(EntityStatisticsBuffer & buffer, unsigned long & size) {
    std::vector<EntityStatistics> v = buffer.getCopyAndClear();
    size += v.size();
}


/**
 * Test verifies that all threads correct use getCopyAndClear method.
 * It is verified that the length of all displaced vectors is equal to the size of the initially filled
 * EntityStatisticsBuffer object.
 */
TEST(entityStatisticsBufferTests, correctGetCopyAndClearSize) {
    const unsigned long test_size = 30000;
    EntityStatisticsBuffer test_buffer(test_size);
    for (unsigned long i = 0; i < test_size; i++) {
        std::chrono::microseconds time{0};
        size_t size = 0;
        EntityStatistics entity_statistics_element(time, size);
        test_buffer.push(entity_statistics_element);
    }
    unsigned long total_size = 0;
    std::vector<std::thread> test_threads(test_size);
    for (auto & it : test_threads) {
        it = std::thread(getCopyAndClear, std::ref(test_buffer), std::ref(total_size));
    }
    for (auto & it : test_threads) {
        it.join();
    }

    EXPECT_EQ(test_size, total_size);
}

//Test 3

/**
 * Test verifies that with empty statistics, an empty vector is returned
 */
TEST(entityStatisticsBufferTests, correctGetCopyAndClearWithEmptyVector)
{
    const unsigned long test_size = 100000;
    EntityStatisticsBuffer test_buffer(test_size);
    EXPECT_EQ(0, test_buffer.getCopyAndClear().size());
}

