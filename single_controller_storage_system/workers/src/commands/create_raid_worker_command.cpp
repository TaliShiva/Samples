//
// Created by user on 13.03.17.
//

#include "../../include/commands/create_raid_worker_command.hpp"
namespace gorynych {
    namespace workers {

        CreateRaidWorkerCommand::CreateRaidWorkerCommand(const unsigned int deviceCount, const unsigned int raidLevel,
                                                         const std::vector<std::string> devices,
                                                         const std::string raidPath)
                : AbstractWorkerCommand(WorkerCommandType::CREATE_RAID), deviceCount_(deviceCount),
                  raidLevel_(raidLevel), devices_(devices), raidPath_(raidPath)  {}

        const unsigned int CreateRaidWorkerCommand::raidLevel() const {
            return raidLevel_;
        }

        const unsigned int CreateRaidWorkerCommand::deviceCount() const {
            return deviceCount_;
        }

        const std::vector<std::string> &CreateRaidWorkerCommand::devices() const {
            return devices_;
        }

        const std::string &CreateRaidWorkerCommand::raidPath() const {
            return raidPath_;
        }
    }
}