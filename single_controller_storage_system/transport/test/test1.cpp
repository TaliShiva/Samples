
#include <iostream>
#include "../include/transport_api.hpp"
#include "abstract_response.hpp"

using namespace gorynych::transport;
/**
 * Пока вместо гугл-тестов
 * Проверяем что заглушки работают
 */
TextResponse resptest() {
    TextResponse tt;
    tt.setLogicErrorMessage("logic error message");
    return tt;
}
int main() {
    std::cout << "test: " << std::endl;
    OpenCommand a;
    CloseCommand b;
    TextResponse resp;
    a.setDevicePath("/dev/test");
    a.setTargetName("wwn_name");
    resp.setLogicErrorMessage("logic error message");
    std::cout << a.devicePath() << std::endl;
    std::cout << a.targetName() << std::endl;
    std::cout << b.getCodedData() << std::endl;
    std::cout << resp.logicErrorMessage() << std::endl;
    std::cout << a.devicePath() << std::endl;

    if (CommandType::CLOSE_COMMAND == b.getCommandType()) {
        std::cout << "Close command type correct" << std::endl;
    }
    if (CommandType::OPEN_COMMAND == a.getCommandType()) {
        std::cout << "Open command type correct" << std::endl;
    }
    if (ResponseType::TEXT_RESPONSE == resp.getResponseType()) {
        std::cout << "Text Response type correct" << std::endl;
    }
    if (a.isInitializedCorrect()) {
        std::cout << "Open command isInitializedCorrect" << std::endl;
    }
    TextResponse aaa;

    aaa = resptest();
    std::cout << aaa.logicErrorMessage() << std::endl;
}