#pragma once

#include "abstract_command.hpp"

namespace gorynych {
    namespace transport {
        class AddDiskToScstCommand : public AbstractCommand {

        public:
            /**
             * @brief
             * @return
             */
            const std::string &devicePath() const;

            /**
             * @brief
             * @param devicePath
             */
            void setDevicePath(const std::string devicePath);


            AddDiskToScstCommand(protobuf::Command command);

            /**
             * @brief
             */
            void print() override;

            AddDiskToScstCommand();
        };
    }
}



