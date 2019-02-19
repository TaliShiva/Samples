#include "../../include/commands/create_cached_disk_worker_command.hpp"

namespace gorynych {
    namespace workers {
        CreateCachedDiskWorkerCommand::CreateCachedDiskWorkerCommand(const std::string &baseDevicePath,
                                                                     const std::string &cachingDevicePath,
                                                                     CachingAlgorithm cachingAlgorithm,
                                                                     CachingMode cachingMode):
            AbstractWorkerCommand(WorkerCommandType::CREATE_CACHED_DISK),
            baseDevicePath_(baseDevicePath),
            cachingDevicePath_(cachingDevicePath),
            cachingAlgorithm_(cachingAlgorithm),
            cachingMode_(cachingMode) {

        }

        const std::string CreateCachedDiskWorkerCommand::baseDevicePath() const {
            return baseDevicePath_;
        }

        const std::string CreateCachedDiskWorkerCommand::cachingDevicePath() const {
            return cachingDevicePath_;
        }

        const CachingAlgorithm CreateCachedDiskWorkerCommand::cachingAlgorithm() const {
            return cachingAlgorithm_;
        }

        const CachingMode CreateCachedDiskWorkerCommand::cachingMode() const {
            return cachingMode_;
        }
    }
}