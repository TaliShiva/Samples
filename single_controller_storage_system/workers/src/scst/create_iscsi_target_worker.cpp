#include "../../include/scst/create_iscsi_target_worker.hpp"

namespace gorynych {
    namespace workers {
        CreateIscsiTargetWorker::CreateIscsiTargetWorker(const unsigned int id,
                                                         const CreateTargetWorkerCommand &command)
                : AbstractScstWorker(id, WORKER_TYPE::CREATE_ISCSI_TARGET_WORKER), command_(command) {
        }

        CreateTargetWorkerResponse &CreateIscsiTargetWorker::doWork() {
            CreateTargetWorkerResponse *response;
            if (writeToSysFs(iscsiManagementPath_, generateStringForCreateTargetCommand())) {
                response = new CreateTargetWorkerResponse(true);
            } else {
                response = new CreateTargetWorkerResponse(false, "unknown error", "cannot create target");
            }
            return *response; //FIXME заменить на shared_pointer
        }

        void CreateIscsiTargetWorker::sendNotification() {

        }

        const std::string CreateIscsiTargetWorker::generateStringForCreateTargetCommand() {
            auto magicString = "add_target ";
            return magicString + command_.targetName();
        }

        const std::string CreateIscsiTargetWorker::generateSystemErrorMessage() {
            return "";
        }

        const std::string CreateIscsiTargetWorker::generateProgrammerErrorMessage() {
            return "";
        }

    }
}

