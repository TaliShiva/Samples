//
// Created by dumplings on 16.03.17.
//

#include "../../include/command/remove_lun_from_iscsi_target_command.hpp"

namespace gorynych {
    namespace transport {


        RemoveLunFromIscsiTargetCommand::RemoveLunFromIscsiTargetCommand()
                : AbstractCommand(CommandType::REMOVE_LUN_FROM_ISCSI_TARGET_COMMAND,
                                  protobuf::Command::COMMAND_NONE) {

        }
    }
}
