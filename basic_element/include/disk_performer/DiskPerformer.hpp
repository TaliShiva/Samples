/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _DISKPERFORMER_H
#define _DISKPERFORMER_H

#include <thread>
#include <boost/signals2.hpp>
#include <gtest/gtest_prod.h>

#include "../statistics/report/IReport.hpp"
#include "local_disk_queue/LocalDiskQueue.hpp"
#include "hw_queue_mirror/HWQueueMirrorBuffer.hpp"
#include "../disk_performer/statistics/EntityStatisticsBuffer.hpp"
#include "DiskPort.hpp"


class DiskPerformer {
public:

    /**
     * @brief Report statistics data with SensorsReport
     * Served by DiskPerformer::sensorsProcessingThread
     */
    boost::signals2::signal<void(std::shared_ptr<IReport>)> signal_on_sensor_report;

    /**
     * @brief signal notifies you of a response from the kernel
     */
    boost::signals2::signal<void()> getAnswerFromKernel;

    DiskPerformer() = delete;

    DiskPerformer(unsigned int atomic_hw_count,
                  unsigned int hw_queue_max,
                  std::unique_ptr<LocalDiskQueue> local_disk_queue,
                  std::unique_ptr<HWQueueMirrorBuffer> hw_queue_mirror_buffer,
                  std::unique_ptr<EntityStatisticsBuffer> statistics_buffer_solid_data,
                  std::unique_ptr<DiskPort> disk_port,
                  std::chrono::milliseconds statistic_interval = std::chrono::milliseconds{1000}
    );

    DiskPerformer(const DiskPerformer &other) = delete;

    DiskPerformer &operator=(const DiskPerformer &other) = delete;

    DiskPerformer(DiskPerformer &&other) = default;

    DiskPerformer &operator=(DiskPerformer &&other) = default;

    ~DiskPerformer();

    /**
     * @brief Put SolidDataChain to process in DiskPerformer (write to disk)
     * @param solidDataChain for processing
     */
    void pushSolidDataChain(std::shared_ptr<SolidDataChain> solidDataChain);

    /**
     * @brief Method return when DiskPerformer ready to receive new SolidDataChain
     */
    void waitUntilReadyToReceive();

    /**
     * @brief Start thread for receive answers to write requests SolidData from kernel
     */
    void startReceiveResponseThread();

    /**
     * @brief Start thread for send request write SolidData to kernel
     */
    void startSendRequestThread();

    /**
     * @brief Start thread for calculate statistics and call signall for send SensorsReport
     */
    void startSensorsProcessingThread();

    /**
     * @brief Shutdown all activity and correct stop internal thread
     */
    void shutdown() noexcept;



private:
    FRIEND_TEST(DiskPerformerTests, correctCalculateSensorsStatistics);

    std::atomic<unsigned int> atomic_hw_count_;
    unsigned int hw_queue_max_;
    std::unique_ptr<EntityStatisticsBuffer> statistics_buffer_solid_data_;
    std::unique_ptr<LocalDiskQueue> local_disk_queue_;
    std::unique_ptr<HWQueueMirrorBuffer> hw_queue_mirror_buffer_;
    std::mutex hw_queue_mutex_;
    std::condition_variable hw_queue_full_;
    unsigned long long int last_callback_id_;
    std::unique_ptr<DiskPort> disk_port_;
    std::thread send_request_to_kernel_thread_;
    std::thread receive_answers_from_kernel_thread_;
    std::thread sensors_statistics_process_thread_;
    std::chrono::milliseconds statistic_interval_;
    std::atomic_bool stop_working_;

    /**
     * @brief Return new unique callback_id
     * @return callback_id
     */
    unsigned long long int getNextCallbackID();

    /**
     * @brief write one SolidData to disk, if is not one SolidData in internal queue, infinite waiting occurs
     * @throw localDiskQueueInterruptWaitException
     */
    void waitAndWriteOneSolidData();

    /**
     * @brief Get one answer from kernel
     */
    void waitAndGetOneAnswer();

    /**
     * @brief Main loop for thread
     */
    void sendRequestToKernelThread();

    /**
     * @brief Main loop for thread for receive answers to write requests SolidData from kernel
     */
    void receiveAnswerFromKernelThread();

    /**
     * @brief Process statistics data
     *
     */
    void sensorsProcessingThread();

    /**
     * @brief Calculate sensors statistics by interval and clear internal counter
     * @return SensorReport with statistics
     */
    std::shared_ptr<IReport> calculateSensorsStatistics();


};

#endif //_DISKPERFORMER_H