//

#pragma once

#include "../abstract_command.hpp"

namespace gorynych {
    namespace transport {
        class ListLogicalVolumeCommand : public AbstractCommand {
        public:

            ListLogicalVolumeCommand();

            ListLogicalVolumeCommand(ProtoCommand &command);
        };

    }
}




