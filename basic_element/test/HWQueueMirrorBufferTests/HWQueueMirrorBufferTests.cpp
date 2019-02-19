#include <gtest/gtest.h>
#include <thread>

#include "../../include/disk_performer/hw_queue_mirror/HWQueueMirrorBuffer.hpp"

/**
 * Hardcode of HWQueueElement object
 * @param j - callbackID of generated object
 * @return HWQueueElement object
 */
HWQueueMirrorElement create_hw_queue_mirror_element(unsigned long j) {
    std::vector<std::shared_ptr<DataAtom>> data_atoms_vector;
    for (unsigned long i = 0; i < 10; i++) {
        unsigned int raid_id = 5;
        unsigned int raid_disk_number = 7;
        unsigned  long long disk_offset = 4;
        size_t disk_length = 10;
        PhysicalRegion physical_region(raid_id, raid_disk_number, disk_offset, disk_length);

        auto raw_data_write_ptr = std::make_shared<RawDataWrite>(16);
        unsigned long long int raw_data_offset = 8;

        auto data_atom = std::make_shared<DataAtom>(raw_data_offset, physical_region, raw_data_write_ptr);
        data_atoms_vector.push_back(data_atom);
    }

    auto solid_data_ptr = std::make_shared<SolidData>(std::move(data_atoms_vector));

    std::chrono::system_clock::time_point start_time = std::chrono::system_clock::now();
    callback_id_type callback_id = j;

    return HWQueueMirrorElement(start_time, solid_data_ptr, callback_id);
}


/**
 * Test verifies that many threads correctly fill HWQueueMirrorBuffer object
 */
TEST(HWQueueMirrorBufferTests, correctPutSolidDataAndCallbackID) {
    const unsigned long size = 30000;
    HWQueueMirrorBuffer hw_queue_mirror_buffer;

    std::vector<std::thread> test_threads(size);
    for (unsigned long i = 0; i < size; i++) {
        test_threads[i] = std::thread(&HWQueueMirrorBuffer::putSolidDataAndCallbackID, &hw_queue_mirror_buffer,
                                      create_hw_queue_mirror_element(i));
    }


    std::for_each(test_threads.begin(), test_threads.end(), [] (std::thread & t) {t.join();});

    EXPECT_EQ(size, hw_queue_mirror_buffer.size());
}


/**
 * Test verifies that you can not get an item twice with one key
 */
TEST(HWQueueMirrorBufferTests, correctPutSolidDataAndCallbackIDWithSameID) {
    HWQueueMirrorBuffer hw_queue_mirror_buffer;

    HWQueueMirrorElement hw_queue_mirror_element = create_hw_queue_mirror_element(1);

    hw_queue_mirror_buffer.putSolidDataAndCallbackID(std::move(hw_queue_mirror_element));

    hw_queue_mirror_element = create_hw_queue_mirror_element(1);

    ASSERT_THROW(hw_queue_mirror_buffer.putSolidDataAndCallbackID(std::move(hw_queue_mirror_element)),
                 std::logic_error);
}


/**
 * Test verifies that multiple threads correctly receive elements from HWQueueMirrorBuffer object
 */
TEST(HWQueueMirrorBufferTests, correctFindAndPopByCallbackID) {
    const unsigned long size = 30000;
    HWQueueMirrorBuffer hw_queue_mirror_buffer;

    for (unsigned long i = 0; i < size; i++) {
        HWQueueMirrorElement element = create_hw_queue_mirror_element(i);
        hw_queue_mirror_buffer.putSolidDataAndCallbackID(std::move(element));
    }

    std::vector<std::thread> threads_vector(size);

    for (unsigned long i = 0; i < size; i++) {
        threads_vector[i] = std::thread(&HWQueueMirrorBuffer::findAndPopByCallbackID, &hw_queue_mirror_buffer, i);
    }

    for (auto & it : threads_vector) {
        it.join();
    }

    EXPECT_EQ(0, hw_queue_mirror_buffer.size());
}

/**
 * Test verifies that you can not get twice the element from HWQueueMirrorBuffer object
 */
TEST(HWQueueMirrorBufferTests, correctFindAndPopByCallbackIDWithSameID) {
    HWQueueMirrorBuffer hw_queue_mirror_buffer;

    callback_id_type callback_id = 1;

    hw_queue_mirror_buffer.putSolidDataAndCallbackID(create_hw_queue_mirror_element(callback_id));

    auto temp = hw_queue_mirror_buffer.findAndPopByCallbackID(callback_id);

    ASSERT_THROW(hw_queue_mirror_buffer.findAndPopByCallbackID(callback_id), std::logic_error);
}

/**
 * Test verifies that id of pushed and popped element are the same
 */

TEST(HWQueueMirrorBufferTests, correctPutAndPop) {
    HWQueueMirrorBuffer hw_queue_mirror_buffer;

    callback_id_type callback_id = 1;

    hw_queue_mirror_buffer.putSolidDataAndCallbackID(create_hw_queue_mirror_element(callback_id));

    EXPECT_EQ(callback_id, hw_queue_mirror_buffer.findAndPopByCallbackID(callback_id).callback_id);
}





