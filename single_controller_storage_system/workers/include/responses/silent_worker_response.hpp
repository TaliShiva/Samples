#pragma once

#include "abstract_worker_response.hpp"

namespace gorynych {
    namespace workers {

        class SilentWorkerResponse: public AbstractWorkerResponse {
        public:
            SilentWorkerResponse(const bool success,
                                 const std::string systemErrorMessage,
                                 const std::string logicErrorMessage):
                    AbstractWorkerResponse(success, systemErrorMessage, logicErrorMessage) {

            }
        };
    };
}