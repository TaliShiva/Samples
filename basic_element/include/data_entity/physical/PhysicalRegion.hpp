/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _PHYSICALREGION_H
#define _PHYSICALREGION_H

#include <cstddef>

struct PhysicalRegion {
public:
    unsigned int raid_id;
    unsigned int raid_disk_number;
    unsigned long long disk_offset;
    size_t disk_length;

    PhysicalRegion();
    PhysicalRegion(unsigned int raid_id, unsigned int raid_disk_number,
                   unsigned long long int disk_offset, size_t disk_length);
    PhysicalRegion(const PhysicalRegion& other) = default;
    PhysicalRegion& operator=(const PhysicalRegion& other) = default;
    PhysicalRegion(PhysicalRegion&& other) = default;
    PhysicalRegion& operator=(PhysicalRegion&& other) = default;
    ~PhysicalRegion() = default;
};

#endif //_PHYSICALREGION_H