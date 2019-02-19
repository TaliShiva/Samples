
#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>

#include <boost/asio.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/bind.hpp>

#include <google/protobuf/io/coded_stream.h>


class Packet {
public:

    /**
     * @def Bytes
     */
    const static size_t HEADER_BODY_LENGTH_SIZE = 10;

    const static size_t HEADER_SIZE = HEADER_BODY_LENGTH_SIZE;
    /**
     * @def Bytes
     */
    const static size_t MAX_PACKET_SIZE = 65536;

    /**
     * @brief Pack data to send via stream
     * @param data RAW-data
     * @return Packed data
     */
    static ::std::string buildPacket(const ::std::string &data);

    /**
     * @brief Unpack data
     * @param packet Packed data
     * @return Unpacked data
     */
    static ::std::string parsePacket(const ::std::string &packet);

    /**
     * @brief Calculate body size in packet
     * @param packet  Packed data
     * @return Size in bytes
     */
    static size_t getBodySizeFromPacket(const ::std::string &packet);

    /**
     * @brief Checks that the package is received completely.
     * Useful with boost::asio::complete
     * @param buf Pointer to the data buffer
     * @param err Link to error code
     * @param bytes The total size of the data received
     * @return How much data is still needed
     */
    static size_t packet_read_complete(char *buf, const boost::system::error_code &err, size_t bytes);
};


