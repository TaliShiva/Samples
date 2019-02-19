
#include "../../include/command/open.hpp"

namespace gorynych {
    namespace transport {
        OpenCommand::OpenCommand() : AbstractCommand(CommandType::OPEN_COMMAND, protobuf::Command::COMMAND_OPEN) {
        }

        OpenCommand::OpenCommand(protobuf::Command command)
                : AbstractCommand(command, CommandType::OPEN_COMMAND, protobuf::Command::COMMAND_OPEN) {
        }

        OpenCommand::~OpenCommand() {
        }


        const std::string &OpenCommand::devicePath() const {
            return protobufMessage_.open().device_path();
        }

        void OpenCommand::setDevicePath(const std::string &path) {
            protobufMessage_.mutable_open()->set_device_path(path);
        }

        const std::string &OpenCommand::targetName() const {
            return protobufMessage_.open().target_wwn();
        }

        void OpenCommand::setTargetName(const std::string &name) {
            protobufMessage_.mutable_open()->set_target_wwn(name);
        }

        unsigned int OpenCommand::lun() const {
            return protobufMessage_.open().lun();
        }

        void OpenCommand::setLun(int lun) {
            protobufMessage_.mutable_open()->set_lun(lun);
        }

    }
}