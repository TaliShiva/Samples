
//

#pragma once

#include "abstract_worker_response.hpp"

namespace gorynych {
    namespace workers {
        class DestroyLvmWorkerResponse : public AbstractWorkerResponse {
        public:
            DestroyLvmWorkerResponse(bool success, const std::string &systemErrorMessage = "",
                                     const std::string &logicErrorMessage = "");
        };
    }
}


