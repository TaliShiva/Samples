//
// Created by alex on 3/13/17.
//

#pragma once

#include <string>
#include "abstract_worker_command.hpp"

namespace gorynych {
    namespace workers {
        /**
         * Класс команды для передачи данных в Worker @see class CreateLvmWorker
         */
        class CreateLvmWorkerCommand : public AbstractWorkerCommand {
        public:
            /**
             *
             * @param lvmName Название LVM Volume Group
             * @param devicePath Путь к устройству на котором нужно создать LVM
             */
            CreateLvmWorkerCommand(const std::string lvmName, const std::string devicePath);

            /**
             *
             * @return Название LVM Volume Group
             */
            const std::string getLvmName_() const;

            /**
             *
             * @return Путь к устройству на котором нужно создать LVM
             */
            const std::string getDevicePath_() const;

        private:
            const std::string lvmName_;
            const std::string devicePath_;

        };

    }
}




