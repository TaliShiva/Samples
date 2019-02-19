//

#include <iostream>
#include "../../include/response/abstract_response.hpp"




namespace gorynych {
    namespace transport {
        AbstractResponse::AbstractResponse(ResponseType responseType, ProtoResponseType protobufType)
                : responseType_(responseType) {
            // Установка обязательного поля
            protobufMessage_.set_type(protobufType);
        }

        AbstractResponse::AbstractResponse(std::string codedData, ResponseType responseType,
                                           ProtoResponseType protobufType)
                : AbstractResponse(responseType, protobufType){
            //TODO: перенести создание из кодированного сообщения в фабрику
            // Установка обязательного поля
            if (!protobufMessage_.ParseFromString(codedData)) {
                throw std::runtime_error("Protobuf: Ошибка парсинга ответа");
            }
        }

        ResponseType AbstractResponse::getResponseType() const {
            return responseType_;
        }

        std::string AbstractResponse::getCodedData() const {
            std::cout << protobufMessage_.DebugString()<< std::endl;
            return protobufMessage_.SerializeAsString();
        }

        bool AbstractResponse::isInitializedCorrect() const {
            return protobufMessage_.IsInitialized();
        }
    }
}