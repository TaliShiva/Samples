#include <iostream>

#include "../../admin_module/include/admin_module.hpp"

using namespace gorynych;
using namespace admin_module;

int main(int argc, char *argv[]) {
    std::string userInput = "";
    std::string result = "";
    std::cout << std::endl << "> ";
    std::getline(std::cin, userInput);
    std::cout << std::endl;
    bool success = processUserCommand(userInput, result);
    if (success) {
        std::cout << result;
    } else {
        std::cerr << result;
    }
    std::cout << std::endl;
    return 0;
}

