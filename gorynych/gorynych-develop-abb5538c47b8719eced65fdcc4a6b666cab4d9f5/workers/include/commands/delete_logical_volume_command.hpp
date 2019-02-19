//
//

#pragma once
#include <string>
#include <vector>
#include "abstract_worker_command.hpp"

namespace gorynych {
    namespace workers {
        /**
         * Класс команды для передачи данных в Worker @see class DeleteLogicalVolumeWorker
         */
        class DeleteLogicalVolumeWorkerCommand : public AbstractWorkerCommand {
        public:
            /**
             *
             * @param volume_group_name Название LVM Volume Group
             * @param devicePath Путь к устройству на котором нужно создать LVM
             */
            DeleteLogicalVolumeWorkerCommand(const std::string volume_group_name, const std::string logical_volume_name);
            /**
             * @return Название LVM Volume Group
             */
            const std::string& volumeGroupName() const;
            /**
             * @return Названия Логических дисков для удаления
             */
            const std::string & logicalVolumeName() const;

        private:
            const std::string volumeGroupName_;
            const std::string logicalVolumeName_;

        };

    }
}




