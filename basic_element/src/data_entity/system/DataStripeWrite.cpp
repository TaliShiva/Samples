/**
 * Project Gorynych
 * @version 0.1
 */


#include "../../../include/data_entity/system/DataStripeWrite.hpp"

DataStripeWrite::DataStripeWrite(const std::vector<std::shared_ptr<SolidDataChain>> &solid_data_chains) {
    this->solid_data_chains = solid_data_chains;
}
