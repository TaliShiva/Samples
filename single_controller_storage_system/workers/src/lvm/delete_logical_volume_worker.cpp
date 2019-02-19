
#include "../../include/lvm/delete_logical_volume_worker.hpp"
#include "../../../utils/include/start_custom_programm.hpp"

namespace gorynych {
    namespace workers {

        DeleteLogicalVolumeWorker::DeleteLogicalVolumeWorker(const unsigned int id, const DeleteLogicalVolumeWorkerCommand &command)
                : AbstractWorker(id, WORKER_TYPE::DELETE_LOGICAL_VOLUME_WORKER), command_(command) {

        }

        DeleteLogicalVolumeWorkerResponse &DeleteLogicalVolumeWorker::doWork() {
            using utils::startCustomProgramm;
            DeleteLogicalVolumeWorkerResponse *response;
            std::string lvm_destroy_output = "";
            std::string lvm_destroy_command = "lvremove -f "+ command_.volumeGroupName();
            lvm_destroy_command += "/" + command_.logicalVolumeName();
            if (startCustomProgramm(lvm_destroy_command, lvm_destroy_output) == 0) {
                response = new DeleteLogicalVolumeWorkerResponse(true);

            } else {
                response = new DeleteLogicalVolumeWorkerResponse(false, lvm_destroy_output, "cannot destroy lvm");
            }
            return *response;

        }

        void DeleteLogicalVolumeWorker::sendNotification() {

        }
    }
}