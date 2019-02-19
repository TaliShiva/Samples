/**
 * Project Gorynych
 * @version 0.1
 */


#include "../../../include/data_entity/client/ClientDataPacketWrite.hpp"

ClientDataPacketWrite::ClientDataPacketWrite(const std::vector<std::shared_ptr<ClientDataStripeWrite>> &client_data_stripes_write,
                                             const std::shared_ptr<RawDataWrite> &raw_data_write_ptr) {
    this->client_data_stripes_write = client_data_stripes_write;
    this->raw_data_write_ptr = raw_data_write_ptr;
}
