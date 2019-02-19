
#pragma once
#include "abstract_command.hpp"


namespace gorynych {
    namespace transport {
        class DestroyRaidCommand : public AbstractCommand {
        public:
            DestroyRaidCommand(protobuf::Command &protobufMessage);
            DestroyRaidCommand();
            /**
             * @param path - путь к уничтожаемому raid-массиву
             */
            void setRaidPath(const std::string path);
            const std::string& raidPath() const;
            /**
             * @param devices - название удаляемых устройств из raid-массива
             */
            void setDevices(const std::vector<std::string> devices);
            const std::vector<std::string> devices() const;
        };
    }
}


