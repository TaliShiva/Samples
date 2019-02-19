
//

#include "../../include/lvm/create_logical_volume_worker.hpp"
#include "../../../utils/include/start_custom_programm.hpp"

namespace gorynych {
    namespace workers {
        CreateLogicalVolumeWorker::CreateLogicalVolumeWorker(const unsigned int id, CreateLogicalVolumeWorkerCommand command)
                : AbstractWorker(id, WORKER_TYPE::CREATE_LOGICAL_VOLUME_WORKER), command_(command) {}

        CreateLogicalVolumeWorkerResponse &CreateLogicalVolumeWorker::doWork() {
            using utils::startCustomProgramm;
            CreateLogicalVolumeWorkerResponse *response;
            std::string lvcreate_output = "";

            std::string lvcreate_command = getCreateLogicalVolumeProgramString();


            if (startCustomProgramm(lvcreate_command, lvcreate_output) == 0) {
                response = new CreateLogicalVolumeWorkerResponse(true);
            } else {
                response = new CreateLogicalVolumeWorkerResponse(false, lvcreate_output, "Cannot create Logical Volume");
            }
            return *response; //FIXME заменить на shared_pointer
        }

        std::string CreateLogicalVolumeWorker::getCreateLogicalVolumeProgramString() const {
            std::string lvcreate_command = "lvcreate";
            lvcreate_command += " -n " + command_.logicalVolumeName();
            lvcreate_command += " -L" + command_.logicalVolumeSize();
            lvcreate_command += " " + command_.parentVolumeGroupName();
            return lvcreate_command;
        }

        void CreateLogicalVolumeWorker::sendNotification() {}
    }
}