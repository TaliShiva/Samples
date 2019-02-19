
#include <thread>

#include <fstream>

#include <gtest/gtest.h>
#include <boost/align/aligned_allocator.hpp>

#include "../../include/disk_performer/DiskPort.hpp"

/**
 * @brief Read data from file
 * @param file_path
 * @param start_pos
 * @param read_size
 * @throw std::runtime_error when file less than expected
 * @return
 */
std::string getFileContent(const std::string &file_path, unsigned long long start_pos, size_t read_size) {
    std::ifstream t(file_path);
    t.seekg(0, std::ios::end);
    size_t file_total_size = t.tellg();
    if (file_total_size < start_pos + read_size) {
        throw std::runtime_error("The file contains less data than expected");
    }
    std::string buffer(read_size, ' ');
    t.seekg(start_pos);
    t.read(&buffer[0], read_size);
    t.close();
    return buffer;
}

/**
 * @brief Construct SolidData
 * @param offset
 * @param length
 * @param fill
 * @param data_atom_count
 * @return
 */
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

/**
 * Write and verify recorded data
 */
TEST(DiskPortTests, correctOneWrite) {
    const std::string file_path = "/tmp/tt-en1wie0iYohc2eogha3e";
    const unsigned sector_size = 512;
    const unsigned sector_count = 1;
    constexpr unsigned one_write_size = sector_size * sector_count;
    const unsigned char fill = 'K';
    const callback_id_type callback_id = 5;
    const unsigned buffer_count = 1;

    std::ofstream createfile(file_path);
    createfile << "" << std::endl;
    createfile.close();

    auto disk_port = new DiskPort(file_path);

    disk_port->asyncWrite(getSolidData(0, one_write_size, fill, buffer_count), callback_id);
    sleep(1);
    sync();
    delete disk_port;

    std::string content = getFileContent(file_path, 0, one_write_size);
    auto ret = content.find_first_not_of(fill);
    std::remove(file_path.c_str());
    EXPECT_EQ(std::string::npos, ret);

}

/**
 * Write and check answer code
 */
TEST(DiskPortTests, correctOneWriteAndAnswer) {
    const std::string file_path = "/tmp/tt-aevoo7oe0Chauc5ieghu";
    const unsigned sector_size = 512;
    const unsigned sector_count = 1;
    constexpr unsigned one_write_size = sector_size * sector_count;
    const unsigned char fill = 'Z';
    const callback_id_type callback_id = 5;
    const unsigned buffer_count = 1;

    std::ofstream createfile(file_path);
    createfile << "" << std::endl;
    createfile.close();

    auto disk_port = new DiskPort(file_path);

    disk_port->asyncWrite(getSolidData(0, one_write_size, fill, buffer_count), callback_id);
    auto result = disk_port->waitAndGetAnswer(false);
    delete disk_port;
    std::remove(file_path.c_str());
    EXPECT_EQ(one_write_size, result.second);
    EXPECT_EQ(callback_id, result.first);
}

/**
 * Write from multiple buffers and verify recorded data
 */
TEST(DiskPortTests, correctOneWriteFromMultipleBuffer) {
    const std::string file_path = "/tmp/tt-phohw4be3sheeGhaib0e";
    const unsigned sector_size = 512;
    const unsigned sector_count = 1;
    constexpr unsigned one_write_size = sector_size * sector_count;
    const unsigned char fill = 'U';
    const callback_id_type callback_id = 5;
    const unsigned buffer_count = 4;
    constexpr unsigned summ_write_bytes = one_write_size * buffer_count;

    std::ofstream createfile(file_path);
    createfile << "" << std::endl;
    createfile.close();

    auto disk_port = new DiskPort(file_path);

    disk_port->asyncWrite(getSolidData(0, one_write_size, fill, buffer_count), callback_id);
    sleep(1);
    sync();
    delete disk_port;

    std::string content = getFileContent(file_path, 0, summ_write_bytes);
    auto ret = content.find_first_not_of(fill);
    std::remove(file_path.c_str());
    EXPECT_EQ(std::string::npos, ret);

}

/**
 * Write from multiple buffers and check answer code
 */
TEST(DiskPortTests, correctOneWriteFromMultipleBufferAndAnswer) {
    const std::string file_path = "/tmp/tt-Oochi9IlahxeiVeg9eQu";
    const unsigned sector_size = 512;
    const unsigned sector_count = 1;
    constexpr unsigned one_write_size = sector_size * sector_count;
    const unsigned char fill = 'U';
    const callback_id_type callback_id = 5;
    const unsigned buffer_count = 4;
    constexpr unsigned summ_write_bytes = one_write_size * buffer_count;

    std::ofstream createfile(file_path);
    createfile << "" << std::endl;
    createfile.close();

    auto disk_port = new DiskPort(file_path);

    disk_port->asyncWrite(getSolidData(0, one_write_size, fill, buffer_count), callback_id);
    auto result = disk_port->waitAndGetAnswer(false);
    delete disk_port;
    EXPECT_EQ(summ_write_bytes, result.second);
    std::remove(file_path.c_str());


}


/**
 * Check while open non exist device
 */
TEST(DiskPortTests, correctExceptionWhenOpenNonExistDevice) {
    const std::string file_path = "/tmp/tt-Ig2ahngeey4AiteeNgai";

    std::remove(file_path.c_str());
    try {
        DiskPort disk_port(file_path);
        FAIL();
    } catch (std::system_error &e) {
        EXPECT_EQ(e.code().value() , static_cast<int>(std::errc::no_such_file_or_directory));
    }

}


