//
//

#pragma once
#include "abstract_worker_response.hpp"
namespace gorynych {
    namespace workers {
    /**
     * Класс ответа от Worker'a @see class DeleteLogicalVolumeWorker
     */
    class DeleteLogicalVolumeWorkerResponse : public AbstractWorkerResponse {
    public:
        DeleteLogicalVolumeWorkerResponse(const bool success, const std::string &systemErrorMessage = "",
                                const std::string &logicErrorMessage = "");
        };

    }
}

