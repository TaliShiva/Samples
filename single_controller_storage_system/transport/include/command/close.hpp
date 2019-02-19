#pragma once

#include "../command.hpp"
#include "abstract_command.hpp"

namespace gorynych {
    namespace transport {
        /**
         * Класс команды close
         */
        class CloseCommand : public AbstractCommand {
        public:

            /**
             * @brief Создать пустую команду Close
             */
            CloseCommand(); //TODO заменить сеттеры на конструктор с параметрами, конструктор по-уммолчанию запретить

            /**
             * @brief Создать команду Close из данных protobuf
             * @param command
             */
            CloseCommand(gorynych::transport::protobuf::Command command);

            ~CloseCommand();

            /**
             * @brief Возвращает путь к устройству которое должно быть экспортировано
             * @return путь к устройству
             */
            const std::string &devicePath() const;

            /**
             * @brief Устанавливает путь к устройству которое должно быть экспортировано
             * @param path
             */
            void setDevicePath(const std::string &path);

            /**
             * @brief Возвращает имя таргета который должен быть создан
             * @return имя таргета
             */
            const std::string &targetName() const;

            /**
             * @brief Устанавливает имя таргета который должен быть создан
             * @param name имя таргета
             */
            void setTargetName(const std::string &name);

            /**
             * @brief Возвращает номер LUN с которым должкен быть экспортирован диск
             * @return LUN
             */
            unsigned int lun() const;

            /**
             * @brief Устанавливает номер LUN с которым должен быть экспортирован диск
             * @param lun LUN
             */
            void setLun(int lun);

        };
    }
}