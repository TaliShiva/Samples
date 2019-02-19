#include "../../include/scst/remove_disk_from_scst_worker.hpp"
namespace gorynych {
    namespace workers {

        RemoveDiskFromScstWorker::RemoveDiskFromScstWorker(const unsigned int id,
                                                           const RemoveDiskFromScstWorkerCommand &command)
                : AbstractScstWorker(id,WORKER_TYPE::REMOVE_DISK_FROM_SCST_WORKER), command_(command) {

        }

        void RemoveDiskFromScstWorker::sendNotification() {

        }

        RemoveDiskFromScstWorkerResponse &RemoveDiskFromScstWorker::doWork() {
            if(writeToSysFs(vDiskPath_, generateRemoveDiskString())) {
                return *new RemoveDiskFromScstWorkerResponse(true);
            } else {
                return  *new RemoveDiskFromScstWorkerResponse(false, generateSystemErrorMessage(),
                                                              generateProgrammerErrorMessage());
            }
        }

        const std::string RemoveDiskFromScstWorker::generateSystemErrorMessage() {
            return "RemoveDiskFromScstWorker: system error";
        }

        const std::string RemoveDiskFromScstWorker::generateProgrammerErrorMessage() {
            return "эта хрень не работает, уберите свой говнокод";
        }
    }
}
