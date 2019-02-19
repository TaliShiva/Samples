//

#pragma once

#include "abstract_command.hpp"

namespace gorynych {
    namespace transport {
        class RemoveDiskFromScstCommand : public AbstractCommand {
        public:
            /**
             * @brief RemoveDiskFromScstCommand  - @see documentation  AbstractCommand
             */
            RemoveDiskFromScstCommand();

            RemoveDiskFromScstCommand(protobuf::Command command);

            const std::string &devicePath() const;

            void setDevicePath(const std::string &devicePath);
        };
    }
}
