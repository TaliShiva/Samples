

#ifndef PROTOBUF_EXAMPLE_PACKAGE_H
#define PROTOBUF_EXAMPLE_PACKAGE_H

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

    static ::std::string buildPacket(const ::std::string &data);

    static ::std::string parsePacket(const ::std::string &packet);

    static size_t getBodySizeFromPacket(const ::std::string &packet);

    static bool packetIsFull(const ::std::string &packet);
};


#endif //PROTOBUF_EXAMPLE_PACKAGE_H
