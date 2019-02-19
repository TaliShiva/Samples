/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _DATAATOM_H
#define _DATAATOM_H

#include <vector>
#include <memory>

#include "../physical/PhysicalRegion.hpp"
#include "../client/ClientDataAtomWrite.hpp"
#include "../RawDataWrite.hpp"

class SolidData;

class DataAtom {
public:
    unsigned long long raw_data_offset;
    PhysicalRegion physical_region;
    std::vector<std::shared_ptr<ClientDataAtomWrite>> client_data_atoms_write;
    std::shared_ptr<SolidData> solid_data_ptr;
    std::shared_ptr<RawDataWrite> raw_data_write_ptr;

    DataAtom() = delete;
    DataAtom(unsigned long long int raw_data_offset,
             const PhysicalRegion &physical_region,
             const std::shared_ptr<RawDataWrite> &raw_data_write_ptr);
    DataAtom(const DataAtom& other) = delete;
    DataAtom& operator=(const DataAtom &other) = delete;
    DataAtom(DataAtom&& other) = default;
    DataAtom& operator=(DataAtom&& other) = default;
    ~DataAtom() = default;
};

#endif //_DATAATOM_H