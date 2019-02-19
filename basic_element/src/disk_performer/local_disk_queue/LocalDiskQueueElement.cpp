/**
 * Project Gorynych
 * @version 0.1
 */


#include <vector>

#include "../../../include/data_entity/system/SolidDataChain.hpp"
#include "../../../include/disk_performer/local_disk_queue/LocalDiskQueueElement.hpp"

LocalDiskQueueElement::LocalDiskQueueElement(const std::shared_ptr<SolidDataChain> &solid_data_chain) {
    this->solid_data_chain = solid_data_chain;
    solid_datas_it = this->solid_data_chain->solid_datas.begin();
}
