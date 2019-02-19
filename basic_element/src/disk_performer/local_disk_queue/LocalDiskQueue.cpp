/**
 * Project Gorynych
 * @version 0.1
 */


#include "../../../include/disk_performer/local_disk_queue/LocalDiskQueue.hpp"

using Clock = std::chrono::steady_clock;

LocalDiskQueue::LocalDiskQueue(std::shared_ptr<EntityStatisticsBuffer> &&solid_data_chain_statistics_buffer,
                               unsigned int min_level_size,
                               unsigned int max_level_size) :
        min_level_size(min_level_size),
        max_level_size(max_level_size),
        solid_data_chain_statistics_buffer_(std::move(solid_data_chain_statistics_buffer)) {
    if (min_level_size >= max_level_size) {
        throw std::logic_error("min level must be less than max level!");
    }
    stop_working_.store(false);
    min_level_flag = local_disk_queue_elements_.size() <= min_level_size;
    max_level_flag = local_disk_queue_elements_.size() > max_level_size;
    receive_next_flag = false;
    front_solid_data_chain_size_ = 0;
}

std::shared_ptr<SolidData> LocalDiskQueue::waitAndPopSolidData() {
    std::unique_lock<std::mutex> queue_lock(queue_mutex_);
    BOOST_LOG_TRIVIAL(debug) << "LocalDiskQueue::waitAndPopSolidData queue_not_empty_ wait";
    queue_not_empty_.wait(queue_lock, [this] { return !local_disk_queue_elements_.empty() || (this->stop_working_ && local_disk_queue_elements_.empty()); });
    if(stop_working_ && local_disk_queue_elements_.empty()) {
        BOOST_LOG_TRIVIAL(debug) << "LocalDiskQueue::waitAndPopSolidData interrupt";
        throw localDiskQueueInterruptWaitException();
    }
        BOOST_LOG_TRIVIAL(debug) << "LocalDiskQueue::waitAndPopSolidData queue_not_empty_ wait after";
        if (local_disk_queue_elements_.front().solid_datas_it ==
            local_disk_queue_elements_.front().solid_data_chain->solid_datas.begin()) {
            start_time_on_front_solid_data_chain = Clock::now();
        }
        std::shared_ptr<SolidData> sd = *local_disk_queue_elements_.front().solid_datas_it;
        for (const auto &da: sd->data_atoms) {
            front_solid_data_chain_size_ += da->physical_region.disk_length;
        }
        if (local_disk_queue_elements_.front().solid_datas_it ==
            std::prev(local_disk_queue_elements_.front().solid_data_chain->solid_datas.end())) {
            local_disk_queue_elements_.pop_front();
            receive_next_flag = true;
            receive_next_chain_.notify_one();
            if (local_disk_queue_elements_.size() < min_level_size && !min_level_flag) {
                min_level_flag = true;
                sig_min_level_below();
            } else if (local_disk_queue_elements_.size() <= max_level_size && max_level_flag) {
                max_level_flag = false;
                sig_max_level_below();
            }
            std::chrono::microseconds execution_time = std::chrono::duration_cast<std::chrono::microseconds>(
                    start_time_on_front_solid_data_chain - Clock::now());
            BOOST_LOG_TRIVIAL(debug)
                << "LocalDiskQueue::waitAndPopSolidData solid_data_chain_statistics_buffer_->push wait";
            solid_data_chain_statistics_buffer_->push(EntityStatistics(execution_time, front_solid_data_chain_size_));
            front_solid_data_chain_size_ = 0;
        } else {
            local_disk_queue_elements_.front().solid_datas_it++;
        }
        BOOST_LOG_TRIVIAL(debug) << "LocalDiskQueue::waitAndPopSolidData end";
        return sd;

}

void LocalDiskQueue::putSolidDataChainInQueue(std::shared_ptr<SolidDataChain> solid_data_chain) {
    if(stop_working_) {
        throw localDiskQueueShutdownInvalidException();
    }
    std::lock_guard<std::mutex> lock(queue_mutex_);
    local_disk_queue_elements_.emplace_back(solid_data_chain);
    receive_next_flag = false;
    BOOST_LOG_TRIVIAL(debug) << "LocalDiskQueue::putSolidDataChainInQueue before notify size:"
                             << local_disk_queue_elements_.size();
    queue_not_empty_.notify_one();
    if (local_disk_queue_elements_.size() >= min_level_size && min_level_flag) {
        min_level_flag = false;
        sig_min_level_above();
    } else if (local_disk_queue_elements_.size() > max_level_size && !max_level_flag) {
        max_level_flag = true;
        sig_max_level_above();
    }
}

void LocalDiskQueue::waitUntilReadyToReceive() {
    if (!min_level_flag) {
        std::unique_lock<std::mutex> solid_data_chain_lock(receive_next_mutex_);
        receive_next_chain_.wait(solid_data_chain_lock, [this] { return receive_next_flag == true; });
    }
}

void LocalDiskQueue::shutdown() noexcept {
    BOOST_LOG_TRIVIAL(trace) << "LocalDiskQueue shutdown called";
    // Stop endless loop
    stop_working_.store(true);
    queue_not_empty_.notify_one();
}
