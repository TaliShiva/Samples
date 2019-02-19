//
// Created by user on 15.03.17.
//

#include "../../include/commands/destroy_raid_worker_command.hpp"

namespace gorynych {
    namespace workers {

        DestroyRaidWorkerCommand::DestroyRaidWorkerCommand(const std::vector<std::string> devices,
                                                           const std::string raidPath)
                : AbstractWorkerCommand(WorkerCommandType::DESTROY_RAID), devices_(devices), raidPath_(raidPath) {

        }

        const std::vector<std::string> &gorynych::workers::DestroyRaidWorkerCommand::devices() const {
            return devices_;
        }

        const std::string &gorynych::workers::DestroyRaidWorkerCommand::raidPath() const {
            return raidPath_;
        }
    }
}