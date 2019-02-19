//
// Created by alex on 3/13/17.
//

#pragma once

#include "abstract_worker_response.hpp"

namespace gorynych {
    namespace workers {
        /**
         * Класс ответа от Worker'a @see class CreateLvmWorker
         */
        class CreateLvmWorkerResponse : public AbstractWorkerResponse {
        public:
            CreateLvmWorkerResponse(const bool success, const std::string &systemErrorMessage = "",
                                    const std::string &logicErrorMessage = "");
        };

    }
}

