#pragma once

#include "abstract_worker_command.hpp"
#include <string>
namespace gorynych {
    namespace workers {
        /**
         * @class AddDisk2ScstWorkerCommand
         */
        class AddDiskToScstWorkerCommand : public AbstractWorkerCommand {
        public:
            /**
             *
             * @param devicePath
             */
            AddDiskToScstWorkerCommand(const std::string &devicePath, const std::string &vDiskName);

            /**
             *
             * @return
             */
            const std::string devicePath() const { return devicePath_; }

            const std::string &vDiskName() const;

        private:
            const std::string devicePath_;
            const std::string vDiskName_;
        };
    }
}
