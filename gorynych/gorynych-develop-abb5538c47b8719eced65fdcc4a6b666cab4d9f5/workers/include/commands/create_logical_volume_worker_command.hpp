
//

#pragma once

#include <string>
#include "abstract_worker_command.hpp"

namespace gorynych {
    namespace workers {
        /**
         * Создание логического диска на Volume Gruop'е в LVM
         */
        class CreateLogicalVolumeWorkerCommand : public AbstractWorkerCommand {
        public:
            /**
             *
             * @param logicalVolumeName_ Название логического диска
             * @param logicalVolumeSize_ Размер логического диска
             * @param parentVolumeGroupName_ Имя VolumeGroup в которой нужно создать логический диск
             */
            CreateLogicalVolumeWorkerCommand(const std::string logicalVolumeName_,
                                             const std::string logicalVolumeSize_,
                                             const std::string parentVolumeGroupName_);

            const std::string &logicalVolumeName() const;

            const std::string &logicalVolumeSize() const;

            const std::string &parentVolumeGroupName() const;

        private:
            const std::string logicalVolumeName_;
            const std::string logicalVolumeSize_;
            const std::string parentVolumeGroupName_;
        };
    }
}


