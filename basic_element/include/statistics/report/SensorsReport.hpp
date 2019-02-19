/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _SENSORSREPORT_H
#define _SENSORSREPORT_H

#include <chrono>
#include <string>

#include "IReport.hpp"
#include "../../../cmake-build-debug/report.pb.h"


class SensorsReport : public IReport {
public:
    unsigned long int sd_count;
    unsigned long int sd_chain_count;
    unsigned long int average_size_sd;
    unsigned long int average_size_sd_chain;
    unsigned long int average_latency_sd;
    unsigned long int average_latency_sd_chain;
    std::chrono::system_clock::time_point timestamp;

    SensorsReport(unsigned long sd_count,
                  unsigned long sd_chain_count,
                  unsigned long int average_size_sd,
                  unsigned long int average_size_sd_chain,
                  unsigned long int average_latency_sd,
                  unsigned long int average_latency_sd_chain,
                  const std::chrono::system_clock::time_point &timestamp);
    
    /**
     * 
     * @brief Convert Report to Protobuf-coded data
     * @return Protobuf-coded data
     */
    std::string serializeToString() override;

};

#endif //_SENSORSREPORT_H