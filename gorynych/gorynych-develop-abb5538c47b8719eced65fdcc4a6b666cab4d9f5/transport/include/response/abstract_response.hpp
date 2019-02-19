//

#pragma once

#include "../response.hpp"

namespace gorynych {
    namespace transport {
        typedef protobuf::Response::Response_Type ProtoResponseType;
        class AbstractResponse :public IResponse {
        public:
            /**
             * @brief Возвращает название типа ответа
             * @return тип ответа @see ResponseType
             */
            ResponseType getResponseType() const;

            std::string getCodedData() const;

            /**
             * @brief Проверяет что все поля, необходимые для ответа заполнены
             * @return статус инициализации
             */
            bool isInitializedCorrect() const;


            AbstractResponse(std::string codedData, ResponseType responseType,
                             ProtoResponseType protobufType);

            AbstractResponse(ResponseType responseType, ProtoResponseType protobufType);

        protected:
            ResponseType responseType_;
        };

    }
}


