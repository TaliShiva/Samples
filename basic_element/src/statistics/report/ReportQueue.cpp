/**
 * Project Gorynych
 * @version 0.1
 */

#define BOOST_LOG_DYN_LINK

#include <boost/log/trivial.hpp>

#include "../../../include/statistics/report/ReportQueue.hpp"

std::shared_ptr<IReport> ReportQueue::wait_and_pop() {
    std::unique_lock<std::mutex> lock(mutex_);
    condition_variable_for_wait_and_pop_.wait(lock, [this]() { return !queue_.empty() || stop_reception_flag; });
    if (queue_.empty() && stop_reception_flag) {
        throw StopReceptionException();
    }
    auto result = std::move(queue_.front());
    queue_.pop();
    return result;
}

void ReportQueue::push(std::shared_ptr<IReport> report) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (stop_reception_flag) {
        throw StopPushException();
    }
    queue_.push(std::move(report));
    condition_variable_for_wait_and_pop_.notify_one();
}

bool ReportQueue::empty() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.empty();
}

size_t ReportQueue::size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.size();
}

void ReportQueue::shutdown() {
    BOOST_LOG_TRIVIAL(trace) << "ReportQueue shutdown called";
    stop_reception_flag.store(true);
    condition_variable_for_wait_and_pop_.notify_one();
}
