#pragma once
#include "abstract_worker_response.hpp"

namespace gorynych {
    namespace workers {
        class CreateRaidWorkerResponse : public AbstractWorkerResponse{
        public:
            /**
             * @param success - результат выполнения worker-а
             * @param systemErrorMessage - сообщение об ошибке от системы
             * @param logicErrorMessage  - сообщение об ошибке от программиста
             */
            CreateRaidWorkerResponse(const bool success, const std::string &systemErrorMessage = "",
                                                 const std::string &logicErrorMessage = "");

        };
    }
}