/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _CLIENTDATAATOMWRITE_H
#define _CLIENTDATAATOMWRITE_H

#include <memory>

class DataAtom;

class ClientDataStripeWrite;

class ClientDataAtomWrite {
public:
    std::shared_ptr<DataAtom> data_atom_ptr;
    std::shared_ptr<ClientDataStripeWrite> client_data_stripe_write_ptr;

    ClientDataAtomWrite() = delete;
    ClientDataAtomWrite(const std::shared_ptr<DataAtom> &data_atom_ptr);
    ClientDataAtomWrite(const ClientDataAtomWrite &other) = delete;
    ClientDataAtomWrite& operator=(const ClientDataAtomWrite &other) = delete;
    ClientDataAtomWrite(ClientDataAtomWrite&& other) = default;
    ClientDataAtomWrite& operator=(ClientDataAtomWrite&& other) = default;
};

#endif //_CLIENTDATAATOMWRITE_H