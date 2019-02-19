#include "../../include/commands/add_disk_to_scst_worker_command.hpp"
namespace gorynych {
    namespace workers {

        AddDiskToScstWorkerCommand::AddDiskToScstWorkerCommand(const std::string &devicePath, const std::string &vDiskName)
                : AbstractWorkerCommand(WorkerCommandType::ADD_DISK_TO_SCST), 
                  devicePath_(devicePath),vDiskName_(vDiskName) {
        }

        const std::string &AddDiskToScstWorkerCommand::vDiskName() const {
            return vDiskName_;
        }
    }
}
