/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _HWQUEUEMIRRORBUFFER_H
#define _HWQUEUEMIRRORBUFFER_H

#include <map>
#include <mutex>

#include "HWQueueMirrorElement.hpp"

/**
 * @class HWQueueMirrorBuffer
 * @brief Receives mirrors of hardware queue elements, all methods thread safely
 * @version 1.0
 */
class HWQueueMirrorBuffer {

private:
    std::map<callback_id_type, HWQueueMirrorElement> hw_queue_mirror_elements_;
    mutable std::mutex hw_queue_mirror_buffer_mutex_;

public:
    HWQueueMirrorBuffer() = default;
    HWQueueMirrorBuffer(const HWQueueMirrorBuffer &other) = delete;
    HWQueueMirrorBuffer& operator=(const HWQueueMirrorBuffer &other) = delete;
    HWQueueMirrorBuffer(HWQueueMirrorBuffer&& other) = default;
    HWQueueMirrorBuffer& operator=(HWQueueMirrorBuffer&& other) = default;
    ~HWQueueMirrorBuffer() = default;

    /**
     * @brief method adds HWQueueMirrorElement and it's callbackID into hw_queue_mirror_elements
     * @param element - HWQueueMirrorElement object which should be added
     * Generates an exception when trying to write an element with an existing key
     */
    void putSolidDataAndCallbackID(HWQueueMirrorElement && element);

    /**
     * @brief method finds HWQueueMirrorElement object by it's callbackID and pops that object
     * @param callbackID - id on which the search is conducted
     * @return - HWQueueMirrorElement object
     * Generates an exception when attempting to retrieve an element on a nonexistent key
     */
    HWQueueMirrorElement findAndPopByCallbackID(callback_id_type callbackID);

    /**
     * @brief method return hw_queue_mirror_elements size
     * @return hw_queue_mirror_elements size
     */
    unsigned long size() const;

};

#endif //_HWQUEUEMIRRORBUFFER_H