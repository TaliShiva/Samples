
#include "../../include/command/destroy_raid_command.hpp"

namespace gorynych {
    namespace transport {

        DestroyRaidCommand::DestroyRaidCommand(protobuf::Command &protobufMessage) : AbstractCommand(
                protobufMessage, CommandType::DESTROY_RAID_COMMAND,  protobuf::Command::COMMAND_DESTROY_RAID) {}

        DestroyRaidCommand::DestroyRaidCommand()
                : AbstractCommand(CommandType::DESTROY_RAID_COMMAND,  protobuf::Command::COMMAND_DESTROY_RAID) {}

        void DestroyRaidCommand::setRaidPath(const std::string path) {
            protobufMessage_.mutable_destroy_raid()->set_raid_path(path);
        }

        const std::string &DestroyRaidCommand::raidPath() const {
            return protobufMessage_.destroy_raid().raid_path();
        }

        void DestroyRaidCommand::setDevices(const std::vector<std::string> devices) {
            for(auto device : devices){
                protobufMessage_.mutable_destroy_raid()->add_device(device);
            }
        }

        const std::vector<std::string> DestroyRaidCommand::devices() const {
            std::vector<std::string> devices;
            for(int i = 0; i<protobufMessage_.destroy_raid().device_size();i++){
                devices.push_back(protobufMessage_.destroy_raid().device(i));
            }
            return devices;
        }

    }
}