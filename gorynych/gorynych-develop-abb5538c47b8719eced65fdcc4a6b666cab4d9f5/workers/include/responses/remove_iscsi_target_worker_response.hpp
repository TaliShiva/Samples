#pragma once

#include "abstract_worker_response.hpp"

namespace gorynych{
    namespace workers{
        /**
         * @class RemoveIscsiTargetWorkerResponse
         * @see documentation AbstractWorkerResponse
         */
        class RemoveIscsiTargetWorkerResponse : public AbstractWorkerResponse {
        public:
            RemoveIscsiTargetWorkerResponse(const bool success,
                                            const std::string &systemErrorMessage = "",
                                            const std::string &programmerErrorMessage = "");

        };
    }
}

