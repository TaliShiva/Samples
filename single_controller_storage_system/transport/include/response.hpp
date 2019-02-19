#pragma once

#include <string>
#include "../../cmake-build-debug/command_api.pb.h"

namespace gorynych {
    namespace transport {
        typedef protobuf::Response ProtoResponse;
        /**
         * Перечисление всех типов ответов
         */
        enum class ResponseType {
            TEXT_RESPONSE,
            LIST_RAID_RESPONSE,
            LIST_LOGICAL_VOLUME_RESPONSE,
            LIST_SCST_RESPONSE,
        };

        /**
         * Общий интерфейс для ответов на команды
         */
        class IResponse {
        protected:
            protobuf::Response protobufMessage_;
        public:
            /**
             * @brief Возвращает название типа ответа
             * @return название типа ответа
             */
            virtual ResponseType getResponseType() const =0;

            virtual std::string getCodedData() const =0;

            /**
             * @brief Проверяет что все поля, необходимые для ответа заполнены
             * @return статус инициализации
             */
            virtual bool isInitializedCorrect() const =0;
        };
    }
}
