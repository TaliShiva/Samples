/**
 * Project Gorynych
 * @version 0.1
 */


#include "../../../include/statistics/report/StartReport.hpp"


StartReport::StartReport(const std::chrono::system_clock::time_point &start_time) : start_time(start_time) {}


std::string StartReport::serializeToString() {
    gorynych::protobuf::Report protobuf_report;
    protobuf_report.set_type(gorynych::protobuf::Report::REPORT_START);
    protobuf_report.mutable_report_start()->set_start_time(
            std::chrono::time_point_cast<std::chrono::microseconds>(start_time).time_since_epoch().count());
    if (!protobuf_report.IsInitialized()) {
        throw std::runtime_error("Protobuf object not initialized");
    }
    return protobuf_report.SerializeAsString();
}
