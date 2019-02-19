#include <boost/algorithm/string/replace.hpp>
#include "../../include/scst/add_disk_to_scst_worker.hpp"
#include "../../../utils/include/build__scst_vdisk_name.hpp"

namespace gorynych {
    namespace workers {
        
        AddDiskToScstWorker::AddDiskToScstWorker(const unsigned int id, const AddDiskToScstWorkerCommand &command)
                : AbstractScstWorker(id, WORKER_TYPE::ADD_DISC_TO_SCST_WORKER), command_(command) {
        }

        AddDiskToScstWorkerResponse &AddDiskToScstWorker::doWork() {
            AddDiskToScstWorkerResponse *response;
            if (writeToSysFs(fileIoHandlerPath_, generateStringForAddCommand())) {
                response = new AddDiskToScstWorkerResponse(true);
            } else {
                response = new AddDiskToScstWorkerResponse(false, generateSystemErrorMessage(),
                                                           generateProgrammerErrorMessage());
            }
            return *response;
        }

        void AddDiskToScstWorker::sendNotification() {

        }

        const std::string AddDiskToScstWorker::generateStringForAddCommand() {
            auto magicString1 = "add_device ";
            auto magicString2 = " filename=";
            auto magicString3 = "; nv_cache=1";
            
            return magicString1 + command_.vDiskName() + magicString2 + command_.devicePath() + magicString3;
        }

        const std::string AddDiskToScstWorker::generateSystemErrorMessage() {
            return "AddDiskToScstWorker system error";
        }

        const std::string AddDiskToScstWorker::generateProgrammerErrorMessage() {
            return "cannot add device " + command_.vDiskName() + "from " + command_.devicePath();;
        }
    }
}
