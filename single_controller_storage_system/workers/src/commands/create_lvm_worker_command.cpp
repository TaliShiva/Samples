//
// Created by alex on 3/13/17.
//

#include "../../include/commands/create_lvm_worker_command.hpp"

namespace gorynych {
    namespace workers {

        CreateLvmWorkerCommand::CreateLvmWorkerCommand(const std::string lvmName, const std::string devicePath)
                : AbstractWorkerCommand(WorkerCommandType::CREATE_LVM), lvmName_(lvmName), devicePath_(devicePath) {}

        const std::string CreateLvmWorkerCommand::getLvmName_() const {
            return lvmName_;
        }

        const std::string CreateLvmWorkerCommand::getDevicePath_() const {
            return devicePath_;
        }
    }
}