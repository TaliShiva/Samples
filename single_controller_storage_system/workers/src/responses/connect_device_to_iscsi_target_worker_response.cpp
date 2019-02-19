//
// Created by dumplings on 15.03.17.
//
#include "../../include/responses/connect_device_to_iscsi_target_worker_response.hpp"

namespace gorynych {
    namespace workers {
        ConnectDeviceToIscsiTargetWorkerResponse::ConnectDeviceToIscsiTargetWorkerResponse(bool success,
                                                                                   const std::string &systemErrorMessage,
                                                                                   const std::string &logicErrorMessage)
                : AbstractWorkerResponse(success, systemErrorMessage,
                                         logicErrorMessage) {

        }

    }
}