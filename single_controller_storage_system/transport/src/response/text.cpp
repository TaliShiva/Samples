
#include <iostream>
#include "../../include/response/text.hpp"

namespace gorynych {
    namespace transport {
        TextResponse::TextResponse(const std::string &coded_data)
                : AbstractResponse(coded_data,
                                   ResponseType::TEXT_RESPONSE,
                                   ProtoResponse::RESPONSE_TEXT) {}

        TextResponse::TextResponse()
                : AbstractResponse(ResponseType::TEXT_RESPONSE,
                                   ProtoResponse::RESPONSE_TEXT) {}

        TextResponse::~TextResponse() {
        }


        bool TextResponse::success() const {
            return protobufMessage_.text().success();
        }

        void TextResponse::setSuccess(bool status) {
            protobufMessage_.mutable_text()->set_success(status);
        }

        const std::string &TextResponse::logicErrorMessage() const {
            return protobufMessage_.text().logic_error_message();
        }

        void TextResponse::setLogicErrorMessage(const std::string &message) {
            protobufMessage_.mutable_text()->set_logic_error_message(message);
        }

        const std::string &TextResponse::systemErrorMessage() const {
            return protobufMessage_.text().system_error_message();
        }

        void TextResponse::setSystemErrorMessage(const std::string &message) {
            protobufMessage_.mutable_text()->set_system_error_message(message);
        }
    }
}