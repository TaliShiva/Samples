/**
 * Project Gorynych
 * @version 0.1
 */


#include "../../../include/data_entity/system/FullStripeWrite.hpp"

FullStripeWrite::FullStripeWrite(const std::shared_ptr<DataStripeWrite> &data_stripe_write_ptr,
                                 const std::shared_ptr<SolidDataChain> &solid_data_chain_ptr) {
    this->data_stripe_write_ptr = data_stripe_write_ptr;
    this->solid_data_chain_ptr = solid_data_chain_ptr;
}
