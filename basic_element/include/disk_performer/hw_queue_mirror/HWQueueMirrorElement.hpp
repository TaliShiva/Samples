/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _HWQUEUEMIRRORELEMENT_H
#define _HWQUEUEMIRRORELEMENT_H

#include <chrono>

#include "../../data_entity/system/SolidData.hpp"

using callback_id_type = unsigned long long int;

/**
 * @struct HWQueueMirrorElement
 * @brief container for mirrors of hardware queue elements
 * @version 1.0
 *
 */
struct HWQueueMirrorElement {

public:

    std::chrono::system_clock::time_point start_time;
    callback_id_type callback_id;
    std::shared_ptr<SolidData> solid_data_ptr;

    HWQueueMirrorElement() = delete;
    HWQueueMirrorElement(const std::chrono::system_clock::time_point &start_time,
                         const std::shared_ptr<SolidData> &solid_data_ptr,
                         callback_id_type callback_id);

    HWQueueMirrorElement(const HWQueueMirrorElement &other) = delete;
    HWQueueMirrorElement& operator=(const HWQueueMirrorElement &other) = delete;
    HWQueueMirrorElement(HWQueueMirrorElement&& other) = default;
    HWQueueMirrorElement& operator=(HWQueueMirrorElement&& other) = default;
    ~HWQueueMirrorElement() = default;


};

#endif //_HWQUEUEMIRRORELEMENT_H