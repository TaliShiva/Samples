//

#pragma once

#include "../abstract_command.hpp"

namespace gorynych {
    namespace transport {
        class ListScstCommand : public AbstractCommand {
        public:
            ListScstCommand();

            ListScstCommand(ProtoCommand &command);
        };
    }
}



