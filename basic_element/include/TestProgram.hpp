/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _TESTPROGRAM_H
#define _TESTPROGRAM_H

#include <boost/crc.hpp>

#include "../include/global_buffer/GlobalBufferMock.hpp"
#include "statistics/ExternalStatistics.hpp"

/**
 * @class TestProgram
 * @brief class for testing
 * @version 1.0
 */
class TestProgram {
public:
    boost::signals2::signal<void(std::shared_ptr<IReport>)> start_signal;
    boost::signals2::signal<void(std::shared_ptr<IReport>)> stop_signal;

    unsigned long size;

    TestProgram(std::string path_to_device,
                std::string path_to_socket,
                std::string path_to_config,
                unsigned hw_queue_depth,
                unsigned min_level_size,
                unsigned max_level_size,
                std::chrono::milliseconds work_time);

    /**
     * @brief method runs all classes participating in the test
     * Method creates DiskPerformer, ExternalStatistics and GlobalBufferMock objects, writes data from GlobalBufferMock
     * to device and sends statistics on the socket. Also it calculates checksum to verify the correctness of the writing
     */
    void run();

    boost::crc_32_type::value_type getCheckSum();

private:
    boost::crc_32_type::value_type checksum_;
    std::string path_to_device_;
    std::string path_to_socket_;
    std::string path_to_config_;
    unsigned hw_queue_depth_;
    unsigned min_level_size_;
    unsigned max_level_size_;
    std::chrono::milliseconds work_time_;
};

#endif //_TESTPROGRAM_H