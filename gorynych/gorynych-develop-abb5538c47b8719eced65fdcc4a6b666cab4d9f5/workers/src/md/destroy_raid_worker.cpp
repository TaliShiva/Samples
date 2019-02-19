//
// Created by user on 15.03.17.
//

#include "../../include/md/destroy_raid_worker.hpp"
#include "../../../utils/include/start_custom_programm.hpp"

namespace gorynych {
    namespace workers {

        DestroyRaidWorker::DestroyRaidWorker(const unsigned int id,
                                             const DestroyRaidWorkerCommand command)
                : AbstractWorker(id, WORKER_TYPE::DESTROY_RAID_WORKER), command_(command) {}

        DestroyRaidWorkerResponse &DestroyRaidWorker::doWork() {
            using utils::startCustomProgramm;
            DestroyRaidWorkerResponse *response;
            std::string mdadm_stop_raid_output = "";
            std::string mdadm_zero_output = "";
            std::string mdadm_stop_raid_command = "mdadm -S " + command_.raidPath();
            if (startCustomProgramm(mdadm_stop_raid_command, mdadm_stop_raid_output) == 0) {
                std::string mdadm_zero_command = "mdadm --zero-superblock";
                for (auto device : command_.devices()) {
                    mdadm_zero_command += " " + device;
                    std::cout << "erase device: " << device << std::endl;
                }
                if (startCustomProgramm(mdadm_zero_command, mdadm_zero_output) == 0) {
                    response = new DestroyRaidWorkerResponse(true);
                } else {
                    response = new DestroyRaidWorkerResponse(false, mdadm_zero_output, "cannot zero-superblosck");
                }
            } else {
                response = new DestroyRaidWorkerResponse(false, mdadm_stop_raid_output, "cannot remove raid");
            }
            return *response;
        }

        void DestroyRaidWorker::sendNotification() {}
    }
}