/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _REPORTQUEUE_H
#define _REPORTQUEUE_H

#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include "IReport.hpp"

class StopReceptionException : public std::exception {};
class StopPushException : public std::exception {};

class ReportQueue {
public:
    ReportQueue() = default;

    /**
     *
     * @return
     * @throw StopReceptionException
     */
    std::shared_ptr<IReport> wait_and_pop();

    /**
     *
     * @param report
     * @throw StopPushException
     */
    void push(std::shared_ptr<IReport> report);

    bool empty() const;
    size_t size() const;

    void shutdown();

private:
    std::queue<std::shared_ptr<IReport>> queue_;
    mutable std::mutex mutex_;
    std::condition_variable condition_variable_for_wait_and_pop_;

    std::atomic_bool stop_reception_flag{false};


};

#endif //_REPORTQUEUE_H