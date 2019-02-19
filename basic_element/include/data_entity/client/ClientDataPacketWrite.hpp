/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _CLIENTDATAPACKETWRITE_H
#define _CLIENTDATAPACKETWRITE_H

#include <memory>

#include "../RawDataWrite.hpp"
#include "ClientDataStripeWrite.hpp"

class ClientDataPacketWrite {
public:
    std::vector<std::shared_ptr<ClientDataStripeWrite>> client_data_stripes_write;
    std::shared_ptr<RawDataWrite> raw_data_write_ptr;

    ClientDataPacketWrite() = delete;
    ClientDataPacketWrite(const std::vector<std::shared_ptr<ClientDataStripeWrite>> &client_data_stripes_write,
                          const std::shared_ptr<RawDataWrite> &raw_data_write_ptr);
    ClientDataPacketWrite(const ClientDataAtomWrite &other) = delete;
    ClientDataPacketWrite& operator=(const ClientDataPacketWrite &other) = delete;
    ClientDataPacketWrite(ClientDataPacketWrite&& other) = default;
    ClientDataPacketWrite& operator=(ClientDataPacketWrite&& other) = default;
};

#endif //_CLIENTDATAPACKETWRITE_H