#pragma once

#include "abstract_worker_response.hpp"

namespace gorynych {
    namespace workers {
        class EnableIscsiTargetWorkerResponse : public AbstractWorkerResponse {
        public:


            EnableIscsiTargetWorkerResponse(bool success, const std::string &systemErrorMessage = "",
                                            const std::string &logicErrorMessage = "");
        };
    }
}


