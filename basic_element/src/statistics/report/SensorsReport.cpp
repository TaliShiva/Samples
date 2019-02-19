/**
 * Project Gorynych
 * @version 0.1
 */


#include "../../../include/statistics/report/SensorsReport.hpp"


SensorsReport::SensorsReport(unsigned long sd_count,
                             unsigned long sd_chain_count,
                             unsigned long average_size_sd,
                             unsigned long average_size_sd_chain,
                             unsigned long average_latency_sd,
                             unsigned long average_latency_sd_chain,
                             const std::chrono::system_clock::time_point &timestamp)
        : sd_count(sd_count),
          sd_chain_count(sd_chain_count),
          average_size_sd(average_size_sd),
          average_size_sd_chain(average_size_sd_chain),
          average_latency_sd(average_latency_sd),
          average_latency_sd_chain(average_latency_sd_chain),
          timestamp(timestamp) {}

std::string SensorsReport::serializeToString() {
    gorynych::protobuf::Report protobuf_report;
    protobuf_report.set_type(gorynych::protobuf::Report::REPORT_STATISTICS);
    protobuf_report.mutable_report_statistics()->set_sd_count(sd_count);
    protobuf_report.mutable_report_statistics()->set_sd_chain_count(sd_chain_count);
    protobuf_report.mutable_report_statistics()->set_average_size_sd(average_size_sd);
    protobuf_report.mutable_report_statistics()->set_average_size_sd_chain(average_size_sd_chain);
    protobuf_report.mutable_report_statistics()->set_average_latency_sd(average_latency_sd);
    protobuf_report.mutable_report_statistics()->set_average_latency_sd_chain(average_latency_sd_chain);
    protobuf_report.mutable_report_statistics()->set_timestamp(
            std::chrono::time_point_cast<std::chrono::microseconds>(timestamp).time_since_epoch().count());

    if (!protobuf_report.IsInitialized()) {
        throw std::runtime_error("Protobuf object not initialized");
    }
    return protobuf_report.SerializeAsString();
}

