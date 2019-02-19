#pragma once

#include "../command.hpp"
#include "abstract_command.hpp"

namespace gorynych {
    namespace transport {
        class CreateCachedDiskCommand : public AbstractCommand {
        public:
            CreateCachedDiskCommand();

            CreateCachedDiskCommand(protobuf::Command command);

            const std::string baseDevicePath() const;
            const std::string cachingDevicePath() const;
            const std::string cachingAlgorithm() const;
            const std::string cachingMode() const;

            void setBaseDevicePath(const std::string &baseDevicePath);
            void setCachingDevicePath(const std::string &cachingDevicePath);
            void setCachingAlgorithm(const std::string &cachingAlgorithm);
            void setCachingMode(const std::string &cachingMode);

        };
    }
}
