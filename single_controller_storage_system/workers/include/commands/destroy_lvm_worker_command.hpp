
//

#pragma once

#include <string>
#include "abstract_worker_command.hpp"

namespace gorynych {
    namespace workers {
        /**
         * Класс команды для передачи данных в Worker @see class  DestroyLvmWorker
         */
        class DestroyLvmWorkerCommand : public AbstractWorkerCommand {
        public:
            /**
             *
             * @param lvmName Название LVM Volume Group
             * @param devicePath Путь к устройству на котором нужно уничтожить LVM
             */
            DestroyLvmWorkerCommand(const std::string lvmName, const std::string devicePath);

            /**
             *
             * @return Название LVM Volume Group
             */
            const std::string getLvmName_() const;

            /**
             *
             * @return Путь к устройству на котором нужно уничтожить LVM
             */
            const std::string getDevicePath_() const;

        private:
            const std::string lvmName_;
            const std::string devicePath_;
        };

    }
}
