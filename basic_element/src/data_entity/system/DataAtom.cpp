/**
 * Project Gorynych
 * @version 0.1
 */


#include "../../../include/data_entity/system/DataAtom.hpp"

DataAtom::DataAtom(unsigned long long raw_data_offset,
                   const PhysicalRegion &physical_region,
                   const std::shared_ptr<RawDataWrite> &raw_data_write_ptr) {
    this->raw_data_offset = raw_data_offset;
    this->physical_region = physical_region;
    this->raw_data_write_ptr = raw_data_write_ptr;
}
