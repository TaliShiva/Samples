//

#pragma once

#include "abstract_worker_response.hpp"

namespace gorynych {
    namespace workers {
        class DisableIscsiTargetWorkerResponse : public AbstractWorkerResponse {
        public:
            DisableIscsiTargetWorkerResponse(const bool success,
                                             const std::string &systemErrorMessage = "",
                                             const std::string &logicErrorMessage = "")
                    : AbstractWorkerResponse(success,
                                             systemErrorMessage,logicErrorMessage) {}
        };
    }
}