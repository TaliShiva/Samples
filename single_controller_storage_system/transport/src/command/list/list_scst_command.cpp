//

#include "../../../include/command/list/list_scst_command.hpp"

namespace gorynych {
    namespace transport {

        ListScstCommand::ListScstCommand()
                : AbstractCommand(CommandType::LIST_SCST_COMMAND,
                                  ProtoCommand::COMMAND_LIST_SCST) {}

        ListScstCommand::ListScstCommand(ProtoCommand &command)
                : AbstractCommand(command,
                                  CommandType::LIST_SCST_COMMAND,
                                  ProtoCommand::COMMAND_LIST_SCST) {}
    }
}