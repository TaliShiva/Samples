/**
 * Project Gorynych
 * @version 0.1
 */


#include <iostream>
#include "../../../include/data_entity/system/SolidData.hpp"

SolidData::SolidData(std::vector<std::shared_ptr<DataAtom>> &&data_atoms) {
    if (data_atoms.empty()) {
        throw std::logic_error("can not construct solid data with no data atoms!");
    }
    this->data_atoms = std::move(data_atoms);
}

void SolidData::sendOperationResultCode(long code) {
    code_ = code;
}

size_t SolidData::getSolidDataSize() const {
    size_t solid_data_size = 0;
    for (auto &atom: this->data_atoms) {
        solid_data_size += atom->physical_region.disk_length;
    }
    return solid_data_size;
}
