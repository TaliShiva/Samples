/**
 * Project Gorynych
 * @version 0.1
 */
#define BOOST_LOG_DYN_LINK


#include <boost/log/trivial.hpp>
#include <iostream>


#include "../../include/disk_performer/DiskPerformer.hpp"
#include "../../include/statistics/report/SensorsReport.hpp"


using Clock = std::chrono::system_clock;

DiskPerformer::DiskPerformer(unsigned int atomic_hw_count,
                             unsigned int hw_queue_max,
                             std::unique_ptr<LocalDiskQueue> local_disk_queue,
                             std::unique_ptr<HWQueueMirrorBuffer> hw_queue_mirror_buffer,
                             std::unique_ptr<EntityStatisticsBuffer> statistics_buffer_solid_data,
                             std::unique_ptr<DiskPort> disk_port,
                             std::chrono::milliseconds statistic_interval) :
        atomic_hw_count_(atomic_hw_count),
        hw_queue_max_(hw_queue_max),
        statistics_buffer_solid_data_(std::move(statistics_buffer_solid_data)),
        local_disk_queue_(std::move(local_disk_queue)),
        hw_queue_mirror_buffer_(std::move(hw_queue_mirror_buffer)),
        last_callback_id_(0),
        disk_port_(std::move(disk_port)),
        statistic_interval_(statistic_interval) {
    stop_working_.store(false);
}

DiskPerformer::~DiskPerformer() {
    BOOST_LOG_TRIVIAL(debug) << "DiskPerformer begin destructor";
    shutdown();

    BOOST_LOG_TRIVIAL(debug) << "DiskPerformer end destructor";
}

void DiskPerformer::shutdown() noexcept {
    BOOST_LOG_TRIVIAL(trace) << "DiskPerformer shutdown called";
    // Stop endless loop
    stop_working_.store(true);
    local_disk_queue_->shutdown();
    if (send_request_to_kernel_thread_.joinable()) {
        BOOST_LOG_TRIVIAL(debug) << "DiskPerformer::sendRequestToKernelThread join.";
        send_request_to_kernel_thread_.join();
    }
    disk_port_->shutdown();
    if (receive_answers_from_kernel_thread_.joinable()) {
        BOOST_LOG_TRIVIAL(debug) << "DiskPerformer::receiveAnswerFromKernelThread join.";
        receive_answers_from_kernel_thread_.join();
    }
    if (sensors_statistics_process_thread_.joinable()) {
        BOOST_LOG_TRIVIAL(debug) << "DiskPerformer::sensorsProcessingThread join.";
        sensors_statistics_process_thread_.join();
    }
}

void DiskPerformer::startSendRequestThread() {
    BOOST_LOG_TRIVIAL(debug) << "DiskPerformer::sendRequestToKernelThread start.";

    send_request_to_kernel_thread_ = std::move(std::thread(&DiskPerformer::sendRequestToKernelThread, this));
}

void DiskPerformer::startReceiveResponseThread() {
    BOOST_LOG_TRIVIAL(debug) << "DiskPerformer::receiveAnswerFromKernelThread start.";
    receive_answers_from_kernel_thread_ = std::move(std::thread(&DiskPerformer::receiveAnswerFromKernelThread, this));
}

void DiskPerformer::startSensorsProcessingThread() {
    BOOST_LOG_TRIVIAL(debug) << "DiskPerformer::sensorsProcessingThread start.";
    sensors_statistics_process_thread_ = std::move(std::thread(&DiskPerformer::sensorsProcessingThread, this));
}


void DiskPerformer::waitAndWriteOneSolidData() {
    BOOST_LOG_TRIVIAL(trace) << "DiskPerformer::waitAndWriteOneSolidData wait data";
    std::shared_ptr<SolidData> sold_data = std::move(local_disk_queue_->waitAndPopSolidData());
    BOOST_LOG_TRIVIAL(trace) << "DiskPerformer::waitAndWriteOneSolidData process data";
    atomic_hw_count_++;
    auto start_time = Clock::now();
    unsigned long long int callcbak_id = getNextCallbackID();
    hw_queue_mirror_buffer_->putSolidDataAndCallbackID(HWQueueMirrorElement(start_time, sold_data, callcbak_id));
    disk_port_->asyncWrite(sold_data, callcbak_id);
    if (atomic_hw_count_ >= hw_queue_max_) {
        BOOST_LOG_TRIVIAL(trace) << "DiskPerformer::waitAndWriteOneSolidData wait hw count";
        std::unique_lock<std::mutex> lock(hw_queue_mutex_);
        hw_queue_full_.wait(lock, [this]() { return atomic_hw_count_ < hw_queue_max_; });
    }
}

void DiskPerformer::sendRequestToKernelThread() {
    try {
        while (true) {
            this->waitAndWriteOneSolidData();
        }
    } catch (localDiskQueueInterruptWaitException &e) {
        BOOST_LOG_TRIVIAL(trace) << "Exit DiskPerformer::sendRequestToKernelThread endless loop.";
    }
}

void DiskPerformer::waitAndGetOneAnswer() {
    std::pair<callback_id_type, disk_error_code> answer = disk_port_->waitAndGetAnswer(
            hw_queue_mirror_buffer_->size() <= 1);

    HWQueueMirrorElement mirror_element = std::move(hw_queue_mirror_buffer_->findAndPopByCallbackID(answer.first));
    std::chrono::microseconds request_duration = std::chrono::duration_cast<std::chrono::microseconds>(
            Clock::now() - mirror_element.start_time);
        mirror_element.solid_data_ptr->sendOperationResultCode(answer.second);

    getAnswerFromKernel();
    statistics_buffer_solid_data_->push(
            EntityStatistics(request_duration, mirror_element.solid_data_ptr->getSolidDataSize()));
    atomic_hw_count_--;
    hw_queue_full_.notify_one();
}

void DiskPerformer::receiveAnswerFromKernelThread() {
    try {
        while (true) {
            this->waitAndGetOneAnswer();
        }
    } catch (diskPortInterruptWaitException &e) {
        BOOST_LOG_TRIVIAL(trace) << "Exit DiskPerformer::receiveAnswerFromKernelThread endless loop.";
    }
}

void DiskPerformer::sensorsProcessingThread() {
    std::mutex timer_mutex;
    std::condition_variable timer_cv;
    std::atomic_bool alert(false);
    std::thread timerThread([this, &timer_mutex, &timer_cv, &alert]() {
        auto next_timer_time = std::chrono::steady_clock::now();
        while (!stop_working_.load()) {
            next_timer_time = next_timer_time + this->statistic_interval_;
            auto next = next_timer_time;
            std::this_thread::sleep_until(next);
            alert = true;
            timer_cv.notify_one();
            BOOST_LOG_TRIVIAL(trace) << "DiskPerformer::sensorsProcessingThread timer event.";
        }
    });
    while (!stop_working_.load()) {
        std::unique_lock<std::mutex> lk(timer_mutex);
        timer_cv.wait(lk, [&alert] { return alert.load(); });
        BOOST_LOG_TRIVIAL(trace) << "DiskPerformer::sensorsProcessingThread sending SensorsReport signal.";
        signal_on_sensor_report(std::move(calculateSensorsStatistics()));
        alert = false;
    }
    BOOST_LOG_TRIVIAL(trace) << "DiskPerformer::sensorsProcessingThread timerThread join.";
    timerThread.join();
    BOOST_LOG_TRIVIAL(trace) << "DiskPerformer::sensorsProcessingThread timerThread ended.";
}

std::shared_ptr<IReport> DiskPerformer::calculateSensorsStatistics() {
    auto calc = [this](const std::vector<EntityStatistics> &buff) -> std::pair<std::chrono::microseconds, size_t> {
        size_t solid_data_total_size = 0;
        size_t solid_data_avg_size = 0;
        std::chrono::microseconds solid_data_sum_time = std::chrono::microseconds::zero();
        std::chrono::microseconds solid_data_avg_time = std::chrono::microseconds::zero();
        if (!buff.empty()) {
            for (auto &element: buff) {
                solid_data_total_size += element.size;
                solid_data_sum_time += element.time_duration;
            }
            solid_data_avg_time = solid_data_sum_time / buff.size();
            solid_data_avg_size = solid_data_total_size / buff.size();
        }
        return {solid_data_avg_time, solid_data_avg_size};
    };

    auto event_time = std::chrono::system_clock::now();
    auto solid_data_statistics_buffer = statistics_buffer_solid_data_->getCopyAndClear();
    auto solid_data_chain_statistics_buffer = local_disk_queue_->solid_data_chain_statistics_buffer_->getCopyAndClear();
    auto sd_result = calc(solid_data_statistics_buffer);
    auto sdc_result = calc(solid_data_statistics_buffer);
    return std::move(std::shared_ptr<IReport>(new SensorsReport(solid_data_statistics_buffer.size(),
                                                                solid_data_statistics_buffer.size(),
                                                                sd_result.second,
                                                                sdc_result.second,
                                                                sd_result.first.count(),
                                                                sdc_result.first.count(),
                                                                event_time
    )));

}

void DiskPerformer::pushSolidDataChain(std::shared_ptr<SolidDataChain> solidDataChain) {
    local_disk_queue_->putSolidDataChainInQueue(std::move(solidDataChain));
}

void DiskPerformer::waitUntilReadyToReceive() {
    local_disk_queue_->waitUntilReadyToReceive();
}

unsigned long long int DiskPerformer::getNextCallbackID() {
    if (last_callback_id_ == ULLONG_MAX) {
        last_callback_id_ = 0;
        BOOST_LOG_TRIVIAL(trace) << "ULLONG_MAX reached for callback_id, atrt from 0";
    } else {
        last_callback_id_++;
    }
    BOOST_LOG_TRIVIAL(trace) << "Next id: " << last_callback_id_;
    return last_callback_id_;

}