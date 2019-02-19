/**
 * Project Gorynych
 * @version 0.1
 */


#include "../../../include/statistics/report/StopReport.hpp"


StopReport::StopReport(const std::chrono::system_clock::time_point &stop_time) : stop_time(stop_time) {}

std::string StopReport::serializeToString() {
    gorynych::protobuf::Report protobuf_report;
    protobuf_report.set_type(gorynych::protobuf::Report::REPORT_STOP);
    protobuf_report.mutable_report_stop()->set_stop_time(
            std::chrono::time_point_cast<std::chrono::microseconds>(stop_time).time_since_epoch().count());
    if (!protobuf_report.IsInitialized()) {
        throw std::runtime_error("Protobuf object not initialized");
    }
    return protobuf_report.SerializeAsString();
}
