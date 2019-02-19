/**
 * Project Gorynych
 * @version 0.1
 */


#include "../../../include/data_entity/system/ChecksumChainWrite.hpp"

ChecksumChainWrite::ChecksumChainWrite(const std::vector<std::shared_ptr<ChecksumSolidDataWrite>> &checksum_solid_datas_write) {
    this->checksum_solid_datas_write = checksum_solid_datas_write;
}
