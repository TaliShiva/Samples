#pragma once
#include "abstract_worker_response.hpp"

namespace gorynych {
    namespace workers {
        /**
         * @see documentation for AbstractWorkerResponse
         */
        class CreateTargetWorkerResponse : public AbstractWorkerResponse {
        public:
            /**
             *
             * @param success
             * @param systemErrorMessage
             * @param logicErrorMessage
             */
            CreateTargetWorkerResponse(bool success, const std::string &systemErrorMessage = "",
                                       const std::string &logicErrorMessage = "");

        };

    }
}



