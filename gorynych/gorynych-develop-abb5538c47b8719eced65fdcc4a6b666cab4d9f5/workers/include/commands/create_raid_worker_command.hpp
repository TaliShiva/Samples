//
// Created by user on 13.03.17.
//

#pragma once

#include <vector>
#include <string>
#include "abstract_worker_command.hpp"

namespace gorynych {
    namespace workers {
        class CreateRaidWorkerCommand : public AbstractWorkerCommand{
        public:
            /**
             * @param deviceCount - кол-во устройств в raid-массиве
             * @param raidLevel - тип raid-массива
             * @param devices  - имена устройств добавляемых в raid-массив
             * @param raidPath - путь самого raid-массива
             */
            CreateRaidWorkerCommand(const unsigned int deviceCount, const unsigned int raidLevel,
                                    const std::vector<std::string> devices, const std::string raidPath);

        private:
            const unsigned int deviceCount_;
            const unsigned int raidLevel_;
            const std::vector<std::string> devices_;
            const std::string raidPath_;




        public:

            const unsigned int raidLevel() const;
            const unsigned int deviceCount() const;
            const std::vector<std::string> &devices() const;
            const std::string &raidPath() const;
        };
    }
}