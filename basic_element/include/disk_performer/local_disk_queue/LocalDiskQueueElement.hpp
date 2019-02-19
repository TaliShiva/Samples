/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _LOCALDISKQUEUEELEMENT_H
#define _LOCALDISKQUEUEELEMENT_H

#include "../../data_entity/system/SolidDataChain.hpp"

/**
 * @class LocalDiskQueueElement
 * @brief container for solid data chain
 */
class LocalDiskQueueElement {
public:
    std::vector<std::shared_ptr<SolidData>>::iterator solid_datas_it; /*!< points to solid data to be popped next */
    std::shared_ptr<SolidDataChain> solid_data_chain; /*!< chain to be processed */

    LocalDiskQueueElement() = delete;
    explicit LocalDiskQueueElement(const std::shared_ptr<SolidDataChain> &solid_data_chain);
    LocalDiskQueueElement(const LocalDiskQueueElement &other) = delete;
    LocalDiskQueueElement& operator=(const LocalDiskQueueElement &other) = delete;
    LocalDiskQueueElement(LocalDiskQueueElement&& other) = default;
    LocalDiskQueueElement& operator=(LocalDiskQueueElement&& other) = default;
};

#endif //_LOCALDISKQUEUEELEMENT_H