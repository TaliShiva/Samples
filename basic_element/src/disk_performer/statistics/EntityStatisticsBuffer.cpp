/**
 * Project Gorynych
 * @version 0.1
 */


#include <stdexcept>

#include "../../../include/disk_performer/statistics/EntityStatisticsBuffer.hpp"

EntityStatisticsBuffer::EntityStatisticsBuffer(unsigned recommended_size) {
    this->entity_statistics_.reserve(recommended_size);
}

EntityStatisticsBuffer::EntityStatisticsBuffer(EntityStatisticsBuffer &&other) {
    std::lock_guard<std::mutex> lock(other.statistics_mutex_);
    entity_statistics_ = std::move(other.entity_statistics_);
}

void EntityStatisticsBuffer::push(EntityStatistics element) {
    std::lock_guard<std::mutex> lock(statistics_mutex_);
    this->entity_statistics_.push_back(element);
}

std::vector<EntityStatistics> EntityStatisticsBuffer::getCopyAndClear() {
    std::lock_guard<std::mutex> lock(statistics_mutex_);
    std::vector<EntityStatistics> temp;
    temp.reserve(this->entity_statistics_.capacity());
    std::swap(temp, this->entity_statistics_);
    return temp;
}

