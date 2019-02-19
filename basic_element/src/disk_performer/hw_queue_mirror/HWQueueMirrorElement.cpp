/**
 * Project Gorynych
 * @version 0.1
 */


#include "../../../include/disk_performer/hw_queue_mirror/HWQueueMirrorElement.hpp"

HWQueueMirrorElement::HWQueueMirrorElement(const std::chrono::system_clock::time_point &start_time,
                                           const std::shared_ptr<SolidData> &solid_data_ptr,
                                           callback_id_type callback_id) : start_time(start_time), 
                                                                           callback_id(callback_id), 
                                                                           solid_data_ptr(solid_data_ptr) {
}

