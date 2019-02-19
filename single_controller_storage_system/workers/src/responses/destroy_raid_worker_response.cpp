//
// Created by user on 15.03.17.
//

#include "../../include/responses/destroy_raid_worker_response.hpp"

namespace gorynych {
    namespace workers {
        DestroyRaidWorkerResponse::DestroyRaidWorkerResponse(const bool success, const std::string &systemErrorMessage,
                                                             const std::string &logicErrorMessage)
                : AbstractWorkerResponse(success, systemErrorMessage,
                                         logicErrorMessage) {}
    }
}