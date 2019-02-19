/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _STARTREPORT_H
#define _STARTREPORT_H

#include <chrono>
#include <string>
#include "IReport.hpp"
#include "../../../cmake-build-debug/report.pb.h"


class StartReport : public IReport {
public:
    std::chrono::system_clock::time_point start_time;

    explicit StartReport(const std::chrono::system_clock::time_point &start_time);

    /**
     * 
     * @brief Convert Report to Protobuf-coded data
     * @return Protobuf-coded data
     */
    std::string serializeToString() override ;
};

#endif //_STARTREPORT_H