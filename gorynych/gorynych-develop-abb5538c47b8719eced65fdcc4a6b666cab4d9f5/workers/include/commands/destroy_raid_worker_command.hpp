//
// Created by user on 15.03.17.
//

#pragma once

#include "abstract_worker_command.hpp"
#include <string>
#include <vector>

namespace gorynych {
    namespace workers {
        class DestroyRaidWorkerCommand : public AbstractWorkerCommand {
        public:
            /**
             *
             * @brief - Удаление raid-массива
             * @param devices - устройства которые нужно удалить
             * @param raidPath  - путь к raid-массиву который мы удаляем
             */
            DestroyRaidWorkerCommand(const std::vector<std::string> devices, const std::string raidPath);

            const std::vector<std::string> &devices() const;
            const std::string &raidPath() const;

        private:

            const std::vector<std::string> devices_;
            const std::string raidPath_;
        };
    }
}



