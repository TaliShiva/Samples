/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _SOLIDDATA_H
#define _SOLIDDATA_H

#include "DataAtom.hpp"

class SolidDataChain;

class SolidData {
public:
    std::vector<std::shared_ptr<DataAtom>> data_atoms;
    std::shared_ptr<SolidDataChain> solid_data_chain_ptr;
    long code_ = LONG_MAX;

    SolidData() = delete;

    explicit SolidData(std::vector<std::shared_ptr<DataAtom>> &&data_atoms);

    SolidData(const SolidData &other) = delete;

    SolidData &operator=(const SolidData &other) = delete;

    SolidData(SolidData &&other) = default;

    SolidData &operator=(SolidData &&other) = default;

    void sendOperationResultCode(long code);

    ~SolidData() = default;

    /**
     * @brief Return size writting data in bytes
     * @return size in bytes
     */
    size_t getSolidDataSize() const;
};

#endif //_SOLIDDATA_H