#include "../../include/responses/add_disk_to_scst_worker_response.hpp"

namespace gorynych {
    namespace workers {

        AddDiskToScstWorkerResponse::AddDiskToScstWorkerResponse(const bool success,
                                                                 const std::string &systemErrorMessage,
                                                                 const std::string &logicErrorMessage)
                : AbstractWorkerResponse(success, systemErrorMessage,
                                         logicErrorMessage) {

        }
    }
}
