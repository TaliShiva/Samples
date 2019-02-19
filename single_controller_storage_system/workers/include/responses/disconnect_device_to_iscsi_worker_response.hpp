#pragma once


#include "abstract_worker_response.hpp"

namespace gorynych{
    namespace workers{
        class DisconnectDeviceToIscsiTargetWorkerResponse : public AbstractWorkerResponse{
        public:
            DisconnectDeviceToIscsiTargetWorkerResponse(bool success ,
                                                                    const std::string &systemErrorMessage = "",
                                                                    const std::string &logicErrorMessage = "");
        };
    }
}