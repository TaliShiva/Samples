//
// Created by alex on 3/13/17.
//

#include "../../include/responses/create_lvm_worker_response.hpp"

namespace gorynych {
    namespace workers {

        CreateLvmWorkerResponse::CreateLvmWorkerResponse(const bool success, const std::string &systemErrorMessage,
                                                         const std::string &logicErrorMessage) : AbstractWorkerResponse(
                success, systemErrorMessage, logicErrorMessage) {}
    }
}