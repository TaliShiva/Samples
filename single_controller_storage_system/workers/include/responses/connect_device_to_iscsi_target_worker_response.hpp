//
// Created by dumplings on 15.03.17.
//
#pragma once

#include "abstract_worker_response.hpp"

namespace gorynych {
    namespace workers {
        class ConnectDeviceToIscsiTargetWorkerResponse : public AbstractWorkerResponse {
        public:
            ConnectDeviceToIscsiTargetWorkerResponse(bool success, const std::string &systemErrorMessage = "",
                                                 const std::string &logicErrorMessage = "");
        };
    }
}