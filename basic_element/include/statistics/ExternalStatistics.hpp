/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _EXTERNALSTATISTICS_H
#define _EXTERNALSTATISTICS_H

#include <memory>
#include <deque>
#include <thread>
#include <boost/asio.hpp>
#include <gtest/gtest_prod.h>

#include "report/IReport.hpp"
#include "report/ReportQueue.hpp"

/**
 * Manage Reports(interface IReport), Accept and store and send via UNIX-socket
 *
 */
class ExternalStatistics {
public:

    explicit ExternalStatistics(const std::string &socket_path,
                                std::unique_ptr<ReportQueue> report_queue = std::unique_ptr<ReportQueue>(
                                        new ReportQueue));

    ExternalStatistics(const ExternalStatistics &) = delete;

    ExternalStatistics &operator=(const ExternalStatistics &) = delete;

    ExternalStatistics(ExternalStatistics &&) = default;

    ExternalStatistics &operator=(ExternalStatistics &&) = default;

    /**
     * @brief Put Report to internal queue
     * @param report Report for store
     * @remarks
     * This method thread-safe
     */
    void slotProcessReport(std::shared_ptr<IReport> report);

    /**
     * @brief Connect to socket and send all Report element from internal queue in endless loop
     * Never return
     * @remarks
     * This method thread-safe
     * @todo add kill_thread feature
     */
    void connectAndStartSendingLoop();



    /**
     * @brief Start new thread with socketThread method within
     * @see ExternalStatistics#socketThread
     */
    void startSendingToSocketThread();

    ~ExternalStatistics();

    /**
     *
     */
    void shutdown();

private:
    FRIEND_TEST(ExternalStatisticsTest, correctSlotProcessReport);
    FRIEND_TEST(ExternalStatisticsTest, correctWaitOnEmptyInternalQueue);
    FRIEND_TEST(KillableThreadOfExternalStatisticsTests, correctProcessingOfQueueAfterStop);
    FRIEND_TEST(KillableThreadOfExternalStatisticsTests, CorrectThreadStop);
    FRIEND_TEST(KillableThreadOfExternalStatisticsTests, CorrectHandlingOfPushWithStoppedThread);

    const std::string socket_path_;
    std::unique_ptr<ReportQueue> report_queue_;
    std::thread send_thread_;
    boost::asio::io_service ioservice_;
    boost::asio::local::stream_protocol::endpoint endpoint_;
    boost::asio::local::stream_protocol::socket socket_;
    std::atomic_bool stop_thread_flag;

    /**
     * @brief Send one report to UNIX-socket
     */
    void sendOneReport();
    /**
     * @brief Connect to socket
     */
    void connectToSocket();


};

#endif //_EXTERNALSTATISTICS_H