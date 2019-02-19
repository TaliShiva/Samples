/**
 * Project Gorynych
 * @version 0.1
 */



#include "../../../include/disk_performer/statistics/EntityStatistics.hpp"

EntityStatistics::EntityStatistics(const std::chrono::microseconds &time_duration,
                                   size_t size):
        time_duration(time_duration),
        size(size) { }