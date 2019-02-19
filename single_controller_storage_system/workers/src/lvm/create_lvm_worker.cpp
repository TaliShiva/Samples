//
// Created by alex on 3/13/17.
//

#include "../../include/lvm/create_lvm_worker.hpp"
#include "../../../utils/include/start_custom_programm.hpp"

namespace gorynych {
    namespace workers {

        CreateLvmWorker::CreateLvmWorker(const unsigned int id, const CreateLvmWorkerCommand &command)
                : AbstractWorker(id, WORKER_TYPE::CREATE_LVM_WORKER), command_(command) {

        }

        CreateLvmWorkerResponse &CreateLvmWorker::doWork() {
            using utils::startCustomProgramm;
            const std::string initializeDiskProgrammFirst = "pvcreate -y ";
            std::string initializeDiskProgramm = initializeDiskProgrammFirst + command_.getDevicePath_();

            std::string initializeDiskProgrammOutput = "";
            if (startCustomProgramm(initializeDiskProgramm, initializeDiskProgrammOutput) == 0) {
                const std::string createVgProgrammFirst = "vgcreate -y ";
                std::string createVgProgramm =
                        createVgProgrammFirst + command_.getLvmName_() + " " + command_.getDevicePath_();
                std::string createVgProgrammOutput = "";
                if (startCustomProgramm(createVgProgramm, createVgProgrammOutput) == 0) {
                    return *(new CreateLvmWorkerResponse(true));
                } else {
                    return *(new CreateLvmWorkerResponse(false, "LVM Failed; Error creating VG",
                                                         createVgProgrammOutput));
                }
            } else {
                return *(new CreateLvmWorkerResponse(false, "LVM Failed; Error initializing device",
                                                     initializeDiskProgrammOutput));
            }
        }

        void CreateLvmWorker::sendNotification() {
        }
    }
}