/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _FULLSTRIPEWRITE_H
#define _FULLSTRIPEWRITE_H

#include "DataStripeWrite.hpp"
#include "SolidDataChain.hpp"

class FullStripeWrite {
public:
    std::shared_ptr<DataStripeWrite> data_stripe_write_ptr;
    std::shared_ptr<SolidDataChain> solid_data_chain_ptr;

    FullStripeWrite() = delete;
    explicit FullStripeWrite(const std::shared_ptr<DataStripeWrite> &data_stripe_write_ptr,
                    const std::shared_ptr<SolidDataChain> &solid_data_chain_ptr);
    FullStripeWrite(const FullStripeWrite &other) = delete;
    FullStripeWrite& operator=(const FullStripeWrite &other) = delete;
    FullStripeWrite(FullStripeWrite&& other) = default;
    FullStripeWrite& operator=(FullStripeWrite&& other) = default;
    ~FullStripeWrite() = default;
};

#endif //_FULLSTRIPEWRITE_H