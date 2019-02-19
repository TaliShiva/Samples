#pragma once

#include "abstract_worker_command.hpp"

#include <string>

namespace gorynych {
    namespace workers {

        class DetachCachedDiskWorkerCommand: public AbstractWorkerCommand {
        public:
            DetachCachedDiskWorkerCommand(const std::string &baseDeviceName,
                                          const std::string &cachingDeviceName);
            const std::string baseDevicePath() const;
            const std::string cachingDevicePath() const;
        private:
            const std::string baseDevicePath_;
            const std::string cachingDevicePath_;
        };
    }
}