/**
 * Project Gorynych
 * @version 0.1
 */


#include "../../../include/data_entity/client/ClientDataStripeWrite.hpp"

ClientDataStripeWrite::ClientDataStripeWrite(const std::vector<std::shared_ptr<ClientDataAtomWrite>> &client_data_atoms_write) {
    this->client_data_atoms_write = client_data_atoms_write;
}
