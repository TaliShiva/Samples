
#include "../../include/command/close.hpp"

namespace gorynych {
    namespace transport {
        CloseCommand::CloseCommand() : AbstractCommand(CommandType::CLOSE_COMMAND,
                                                       protobuf::Command::COMMAND_CLOSE_ALL) {
        }

        CloseCommand::CloseCommand(protobuf::Command command)
                : AbstractCommand(command, CommandType::CLOSE_COMMAND, protobuf::Command::COMMAND_CLOSE_ALL) {
        }

        CloseCommand::~CloseCommand() {
        }

        const std::string &CloseCommand::devicePath() const {
            return protobufMessage_.close().device_path();
        }

        void CloseCommand::setDevicePath(const std::string &path) {
            protobufMessage_.mutable_close()->set_device_path(path);
        }

        const std::string &CloseCommand::targetName() const {
            return protobufMessage_.close().target_wwn();
        }

        void CloseCommand::setTargetName(const std::string &name) {
            protobufMessage_.mutable_close()->set_target_wwn(name);
        }

        unsigned int CloseCommand::lun() const {
            return protobufMessage_.close().lun();
        }

        void CloseCommand::setLun(int lun) {
            protobufMessage_.mutable_close()->set_lun(lun);
        }


    }
}