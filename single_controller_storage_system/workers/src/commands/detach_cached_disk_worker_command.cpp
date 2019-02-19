#include "../../include/commands/detach_cached_disk_worker_command.hpp"

namespace gorynych {
    namespace workers {
        DetachCachedDiskWorkerCommand::DetachCachedDiskWorkerCommand(const std::string &baseDevicePath,
                                                                     const std::string &cachingDevicePath):
                AbstractWorkerCommand(WorkerCommandType::DETACH_CACHED_DISK),
                baseDevicePath_(baseDevicePath),
                cachingDevicePath_(cachingDevicePath) {

        }

        const std::string DetachCachedDiskWorkerCommand::baseDevicePath() const {
            return baseDevicePath_;
        }

        const std::string DetachCachedDiskWorkerCommand::cachingDevicePath() const {
            return cachingDevicePath_;
        }
    }
}