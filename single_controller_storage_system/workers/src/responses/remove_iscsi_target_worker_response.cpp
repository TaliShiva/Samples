//
// Created by boa on 13.03.17.
//

#include "../../include/responses/remove_iscsi_target_worker_response.hpp"
namespace gorynych{
    namespace workers{

        RemoveIscsiTargetWorkerResponse::RemoveIscsiTargetWorkerResponse(const bool success,
                                                                         const std::string &systemErrorMessage,
                                                                         const std::string &programmerErrorMessage)
                : AbstractWorkerResponse(success, systemErrorMessage,
                                         programmerErrorMessage) {

        }
    }
}