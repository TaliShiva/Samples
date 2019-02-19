/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _ENTITYSTATISTICS_H
#define _ENTITYSTATISTICS_H

#include <cstddef>
#include <chrono>
#include <utility>

/**
 * @struct EntityStatistics
 * @brief container for statistics elements
 * @version 1.0
 */
struct EntityStatistics {
public:
    std::chrono::microseconds time_duration;
    size_t size;

    EntityStatistics() = default;
    EntityStatistics(const std::chrono::microseconds & time_duration, size_t size);
    EntityStatistics(const EntityStatistics &other) = default;
    EntityStatistics &operator=(const EntityStatistics & other) = default;
    EntityStatistics(EntityStatistics&& other) = default;
    EntityStatistics& operator=(EntityStatistics&& other) = default;
    ~EntityStatistics() = default;
};

#endif //_ENTITYSTATISTICS_H