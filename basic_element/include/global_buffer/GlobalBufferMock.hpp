/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _GLOBALBUFFERMOCK_H
#define _GLOBALBUFFERMOCK_H

#include <thread>
#include <boost/crc.hpp>

#include "../disk_performer/DiskPerformer.hpp"
#include "../data_entity/system/SolidDataChain.hpp"
#include "../statistics/report/IReport.hpp"
#include "../load/LoadProfile.hpp"
#include "../load/LoadParameters.hpp"

/**
 * @class GlobalBufferMock
 * @brief class imitates data stream for write
 * @version 1.0
 */
class GlobalBufferMock {
public:

    std::shared_ptr<DiskPerformer> disk_performer;

    GlobalBufferMock() = delete;
    explicit GlobalBufferMock(std::shared_ptr<DiskPerformer> disk_performer);
    GlobalBufferMock(const GlobalBufferMock &other) = delete;
    GlobalBufferMock& operator=(const GlobalBufferMock &other) = delete;
    GlobalBufferMock(GlobalBufferMock&& other) = default;
    GlobalBufferMock& operator=(GlobalBufferMock&& other) = default;
    ~GlobalBufferMock();

    /**
     * @brief method launches waitAndPushInDiskPerformerQueue method in a separate thread
     */
    void startPushInDiskPerformerQueue();

    /**
     * @brief method retrieves all elements from queue_of_solid_data_chains_ and processes them
     */
    void waitAndPushInDiskPerformerQueue();

    /**
     * @brief method creates load profile's list according to load parameters
     * @param load_parameters - parameters of load
     */
    void initTestData(const LoadParameters &load_parameters);

    /**
     * @brief method considers checksum of the data in queue_of_solid_data_chains_
     * @return checksum of data
     */
    boost::crc_32_type::value_type getCheckSum();

private:
    std::list<LoadProfile> list_of_load_profiles_;
    std::thread global_buffer_mock_thread_;
    std::atomic_bool is_global_buffer_mock_init_{false};
    unsigned long long offset;

    /**
     * @brief method generate random offset after each SolidData in Chain, multiples of 4096 bytes
     * @return offset
     */
    unsigned int getRandomOffset();

    /**
     * method generates random offset in /dev/urandom
     * @return offset
     */

    std::shared_ptr<SolidData> createSolidData(const LoadTemplate &load_template);

    /**
     * @brief method creates SolidDataChain according to LoadTemplate
     * @param load_template - load template
     * @return shared_ptr to SolidDataChain
     */
    std::shared_ptr<SolidDataChain> createSolidDataChain(const LoadTemplate &load_template);
};

#endif //_GLOBALBUFFERMOCK_H