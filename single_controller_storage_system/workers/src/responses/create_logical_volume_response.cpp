
#include "../../include/responses/create_logical_volume_response.hpp"

namespace gorynych {
    namespace workers {

        CreateLogicalVolumeWorkerResponse::CreateLogicalVolumeWorkerResponse(const bool success,
                                                                             const std::string &systemErrorMessage,
                                                                             const std::string &logicErrorMessage)
                : AbstractWorkerResponse(success, systemErrorMessage,
                                         logicErrorMessage) {}
    }
}