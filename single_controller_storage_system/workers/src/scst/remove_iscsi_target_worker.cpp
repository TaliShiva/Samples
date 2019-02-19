//
// Created by boa on 13.03.17.
//

#include "../../include/scst/remove_iscsi_target_worker.hpp"
#include "../../include/responses/remove_iscsi_target_worker_response.hpp"

namespace gorynych{
    namespace workers{

        RemoveIscsiTargetWorker::RemoveIscsiTargetWorker(const unsigned int id,
                                                         const RemoveIscsiTargetWorkerCommand &command)
                : AbstractScstWorker(id, WORKER_TYPE::REMOVE_ISCSI_TARGET_WORKER), command_(command){

        }

        IWorkerResponse &RemoveIscsiTargetWorker::doWork() {
            RemoveIscsiTargetWorkerResponse *response;
            if(writeToSysFs(iscsiManagementPath_,generateStringFromRemoveTargetCommand())) {
                response = new RemoveIscsiTargetWorkerResponse(true);
            } else {
                response = new RemoveIscsiTargetWorkerResponse(false, generateSystemErrorMessage(),
                                                               generateProgrammerErrorMessage());
            }
            return *response;
        }

        void RemoveIscsiTargetWorker::sendNotification() {

        }

        const std::string RemoveIscsiTargetWorker::generateStringFromRemoveTargetCommand() {
            auto magicString = "del_target ";
            return magicString + command_.targetName();
        }

        const std::string RemoveIscsiTargetWorker::generateProgrammerErrorMessage() {
            lastProgrammerError_ = "RemoveIscsiTargetWorker: cannot remover target: " + command_.targetName();
            return lastProgrammerError_;
        }

        const std::string RemoveIscsiTargetWorker::generateSystemErrorMessage() {
            lastSystemError_ = "Error write to sysfs: " + writeToSysFsError_;
            return lastSystemError_;
        }
    }
}
