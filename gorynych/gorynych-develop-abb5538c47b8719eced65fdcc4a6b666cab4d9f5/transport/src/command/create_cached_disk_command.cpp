#include "../../include/command/create_cached_disk_command.hpp"

namespace gorynych {
    namespace transport {
        CreateCachedDiskCommand::CreateCachedDiskCommand()
                : AbstractCommand(CommandType::CREATE_CACHED_DISK_COMMAND,
                                  protobuf::Command::COMMAND_CREATE_CACHED_DISK) {
        }

        CreateCachedDiskCommand::CreateCachedDiskCommand(protobuf::Command command)
                : AbstractCommand(command, CommandType::CREATE_CACHED_DISK_COMMAND,
                                  protobuf::Command::COMMAND_CREATE_CACHED_DISK) {

        }

        void CreateCachedDiskCommand::setBaseDevicePath(const std::string &baseDevicePath) {
            protobufMessage_.mutable_create_caching_device()->set_base_device_path(baseDevicePath);
        }

        void CreateCachedDiskCommand::setCachingDevicePath(const std::string &cachingDevicePath) {
            protobufMessage_.mutable_create_caching_device()->set_caching_device_path(cachingDevicePath);
        }

        void CreateCachedDiskCommand::setCachingAlgorithm(const std::string &cachingAlgorithm) {
            protobufMessage_.mutable_create_caching_device()->set_caching_algorithm(cachingAlgorithm);
        }

        void CreateCachedDiskCommand::setCachingMode(const std::string &cachingMode) {
            protobufMessage_.mutable_create_caching_device()->set_caching_mode(cachingMode);
        }

        const std::string CreateCachedDiskCommand::baseDevicePath() const {
            return protobufMessage_.create_caching_device().base_device_path();
        }

        const std::string CreateCachedDiskCommand::cachingDevicePath() const {
            return protobufMessage_.create_caching_device().caching_device_path();
        }

        const std::string CreateCachedDiskCommand::cachingAlgorithm() const {
            return protobufMessage_.create_caching_device().caching_algorithm();
        }

        const std::string CreateCachedDiskCommand::cachingMode() const {
            return protobufMessage_.create_caching_device().caching_mode();
        }
    }
}


