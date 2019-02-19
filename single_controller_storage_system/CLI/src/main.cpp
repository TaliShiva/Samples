#include <iostream>
#include <string>

#include "../../admin_module/include/admin_module.hpp"
using namespace gorynych;
using namespace admin_module;

int main (int argc, char* argv[] ) {
    std::string userInput = "";
    std::string result = "";
    std::getline (std::cin, userInput);
    bool success = processUserCommand (userInput, result);
    if (success) {
        std::cout << result;
    } else {
        std::cerr << result;
    }
    return 0;
}

