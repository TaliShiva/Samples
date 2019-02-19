/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _CHECKSUMSOLIDDATAWRITE_H
#define _CHECKSUMSOLIDDATAWRITE_H

#include <vector>
#include <memory>


class ChecksumChainWrite;

class ChecksumSolidDataWrite {
public:
    std::shared_ptr<ChecksumChainWrite> checksum_chain_write;

    ChecksumSolidDataWrite() = delete;
    explicit ChecksumSolidDataWrite(const std::shared_ptr<ChecksumChainWrite> &checksum_chain_write);
    ChecksumSolidDataWrite(ChecksumSolidDataWrite&& other) = default;
    ChecksumSolidDataWrite& operator=(ChecksumSolidDataWrite&& other) = default;
    ~ChecksumSolidDataWrite() = default;
};

#endif //_CHECKSUMSOLIDDATAWRITE_H