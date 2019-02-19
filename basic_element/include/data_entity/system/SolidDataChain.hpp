/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _SOLIDDATACHAIN_H
#define _SOLIDDATACHAIN_H

#include "SolidData.hpp"

class DataStripeWrite;

class SolidDataChain {
public:
    std::vector<std::shared_ptr<SolidData>> solid_datas;
    std::shared_ptr<DataStripeWrite> data_stripe_write_ptr;

    SolidDataChain() = delete;
    explicit SolidDataChain(std::vector<std::shared_ptr<SolidData>> &&solid_datas);
    SolidDataChain(const SolidDataChain &other) = delete;
    SolidDataChain& operator=(const SolidDataChain &other) = delete;
    SolidDataChain(SolidDataChain&& other) = default;
    SolidDataChain& operator=(SolidDataChain&& other) = default;
    ~SolidDataChain() = default;

    /**
     * @brief true if operation completed
     */
    bool isChainCompleted();
    long getResultCode();

    /**
     * @brief true if operation completed successfuly
     */
    bool isChainSuccessful();
};

#endif //_SOLIDDATACHAIN_H