#include "../../include/scst/disable_iscsi_target_worker.hpp"

namespace gorynych {
    namespace workers {
        DisableIscsiTargetWorker::DisableIscsiTargetWorker(const unsigned int id,
                                                           const DisableIscsiTargetWorkerCommand &command)
                : AbstractScstWorker(id, WORKER_TYPE::DISABLE_ISCSI_TARGET_WORKER), command_(command)  {

        }

        DisableIscsiTargetWorkerResponse &DisableIscsiTargetWorker::doWork() {
            if (writeToSysFs(generatePathForDisableTargetCommand(),std::to_string(0))) {
                return *new DisableIscsiTargetWorkerResponse(true);
            } else {
                return *new DisableIscsiTargetWorkerResponse(false, generateSystemErrorMessage(),
                                                             generateProgrammerErrorMessage());
            }
        }

        void DisableIscsiTargetWorker::sendNotification() {

        }

        const std::string DisableIscsiTargetWorker::generateSystemErrorMessage() {
            return "DisableIscsiTargetWorker system error\n";
        }

        const std::string DisableIscsiTargetWorker::generateProgrammerErrorMessage() {
            return "\nваше гавно не работает\n";
        }


        const std::string DisableIscsiTargetWorker::generatePathForDisableTargetCommand() const {
            auto pathSuffix = "/enabled";
            return iscsiTargetsPathPrefix_ + command_.targetName() + pathSuffix;

        }

    }
}
