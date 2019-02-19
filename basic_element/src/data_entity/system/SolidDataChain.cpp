/**
 * Project Gorynych
 * @version 0.1
 */


#include "../../../include/data_entity/system/SolidDataChain.hpp"

SolidDataChain::SolidDataChain(std::vector<std::shared_ptr<SolidData>> &&solid_datas) {
    this->solid_datas = std::move(solid_datas);
}

bool SolidDataChain::isChainCompleted() {
    return solid_datas.at(0)->code_ != LONG_MAX;
}

long SolidDataChain::getResultCode() {
    return solid_datas.at(0)->code_;
}

bool SolidDataChain::isChainSuccessful() {
    return solid_datas.at(0)->code_ == 0;
}
