#include "../../include/responses/create_target_worker_response.hpp"

namespace gorynych {
    namespace workers {

        CreateTargetWorkerResponse::CreateTargetWorkerResponse(bool success,
                                                               const std::string &systemErrorMessage,
                                                               const std::string &logicErrorMessage)
                : AbstractWorkerResponse(success, systemErrorMessage, logicErrorMessage) { }
    }
}
