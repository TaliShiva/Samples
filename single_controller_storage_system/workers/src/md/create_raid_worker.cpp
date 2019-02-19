//
// Created by user on 13.03.17.
//

#include "../../include/md/create_raid_worker.hpp"
#include "../../include/commands/create_raid_worker_command.hpp"
#include "../../../utils/include/start_custom_programm.hpp"

namespace gorynych {
    namespace workers {
        CreateRaidWorker::CreateRaidWorker(const unsigned int id, CreateRaidWorkerCommand command)
                : AbstractWorker(id, WORKER_TYPE::CREATE_RAID_WORKER), command_(command) {}

        CreateRaidWorkerResponse &CreateRaidWorker::doWork() {
            using utils::startCustomProgramm;
            CreateRaidWorkerResponse *response;
            std::string dirtyDisks = "";
            for (auto disk : command_.devices()) {
                std::string check_disk_output;
                if (startCustomProgramm("mdadm -E " + disk, check_disk_output) == 0) {
                    dirtyDisks += disk + " ";
                }
            }
            if(dirtyDisks!="") {
                response = new CreateRaidWorkerResponse(false,"Some disks not clean: " + dirtyDisks,"");
                return *response;
            }

            std::string mdadm_output = "";

            std::string mdadm_command = getMdadmCommand();

            if (startCustomProgramm(mdadm_command, mdadm_output) == 0) {
                response = new CreateRaidWorkerResponse(true);
            } else {
                response = new CreateRaidWorkerResponse(false, mdadm_output, "cannot create raid");
            }
            return *response; //FIXME заменить на shared_pointer
        }

        std::string CreateRaidWorker::getMdadmCommand() const {
            std::string mdadm_command = "mdadm --create --metadata=1.2 --force ";
     /*       if (command_.deviceCount() == 1) {
                mdadm_command += "--force "; // mdadm требует флаг force при создании raid-массива из одного диска
            }*/
            mdadm_command += command_.raidPath();
            mdadm_command += " --level=" + std::to_string(command_.raidLevel());
            mdadm_command += " --raid-devices=" + std::to_string(command_.deviceCount());

            for (auto device : command_.devices()) {
                mdadm_command += " " + device;
            }
            return mdadm_command;
        }

        void CreateRaidWorker::sendNotification() {}
    }
}