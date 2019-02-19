
//

#include "../../include/responses/destroy_lvm_worker_response.hpp"

namespace gorynych {
    namespace workers {
        DestroyLvmWorkerResponse::DestroyLvmWorkerResponse(bool success,
                                                           const std::string &systemErrorMessage,
                                                           const std::string &logicErrorMessage)
                : AbstractWorkerResponse(success,
                                         systemErrorMessage, logicErrorMessage) {

        }
    }
}