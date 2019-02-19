#pragma once
#include "abstract_worker_response.hpp"
namespace gorynych {
    namespace workers {
        class RemoveDiskFromScstWorkerResponse : public AbstractWorkerResponse {
        public:
            /**
             * @see documentation AbstractWorkerResponse
             * @param success
             * @param systemErrorMessage
             * @param programmerErrorMessage
             */
            RemoveDiskFromScstWorkerResponse(const bool success,
                                             const std::string &systemErrorMessage = "",
                                             const std::string &programmerErrorMessage = "");

        };
    }
}




