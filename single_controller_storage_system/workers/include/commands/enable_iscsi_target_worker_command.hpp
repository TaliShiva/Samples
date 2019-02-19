#pragma once

#include "abstract_worker_command.hpp"
#include <string>

namespace gorynych {
    namespace workers {
        class EnableIscsiTargetWorkerCommand : public AbstractWorkerCommand {
        private:
            const std::string targetName_;
        public:
            EnableIscsiTargetWorkerCommand(const std::string &targetName);
            inline std::string targetName() const{
                return targetName_;
            }
        };

    }
}
