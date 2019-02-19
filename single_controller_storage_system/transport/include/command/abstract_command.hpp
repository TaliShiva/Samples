

#pragma once

#include <iostream>
#include "../command.hpp"

namespace gorynych {
    namespace transport {
        typedef  protobuf::Command ProtoCommand;
        class AbstractCommand : public ICommand {
        public:
            AbstractCommand(protobuf::Command &protobufMessage_, CommandType type_,
                            protobuf::Command_Command_Type protobuf_type) : protobufMessage_(protobufMessage_),
                                                                            type_(type_) {
                protobufMessage_.set_type(protobuf_type);
            }


            AbstractCommand(CommandType type_, protobuf::Command_Command_Type protobuf_type) : type_(type_) {
                protobufMessage_.set_type(protobuf_type);
            }

            /**
             * @brief Возвращает название типа команды
             * @return тип команды @see CommandType
             */
            CommandType getCommandType() const override;

            /**
             * @brief Возвращает закодированную строку для передачи по сети
             * @return закодированная строка
             */
            std::string getCodedData() const override;

            /**
             * @brief Проверяет что все поля, необходимые для выполнения команды заполнены
             * @return статус инициализации
             */
            bool isInitializedCorrect() const override;

            virtual void print() { std::cout << "abstract command"; }
        protected:
            protobuf::Command protobufMessage_;
            CommandType type_;
        };
    }
}
