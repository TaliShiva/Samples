#pragma once

#include <string>
#include "../../transport/include/transport_api.hpp"

/**
 * @brief user command handler
 * @param command user command
 * @param errorDescription empty string for no error
 * @return true for successful execution, false otherwise
 */
namespace gorynych {
    namespace admin_module {
        bool processUserCommand(const std::string &command, std::string &result);

        bool isValidCreateCachingDeviceFunc(const std::vector<std::string> &tokens);

        void print(const transport::ListScstResponse response);

        void print(const transport::ListRaidResponse response);

        void print(const transport::ListLogicalVolumeResponse response);

        std::string getSeparator(const unsigned int size);

        std::string appendColumn(const std::string input, unsigned int columnSize);
    }
}

