#include "../../include/responses/disconnect_device_to_iscsi_worker_response.hpp"

namespace gorynych{
    namespace workers{

        DisconnectDeviceToIscsiTargetWorkerResponse::DisconnectDeviceToIscsiTargetWorkerResponse(bool success,
                                                                                                 const std::string &systemErrorMessage,
                                                                                                 const std::string &logicErrorMessage)
                : AbstractWorkerResponse(success, systemErrorMessage, logicErrorMessage) {

        }
    }
}
