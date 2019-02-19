//

#pragma once

#include "abstract_worker_command.hpp"
#include <string>
namespace gorynych {
    namespace workers {
        class DisableIscsiTargetWorkerCommand : public AbstractWorkerCommand {
        private:
            const std::string targetName_;
        public:
            DisableIscsiTargetWorkerCommand(const std::string &targetName);

            inline std::string targetName() const {
                return targetName_;
            }
            DisableIscsiTargetWorkerCommand();
        };
    }
}



