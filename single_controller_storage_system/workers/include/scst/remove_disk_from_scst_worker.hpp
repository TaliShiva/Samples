//

#pragma once

#include <boost/algorithm/string/replace.hpp>
#include "abstract_scst_worker.hpp"
#include "../commands/remove_disk_from_scst_worker_command.hpp"
#include "../responses/remove_disk_from_scst_worker_response.hpp"

namespace gorynych {
    namespace workers {
        /**
         * @class RemoveDiskFromScstWorker
         * @see documentation AbstractScstWorker
         */
        class RemoveDiskFromScstWorker : public AbstractScstWorker {
        public:
            RemoveDiskFromScstWorker(const unsigned int id, const RemoveDiskFromScstWorkerCommand &command);
            /**
             * @brief sendNotification() @see documentation AbstractScstWorker
             */
            void sendNotification() override;
            /**
             * @brief doWork() AbstractScstWorker
             * @return @see documentation AbstractScstWorker
             */
            RemoveDiskFromScstWorkerResponse &doWork();
        private:
            RemoveDiskFromScstWorkerCommand command_;
            /**
             * @brief generateRemoveDiskString()
             * @return magic, more magic!!!
             */
            const std::string generateRemoveDiskString() const {
                auto magicString = "del_device ";
                return magicString + command_.vDiskName();
            }
            /**
             * @brief generateSystemErrorMessage()
             * @return @see documentation AbstractScstWorker
             */
            const std::string generateSystemErrorMessage();
            /**
             * @brief generateProgrammerErrorMessage()
             * @return @see documentation  AbstractScstWorker
             */
            const std::string generateProgrammerErrorMessage();
        };
    }
}



