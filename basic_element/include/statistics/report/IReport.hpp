/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _IREPORT_H
#define _IREPORT_H

#include <string>

#include "../../../cmake-build-debug/report.pb.h"

/**
 * Interface for any report send via ExternalStatistics class
 */
class IReport {
public:
    IReport() = default;

    virtual std::string serializeToString() = 0;

    virtual ~IReport() = default;
};

#endif //_IREPORT_H