/**
 * Project Gorynych
 * @version 0.1
 */

#include <utility>

#include "../../../include/disk_performer/hw_queue_mirror/HWQueueMirrorBuffer.hpp"

void HWQueueMirrorBuffer::putSolidDataAndCallbackID(HWQueueMirrorElement &&element) {
    std::lock_guard<std::mutex> lock(hw_queue_mirror_buffer_mutex_);
    if (hw_queue_mirror_elements_.find(element.callback_id) != hw_queue_mirror_elements_.end()) {
        throw std::logic_error("attempt to write an element with an existing key");
    }
    auto p = std::make_pair(element.callback_id, std::move(element));
    hw_queue_mirror_elements_.insert(std::move(p));
}

HWQueueMirrorElement HWQueueMirrorBuffer::findAndPopByCallbackID(callback_id_type callbackID) {
    std::lock_guard<std::mutex> lock(hw_queue_mirror_buffer_mutex_);
    auto it = hw_queue_mirror_elements_.find(callbackID);
    if (it == hw_queue_mirror_elements_.end()) {
        throw std::logic_error("attempt to get an element with a non-existing key");
    }
    auto element = std::move(it->second);
    hw_queue_mirror_elements_.erase(callbackID);
    return element;
}

unsigned long HWQueueMirrorBuffer::size() const {
    std::lock_guard<std::mutex> lock(hw_queue_mirror_buffer_mutex_);
    return hw_queue_mirror_elements_.size();
}