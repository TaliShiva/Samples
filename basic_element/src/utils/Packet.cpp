
#include "../../include/utils/Packet.hpp"


::std::string Packet::buildPacket(const ::std::string &data) {
    std::ostringstream ss;
    ss << std::setw(Packet::HEADER_BODY_LENGTH_SIZE) << std::setfill('0') << data.size();
    std::string coded_size(ss.str());
    return coded_size + data;
}

::std::string Packet::parsePacket(const ::std::string &packet) {
    auto data = packet.substr(Packet::HEADER_BODY_LENGTH_SIZE, packet.size());
    return data;
}

size_t Packet::getBodySizeFromPacket(const ::std::string &packet) {
    size_t size = static_cast<unsigned>(std::stoi(packet.substr(0, Packet::HEADER_BODY_LENGTH_SIZE)));
    return size;
}

size_t Packet::packet_read_complete(char *buf, const boost::system::error_code &err, size_t bytes) {
    if (err) {
        throw std::runtime_error("asio: Error reading from socket: " + err.message());
    }
    // Header
    if (bytes < Packet::HEADER_SIZE) {
        return Packet::HEADER_SIZE - bytes;
    }
    // All data
    auto packet_size = Packet::getBodySizeFromPacket(buf) + Packet::HEADER_SIZE;
    if (bytes < packet_size) {
        return packet_size - bytes;
    }
    return 0;
}
