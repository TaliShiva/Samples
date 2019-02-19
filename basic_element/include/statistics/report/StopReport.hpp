/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _STOPREPORT_H
#define _STOPREPORT_H

#include <chrono>

#include "IReport.hpp"
#include "../../../cmake-build-debug/report.pb.h"


class StopReport : public IReport {
public:
    std::chrono::system_clock::time_point stop_time;

    explicit StopReport(const std::chrono::system_clock::time_point &stop_time);

    /**
     * 
     * @brief Convert Report to Protobuf-coded data
     * @return Protobuf-coded data
     */
    std::string serializeToString() override;
};

#endif //_STOPREPORT_H