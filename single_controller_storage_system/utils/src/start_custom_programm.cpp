//
// Created by user on 13.03.17.
//
#include "../include/start_custom_programm.hpp"

namespace gorynych {
    namespace utils {

        int startCustomProgramm(const std::string programm_command, std::string &programm_output) {
            const std::string err_to_out = " 2>&1";
            FILE *in;
            char buff[512];
            std::string result_command = programm_command + err_to_out;
            in = popen(result_command.c_str(), "r");
            programm_output.clear();
            while (fgets(buff, sizeof(buff), in) != NULL) {
                programm_output += buff;
                programm_output += "\n";

            }
            auto err = pclose(in);
            return WEXITSTATUS(err);
        }

        int startCustomProgrammWithoutErrorOut(const std::string programm_command, std::string &programm_output) {
            FILE *in;
            char buff[512];
            std::string result_command = programm_command;
            in = popen(result_command.c_str(), "r");
            programm_output.clear();
            while (fgets(buff, sizeof(buff), in) != NULL) {
                programm_output += buff;
                programm_output += "\n";

            }
            auto err = pclose(in);
            return WEXITSTATUS(err);
        }
    }
}