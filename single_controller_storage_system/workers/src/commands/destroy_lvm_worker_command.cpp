
//

#include "../../include/commands/destroy_lvm_worker_command.hpp"
namespace gorynych {
    namespace workers {

        DestroyLvmWorkerCommand::DestroyLvmWorkerCommand(const std::string lvmName, const std::string devicePath)
                : AbstractWorkerCommand(WorkerCommandType::DESTROY_LVM), lvmName_(lvmName), devicePath_(devicePath) {}

        const std::string DestroyLvmWorkerCommand::getLvmName_() const {
            return lvmName_;
        }

        const std::string DestroyLvmWorkerCommand::getDevicePath_() const {
            return devicePath_;
        }
    }
}