/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _ENTITYSTATISTICSBUFFER_H
#define _ENTITYSTATISTICSBUFFER_H

#include <vector>
#include <mutex>
#include <utility>

#include "EntityStatistics.hpp"

/**
 * @class EntityStatisticsBuffer
 * @brief Receives statistics elements, all methods are thread safely
 * @version 1.0
 */
class EntityStatisticsBuffer {
private:
    std::vector<EntityStatistics> entity_statistics_;
    std::mutex statistics_mutex_;
public:
    EntityStatisticsBuffer() = delete;
    explicit EntityStatisticsBuffer(unsigned recommended_size);
    EntityStatisticsBuffer(const EntityStatisticsBuffer &other) = delete;
    EntityStatisticsBuffer& operator=(const EntityStatisticsBuffer &other) = delete;
    EntityStatisticsBuffer(EntityStatisticsBuffer&&);
    EntityStatisticsBuffer& operator=(EntityStatisticsBuffer&&) = default;
    ~EntityStatisticsBuffer() = default;

    /**
     * @brief method push EntityStatistics object into field entity_statistics
     * @param element - EntityStatistics object
     */
    void push(EntityStatistics element);

    /**
     * @brief method return copy of the field entity_statistics and clear it
     * @return copy of the field entity_statistics
     */
    std::vector<EntityStatistics> getCopyAndClear();
};

#endif //_ENTITYSTATISTICSBUFFER_H