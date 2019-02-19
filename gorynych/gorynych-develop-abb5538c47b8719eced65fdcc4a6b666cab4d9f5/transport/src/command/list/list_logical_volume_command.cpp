//

#include "../../../include/command/list/list_logical_volume_command.hpp"

namespace gorynych {
    namespace transport {

        ListLogicalVolumeCommand::ListLogicalVolumeCommand()
                : AbstractCommand(CommandType::LIST_LOGICAL_VOLUME_COMMAND,
                                  ProtoCommand::COMMAND_LIST_LOGICAL_VOLUME) {}

        ListLogicalVolumeCommand::ListLogicalVolumeCommand(ProtoCommand &command)
                : AbstractCommand(command, CommandType::LIST_LOGICAL_VOLUME_COMMAND,
                                  ProtoCommand::COMMAND_LIST_LOGICAL_VOLUME) {

        }
    }
}
