//

#include "../../include/responses/remove_disk_from_scst_worker_response.hpp"
namespace gorynych {
    namespace workers {
        RemoveDiskFromScstWorkerResponse::RemoveDiskFromScstWorkerResponse(const bool success,
                                                                           const std::string &systemErrorMessage,
                                                                           const std::string &programmerErrorMessage)
                : AbstractWorkerResponse(success,
                                         systemErrorMessage,
                                         programmerErrorMessage) {

        }

    }
}

