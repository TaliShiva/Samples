//

#pragma once

#include "abstract_worker_command.hpp"
#include <string>
namespace gorynych {
    namespace workers {
        class RemoveDiskFromScstWorkerCommand : public AbstractWorkerCommand {
        public:
            /**
             * @brief конструктор команды, с параметрами
             * @param vDiskName - собственно путь к устройству, которое мы будем удалять
             */
            RemoveDiskFromScstWorkerCommand(const std::string &vDiskName)
                    :  AbstractWorkerCommand(WorkerCommandType::REMOVE_DISC_FROM_SCST), vDiskName_(vDiskName) {
            }
        private:
            RemoveDiskFromScstWorkerCommand() : AbstractWorkerCommand(WorkerCommandType::REMOVE_DISC_FROM_SCST) {}

            const std::string vDiskName_;
        public:
            inline const std::string &vDiskName() const {
                return vDiskName_;
            }
        };
    }
}


