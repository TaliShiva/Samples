
#include "../include/transport_api.hpp"
#include "../include/client.hpp"

int main(int argc, char *argv[]) {
    using namespace gorynych::transport;
    std::string file = "/tmp/gorynych_control.sock";
    Sender sender1(file);
    OpenCommand command1;
    CloseCommand command2;

    command1.setDevicePath(argv[2]);
    command1.setTargetName(argv[1]);
    command1.setLun(std::stoi((std::string)argv[3]));
    TextResponse response1 = sender1.sendCommand(command1);
    std::cout << "programmerErrorMessage: " << response1.logicErrorMessage() << std::endl;
    std::cout << "systemErrorMessage: " << response1.systemErrorMessage() << std::endl;
    if (response1.success()) {
        std::cout << "Response success!" << std::endl;
    }
    TextResponse response2 = sender1.sendCommand(command2);
    std::cout << "programmerErrorMessage: " << response2.logicErrorMessage() << std::endl;
    std::cout << "systemErrorMessage: " << response2.systemErrorMessage() << std::endl;
    if (response2.success()) {
        std::cout << "Response success!" << std::endl;
    }
    return 0;
}