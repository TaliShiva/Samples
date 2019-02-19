
#include "../include/packet.hpp"

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
    size_t size = std::stoi(packet.substr(0, Packet::HEADER_BODY_LENGTH_SIZE));
    return size;
}

bool Packet::packetIsFull(const ::std::string &packet) {
    if (packet.size() > Packet::HEADER_BODY_LENGTH_SIZE) {
        size_t data_length = std::stoi(packet.substr(0, Packet::HEADER_BODY_LENGTH_SIZE));
        if (packet.size() >= (data_length + Packet::HEADER_BODY_LENGTH_SIZE)) {
            return true;
        }
    }
    return false;

}