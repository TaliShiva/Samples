//
//

#include "../../include/responses/delete_logical_volume_worker_response.hpp"

namespace gorynych {
    namespace workers {

        DeleteLogicalVolumeWorkerResponse::DeleteLogicalVolumeWorkerResponse(const bool success, const std::string &systemErrorMessage,
                                                         const std::string &logicErrorMessage) : AbstractWorkerResponse(
                success, systemErrorMessage, logicErrorMessage) {}
    }
}