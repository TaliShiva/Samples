//

#include "../../../include/command/list/list_raid_command.hpp"
namespace gorynych {
    namespace transport {

        ListRaidCommand::ListRaidCommand()
                : AbstractCommand(CommandType::LIST_RAID_COMMAND,
                                  ProtoCommand::COMMAND_LIST_RAID) {}

        ListRaidCommand::ListRaidCommand(protobuf::Command &command)
                : AbstractCommand(command,
                                  CommandType::LIST_RAID_COMMAND,
                                  ProtoCommand::COMMAND_LIST_RAID) {}
    }
}
