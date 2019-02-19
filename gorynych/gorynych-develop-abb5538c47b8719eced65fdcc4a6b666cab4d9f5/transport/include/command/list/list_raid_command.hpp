//

#pragma once

#include "../abstract_command.hpp"

namespace gorynych {
    namespace transport {
        class ListRaidCommand : public AbstractCommand {
        public:
            ListRaidCommand();

            ListRaidCommand(ProtoCommand &command);
        };

    }
}




