/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _CLIENTDATASTRIPEWRITE_H
#define _CLIENTDATASTRIPEWRITE_H

#include <vector>

#include "ClientDataAtomWrite.hpp"

class ClientDataPacketWrite;

class ClientDataStripeWrite {
public:
    std::vector<std::shared_ptr<ClientDataAtomWrite>> client_data_atoms_write;
    std::shared_ptr<ClientDataPacketWrite> client_data_packet_write_ptr;

    ClientDataStripeWrite() = delete;
    ClientDataStripeWrite(const std::vector<std::shared_ptr<ClientDataAtomWrite>> &client_data_atoms_write);
    ClientDataStripeWrite(const ClientDataStripeWrite& other) = delete;
    ClientDataStripeWrite& operator=(const ClientDataStripeWrite &other) = delete;
    ClientDataStripeWrite(ClientDataStripeWrite&& other) = default;
    ClientDataStripeWrite& operator=(ClientDataStripeWrite&& other) = default;
};

#endif //_CLIENTDATASTRIPEWRITE_H