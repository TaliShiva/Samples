#include "../../include/command/detach_cached_disk_command.hpp"

namespace gorynych {
    namespace transport {
        DetachCachedDiskCommand::DetachCachedDiskCommand()
                : AbstractCommand(CommandType::DETACH_CACHED_DISK_COMMAND,
                                  protobuf::Command::COMMAND_DETACH_CACHED_DISK) {
        }

        DetachCachedDiskCommand::DetachCachedDiskCommand(protobuf::Command command)
                : AbstractCommand(command, CommandType::DETACH_CACHED_DISK_COMMAND,
                                  protobuf::Command::COMMAND_DETACH_CACHED_DISK) {

        }

        void DetachCachedDiskCommand::setBaseDevicePath(const std::string &baseDevicePath) {
            protobufMessage_.mutable_create_caching_device()->set_base_device_path(baseDevicePath);
        }

        void DetachCachedDiskCommand::setCachingDevicePath(const std::string &cachingDevicePath) {
            protobufMessage_.mutable_create_caching_device()->set_caching_device_path(cachingDevicePath);
        }

        const std::string DetachCachedDiskCommand::baseDevicePath() const {
            return protobufMessage_.create_caching_device().base_device_path();
        }

        const std::string DetachCachedDiskCommand::cachingDevicePath() const {
            return protobufMessage_.create_caching_device().caching_device_path();
        }
    }
}