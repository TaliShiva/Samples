#include "../../include/command/abstract_command.hpp"

namespace gorynych {
    namespace transport {
        CommandType AbstractCommand::getCommandType() const {
            return type_;
        }

        std::string AbstractCommand::getCodedData() const {
            return protobufMessage_.SerializeAsString();
        }

        bool AbstractCommand::isInitializedCorrect() const {
            return protobufMessage_.IsInitialized();
        }

    }
}