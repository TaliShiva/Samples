#pragma once

#include "abstract_worker_command.hpp"
#include "connect_device_to_iscsi_target_worker_command.hpp"
#include <string>

namespace gorynych {
    namespace workers {
        class CreateTargetWorkerCommand : public AbstractWorkerCommand {
        public:
            CreateTargetWorkerCommand(const std::string targetName);

        private:
            const std::string targetName_;
        public:
            const std::string targetName() const;

        };

    }
}

