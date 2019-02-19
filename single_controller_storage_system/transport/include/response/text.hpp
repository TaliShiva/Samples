#pragma once

#include "../response.hpp"
#include "abstract_response.hpp"

namespace gorynych {
    namespace transport {
        /**
         * Класс простого ответ на команду
         */
        class TextResponse : public AbstractResponse {
        private:
            std::string logicErrorMessage_ = "programmerErrorMessage";
            std::string systemErrorMessage_ = "systemErrorMessage";
            bool success_ = false;
        public:

            TextResponse(const std::string &coded_data);

            TextResponse();

            ~TextResponse();

            /**
             * @brief Возвращает статус выполнения команды успех/неудача
             * @return статус выполнения
             */
            bool success() const;

            /**
             * @brief Устанавливает статус выполнения команды успех/неудача
             * @param status статус выполнения
             */
            void setSuccess(bool status);

            /**
             * @brief Возвращает сообщение о логической ошибке
             * @return
             */
            const std::string &logicErrorMessage() const;

            /**
             * @brief Устанавливает сообщение о логической ошибке
             * @param message сообщение о логической ошибке
             */
            void setLogicErrorMessage(const std::string &message);

            /**
             * @brief Устанавливает сообщение о ошибке системы
             * @return сообщение о ошибке системы
             */
            const std::string &systemErrorMessage() const;

            /**
             * @brief Устанавливает сообщение о ошибке системы
             * @param message сообщение о ошибке системы
             */
            void setSystemErrorMessage(const std::string &message);
        };
    }
}
