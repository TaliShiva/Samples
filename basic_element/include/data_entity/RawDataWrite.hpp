/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _RAWDATAWRITE_H
#define _RAWDATAWRITE_H

#include <vector>
#include <boost/align/aligned_allocator.hpp>

#define BOOST_LOG_DYN_LINK
#include <boost/log/trivial.hpp>

/**
 * Max sector size in bytes of any drives in Storage
 */
const unsigned MAX_SECTOR_SIZE = 4096;

/**
 * Type for payload data. Alignment needed for non-buffering disk I/O (O_DIRECT)
 */
using payload_data_vector = std::vector<unsigned char, boost::alignment::aligned_allocator<unsigned char, MAX_SECTOR_SIZE>>;

class RawDataWrite {
public:
    payload_data_vector data;

    RawDataWrite() = delete;

    explicit RawDataWrite(unsigned recommended_size);

    explicit RawDataWrite(
            const payload_data_vector &data);

    RawDataWrite(const RawDataWrite &other) = delete;

    RawDataWrite &operator=(const RawDataWrite &other) = delete;

    RawDataWrite(RawDataWrite &&other) = default;

    RawDataWrite &operator=(RawDataWrite &&other) = default;

    ~RawDataWrite() = default;
};

#endif //_RAWDATAWRITE_H