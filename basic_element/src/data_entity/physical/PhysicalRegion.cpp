/**
 * Project Gorynych
 * @version 0.1
 */

#include "../../../include/data_entity/physical/PhysicalRegion.hpp"

PhysicalRegion::PhysicalRegion(): raid_id(0), raid_disk_number(0), disk_offset(0), disk_length(0) { }

PhysicalRegion::PhysicalRegion(unsigned int raid_id,
                               unsigned int raid_disk_number,
                               unsigned long long int disk_offset,
                               size_t disk_length) : raid_id(raid_id),
                                                     raid_disk_number(raid_disk_number),
                                                     disk_offset(disk_offset),
                                                     disk_length(disk_length) { }