//
// Created by user on 13.03.17.
//
#pragma once

#include <iostream>
#include <unistd.h>


namespace gorynych {
    namespace utils {

        /**
         * @brief - Запуск сторонней программы
         * @param programm_command - строка запуска програмы
         * @param programm_output - вывод программы
         * @return - код ответа программы
         */
        int startCustomProgramm(const std::string programm_command, std::string &programm_output);

        int startCustomProgrammWithoutErrorOut(const std::string programm_command, std::string &programm_output);

    }
}
