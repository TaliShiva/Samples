/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _CHECKSUMCHAINWRITE_H
#define _CHECKSUMCHAINWRITE_H

#include "ChecksumSolidDataWrite.hpp"
#include "FullStripeWrite.hpp"

class ChecksumChainWrite {
public:
    std::vector<std::shared_ptr<ChecksumSolidDataWrite>> checksum_solid_datas_write;
    std::shared_ptr<FullStripeWrite> full_stripe_write;

    ChecksumChainWrite() = delete;
    explicit ChecksumChainWrite(const std::vector<std::shared_ptr<ChecksumSolidDataWrite>> &checksum_solid_datas_write);
    ChecksumChainWrite(const ChecksumChainWrite &other) = delete;
    ChecksumChainWrite& operator=(const ChecksumChainWrite &other) = delete;
    ChecksumChainWrite(ChecksumChainWrite&& other) = default;
    ChecksumChainWrite& operator=(ChecksumChainWrite&& other) = default;
    ~ChecksumChainWrite() = default;

};

#endif //_CHECKSUMCHAINWRITE_H