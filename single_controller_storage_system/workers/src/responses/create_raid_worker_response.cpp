//
// Created by user on 13.03.17.
//

#include "../../include/responses/create_raid_worker_response.hpp"

namespace gorynych {
    namespace workers {

        CreateRaidWorkerResponse::CreateRaidWorkerResponse(const bool success, const std::string &systemErrorMessage,
                                                           const std::string &logicErrorMessage)
                : AbstractWorkerResponse(success, systemErrorMessage,
                                         logicErrorMessage) {}
    }
}