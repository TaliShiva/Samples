#pragma once

#include "iworker_response.hpp"

#include <string>

namespace gorynych {
    namespace workers {
        class AbstractWorkerResponse : public IWorkerResponse {
        public:
            AbstractWorkerResponse(const bool success,
                                   const std::string systemErrorMessage,
                                   const std::string logicErrorMessage);

        protected:
            const bool success_;
            const std::string systemErrorMessage_;
            const std::string programmerErrorMessage_;
        public:
            const bool isSuccess() const;
            const std::string systemErrorMessage() const;
            const std::string programmerErrorMessage() const;

        };

    }
}



