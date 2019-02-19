
//

#include "../../include/lvm/destroy_lvm_worker.hpp"
#include "../../../utils/include/start_custom_programm.hpp"

namespace gorynych {
    namespace workers {

        DestroyLvmWorker::DestroyLvmWorker(const unsigned int id, const DestroyLvmWorkerCommand &command)
                : AbstractWorker(id, WORKER_TYPE::DESTROY_LVM), command_(command) {

        }

        DestroyLvmWorkerResponse &DestroyLvmWorker::doWork() {
            using utils::startCustomProgramm;
            const std::string removeVolumeGroupProgramFirst = "vgremove -y ";
            std::string removeVolumeGroupProgram = removeVolumeGroupProgramFirst + command_.getLvmName_();

            std::string removeVolumeGroupProgramOutput = "";
            if (startCustomProgramm(removeVolumeGroupProgram, removeVolumeGroupProgramOutput) == 0) {
                const std::string destroyLvmDeviceProgramFirst = "pvremove -y ";
                std::string destroyLvmDeviceProgram =
                        destroyLvmDeviceProgramFirst + command_.getDevicePath_();
                std::string destroyLvmDeviceProgramOutput = "";
                if (startCustomProgramm(destroyLvmDeviceProgram, destroyLvmDeviceProgramOutput) == 0) {
                    return *(new DestroyLvmWorkerResponse(true));
                } else {
                    return *(new DestroyLvmWorkerResponse(false, "LVM Failed; Error destroy LVM on device",
                                                          destroyLvmDeviceProgramOutput));
                }
            } else {
                return *(new DestroyLvmWorkerResponse(false, "LVM Failed; Error removing VG",
                                                      removeVolumeGroupProgramOutput));
            }
        }

        void DestroyLvmWorker::sendNotification() {
        }
    }
}