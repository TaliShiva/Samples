/**
 * Project Gorynych
 * @version 0.1
 */


#include "../../../include/data_entity/system/ChecksumSolidDataWrite.hpp"

ChecksumSolidDataWrite::ChecksumSolidDataWrite(const std::shared_ptr<ChecksumChainWrite> &checksum_chain_write) {
    this->checksum_chain_write = checksum_chain_write;
}
