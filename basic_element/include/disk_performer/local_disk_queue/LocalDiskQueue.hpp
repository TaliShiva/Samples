/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _LOCALDISKQUEUE_H
#define _LOCALDISKQUEUE_H

#include <atomic>
#include <boost/signals2.hpp>
#include <chrono>
#include <condition_variable>
#include <deque>
#include <memory>

#include "LocalDiskQueueElement.hpp"
#include "../statistics/EntityStatisticsBuffer.hpp"

class localDiskQueueInterruptWaitException : public std::exception {};
class localDiskQueueShutdownInvalidException : public std::exception {};

/**
 * @class LocalDiskQueue
 * @brief Receives solid data chains, returns solid datas thread safely, signals crossing min/max levels.
 */
class LocalDiskQueue {
public:
    boost::signals2::signal<void ()> sig_max_level_above; /*!< signals that now there are more than max_level elements */
    boost::signals2::signal<void ()> sig_max_level_below; /*!< signals that now there are less than max_level elements */
    boost::signals2::signal<void ()> sig_min_level_above; /*!< signals that now there are more than min_level elements */
    boost::signals2::signal<void ()> sig_min_level_below; /*!< signals that now there are less than min_level elements */

    const unsigned int min_level_size; /*!< corresponding signals are sent if this number of elements goes through this level */
    const unsigned int max_level_size; /*!< corresponding signals are sent if this number of elements goes through this level */
    std::atomic_bool min_level_flag {true}; /*!< indicates that there are less than min_level elements enqueued */
    std::atomic_bool max_level_flag {false}; /*!< indicates that there are more than max_level elements enqueued */
    std::atomic_bool receive_next_flag {false}; /*!< indicates that LocalDiskQueue is ready to receive next solid data chain */
    std::chrono::steady_clock::time_point start_time_on_front_solid_data_chain; /*!< accurate time when chain was added to the queue */
    std::shared_ptr<EntityStatisticsBuffer> solid_data_chain_statistics_buffer_; /*!< chain statistics is sent here */


    LocalDiskQueue() = delete;
    LocalDiskQueue(std::shared_ptr<EntityStatisticsBuffer> &&solid_data_chain_statistics_buffer,
                   unsigned int min_level_size,
                   unsigned int max_level_size);
    LocalDiskQueue(const LocalDiskQueue &other) = delete;
    LocalDiskQueue& operator=(const LocalDiskQueue &other) = delete;
    LocalDiskQueue(LocalDiskQueue&& other) = default;
    LocalDiskQueue& operator=(LocalDiskQueue&& other) = default;
    /**
     * @brief if no solid data can be taken, infinite waiting occurs
     * @throw localDiskQueueInterruptWaitException
     * @return SolidData from queue
     */
    std::shared_ptr<SolidData> waitAndPopSolidData();
    /**
     * @brief store SolidDataChain in queue
     * @throw localDiskQueueShutdownInvalidException
     * @param solid_data_chain
     */
    void putSolidDataChainInQueue(std::shared_ptr<SolidDataChain> solid_data_chain);
    void waitUntilReadyToReceive(); /*!< if above min_level, waits for solid data chin popping until unblocking */
    /**
     * @brief Shutdown all activity and correct stop internal thread
     */
    void shutdown() noexcept;

private:
    std::deque<LocalDiskQueueElement> local_disk_queue_elements_; /*!< elements are just solid data chains containers */
    unsigned long long front_solid_data_chain_size_; /*!< how many solid datas are in chain; needed for statistics */
    std::mutex queue_mutex_; /*!< guarantees thread safety  for push/pop */
    std::condition_variable queue_not_empty_; /*!< notifies external services */
    std::mutex receive_next_mutex_; /*!< guarantees thread safety for push */
    std::condition_variable receive_next_chain_; /*!< notifies exteranal services */
    std::atomic_bool stop_working_;
};

#endif //_LOCALDISKQUEUE_H