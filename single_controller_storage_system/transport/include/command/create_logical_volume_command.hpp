
#pragma once

#include "abstract_command.hpp"

namespace gorynych {
    namespace transport {
        class CreateLogicalVolumeCommand : public AbstractCommand {
        public:
            CreateLogicalVolumeCommand();

            CreateLogicalVolumeCommand(protobuf::Command command);

            const std::string &logicalVolumeName() const;

            void setLogicalVolumeName(const std::string name);

            const std::string &logicalVolumeSize() const;

            void setlogicalVolumeSize(const std::string size);

            const std::string &parentVolumeGroupName() const;

            void setParentVolumeGroupName(const std::string volumeGroupName);

        };
    }
}