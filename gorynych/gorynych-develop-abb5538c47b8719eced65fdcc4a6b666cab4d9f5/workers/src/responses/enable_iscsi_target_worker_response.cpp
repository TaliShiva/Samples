//
// Created by oleg on 21.03.17.
//

#include "../../include/responses/enable_iscsi_target_worker_response.hpp"

namespace gorynych {
    namespace workers {

        EnableIscsiTargetWorkerResponse::EnableIscsiTargetWorkerResponse(bool success,
                                                                         const std::string &systemErrorMessage,
                                                                         const std::string &logicErrorMessage)
                : AbstractWorkerResponse(success, systemErrorMessage,
                                         logicErrorMessage) {

        }



    }
}
