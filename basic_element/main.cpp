#include <iostream>
#include <fstream>
#include "include/TestProgram.hpp"

int main() {

    std::string device_path = "/tmp/device";
    std::string socket_path = "/tmp/socket";
    std::string config_path = "../configs/many_solid_data_in_chain.json";
    unsigned hw_queue_depth = 16;
    unsigned min_level_size = 10;
    unsigned max_level_size = 100;
    std::chrono::milliseconds work_time{60000};

    std::ofstream create_device(device_path);
    create_device << "";
    create_device.close();

    std::ofstream create_socket(socket_path);
    create_socket << "";
    create_socket.close();

    TestProgram test_program(device_path,
                             socket_path,
                             config_path,
                             hw_queue_depth,
                             min_level_size,
                             max_level_size,
                             work_time);
    test_program.run();

    std::ifstream device(device_path);
    device.seekg(0, device.end);
    size_t size = device.tellg();

    payload_data_vector buffer(size, ' ');
    device.seekg(0);
    device.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
    device.close();
    boost::crc_32_type checkSum;
    checkSum.process_bytes(buffer.data(), buffer.size());

    assert(test_program.getCheckSum() == checkSum.checksum());

    std::remove(device_path.c_str());
    std::remove(socket_path.c_str());
}


