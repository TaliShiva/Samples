//
// Created by oleg on 21.03.17.
//

#include "../../include/scst/enable_iscsi_target_worker.hpp"
namespace gorynych {
    namespace workers {

        EnableIscsiTargetWorker::EnableIscsiTargetWorker(const unsigned int id,
                                                         const EnableIscsiTargetWorkerCommand &command)
                : AbstractScstWorker(id, WORKER_TYPE::ENABLE_ISCSI_TARGET_WORKER), command_(command) {

        }

        void EnableIscsiTargetWorker::sendNotification() {

        }
        EnableIscsiTargetWorkerResponse &EnableIscsiTargetWorker::doWork(){
            EnableIscsiTargetWorkerResponse *response;
            if (writeToSysFs( generatePathForEnableIscsiTargetCommand(),std::to_string(1))){
                response = new EnableIscsiTargetWorkerResponse(true);
            } else {
                response = new EnableIscsiTargetWorkerResponse(false, "unknown error", "cannot create target");
            }
            return *response;

        }

        const std::string EnableIscsiTargetWorker::generateSystemErrorMessage() {
            return "EnableIscsiTargetWorker : System Error";
        }

        const std::string EnableIscsiTargetWorker::generateProgrammerErrorMessage() {
            return "EnableIscsiTargetWorker : Vse ochen' ploho";
        }
    }
}
