/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _DATASTRIPEWRITE_H
#define _DATASTRIPEWRITE_H

#include "SolidDataChain.hpp"

class FullStripeWrite;

class DataStripeWrite {
public:
    std::vector<std::shared_ptr<SolidDataChain>> solid_data_chains;
    std::shared_ptr<FullStripeWrite> full_stripe_write_ptr;

    DataStripeWrite() = delete;
    explicit DataStripeWrite(const std::vector<std::shared_ptr<SolidDataChain>> &solid_data_chains);
    DataStripeWrite(const DataStripeWrite &other) = delete;
    DataStripeWrite& operator=(const DataStripeWrite &other) = delete;
    DataStripeWrite(DataStripeWrite&& other) = default;
    DataStripeWrite& operator=(DataStripeWrite&& other) = default;
    ~DataStripeWrite() = default;
};

#endif //_DATASTRIPEWRITE_H