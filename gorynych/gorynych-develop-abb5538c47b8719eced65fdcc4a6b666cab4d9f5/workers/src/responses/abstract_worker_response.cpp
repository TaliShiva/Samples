
#include "../../include/responses/abstract_worker_response.hpp"

namespace gorynych {
    namespace workers {

        AbstractWorkerResponse::AbstractWorkerResponse(const bool success,
                                                       const std::string systemErrorMessage = "",
                                                       const std::string logicErrorMessage = "") :
                success_(success),
                systemErrorMessage_(systemErrorMessage),
                programmerErrorMessage_(logicErrorMessage) {

        }

        const bool AbstractWorkerResponse::isSuccess() const {
            return success_;
        }

        const std::string AbstractWorkerResponse::systemErrorMessage() const {
            return systemErrorMessage_;
        }

        const std::string AbstractWorkerResponse::programmerErrorMessage() const {
            return programmerErrorMessage_;
        }
    }
}
