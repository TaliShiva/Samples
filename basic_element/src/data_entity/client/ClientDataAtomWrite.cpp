/**
 * Project Gorynych
 * @version 0.1
 */

#include "../../../include/data_entity/client/ClientDataAtomWrite.hpp"

ClientDataAtomWrite::ClientDataAtomWrite(const std::shared_ptr<DataAtom> &data_atom_ptr) {
    this->data_atom_ptr = data_atom_ptr;
}
