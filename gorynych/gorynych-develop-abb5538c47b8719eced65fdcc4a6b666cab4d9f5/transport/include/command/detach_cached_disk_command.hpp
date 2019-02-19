#pragma once

#include "../command.hpp"
#include "abstract_command.hpp"

namespace gorynych {
    namespace transport {
        class DetachCachedDiskCommand : public AbstractCommand {
        public:
            DetachCachedDiskCommand();

            DetachCachedDiskCommand(protobuf::Command command);

            const std::string baseDevicePath() const;
            const std::string cachingDevicePath() const;

            void setBaseDevicePath(const std::string &baseDevicePath);
            void setCachingDevicePath(const std::string &cachingDevicePath);
        };
    }
}