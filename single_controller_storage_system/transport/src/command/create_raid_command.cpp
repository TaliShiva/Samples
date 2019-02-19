//
// Created by user on 14.03.17.
//

#include "../../include/command/create_raid_command.hpp"


namespace gorynych {
    namespace transport {

        CreateRaidCommand::CreateRaidCommand(protobuf::Command &protobufMessage) : AbstractCommand(
                protobufMessage, CommandType::CREATE_RAID_COMMAND,  protobuf::Command::COMMAND_CREATE_RAID) {}

        CreateRaidCommand::CreateRaidCommand()
                : AbstractCommand(CommandType::CREATE_RAID_COMMAND,  protobuf::Command::COMMAND_CREATE_RAID) {}

        void CreateRaidCommand::setRaidPath(const std::string path) {
            protobufMessage_.mutable_create_raid()->set_raid_path(path);
        }

        const std::string &CreateRaidCommand::raidPath() const {
            return protobufMessage_.create_raid().raid_path();
        }

        void CreateRaidCommand::setRaidLevel(unsigned int level) {
            protobufMessage_.mutable_create_raid()->set_raid_level(level);
        }

        const unsigned int CreateRaidCommand::raidLevel() const {
            return protobufMessage_.create_raid().raid_level();
        }

        void CreateRaidCommand::setDevicesCount(unsigned int devices_count) {
            protobufMessage_.mutable_create_raid()->set_devices_count(devices_count);
        }

        const unsigned int CreateRaidCommand::deviceCount() const {
            return protobufMessage_.create_raid().devices_count();
        }

        void CreateRaidCommand::setDevices(const std::vector<std::string> devices) {
            for(auto device : devices){
                protobufMessage_.mutable_create_raid()->add_device(device);
            }
        }

        const std::vector<std::string> CreateRaidCommand::devices() const {
            std::vector<std::string> devices;
            for (int i = 0; i < protobufMessage_.create_raid().device_size(); i++) {
                devices.push_back(protobufMessage_.create_raid().device(i));
            }
            return devices;
        }

    }
}
