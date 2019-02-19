
#include <iostream>
#include <memory>
#include "../include/transport_api.hpp"
#include "../../cmake-build-debug/command_api.pb.h"

using namespace gorynych::transport;
/**
 * Пока вместо гугл-тестов
 * Проверяем что заглушки работают
 */
 void test_function(std::string& test) {
    std::cout << "test_function" << std::endl;
}
int main() {
    std::shared_ptr<std::string> shared_string(new std::string("dddddd"));
    test_function(*shared_string);
    gorynych::transport::protobuf::Command a;
    a.set_type(gorynych::transport::protobuf::Command::COMMAND_OPEN);
    a.mutable_open()->set_device_path("/dev/path");
    a.mutable_open()->set_target_wwn("wwn_name");
    a.mutable_open()->set_lun(1);
    if(a.IsInitialized()){
        std::cout << "IS OK: " << a.DebugString() << std::endl;
    } else {
        std::cout << "IS NOT INITIALIZED: " << a.DebugString() << std::endl;
    }
    gorynych::transport::protobuf::Response b;
    b.set_type(gorynych::transport::protobuf::Response::RESPONSE_TEXT);
    b.mutable_text()->set_success(true);
    b.mutable_text()->set_logic_error_message("logic error message");
    b.mutable_text()->set_system_error_message("system error message");
    if(b.IsInitialized()){
        std::cout << "IS OK: " << b.DebugString() << std::endl;
    } else {
        std::cout << "IS NOT INITIALIZED: " << b.DebugString() << std::endl;
    }

}