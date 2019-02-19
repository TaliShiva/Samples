#pragma once

#include "abstract_scst_worker.hpp"
#include "../commands/remove_iscsi_target_command.hpp"
#include "../responses/remove_iscsi_target_worker_response.hpp"

namespace gorynych{
    namespace workers{
    class RemoveIscsiTargetWorker : public AbstractScstWorker{
    public:
        RemoveIscsiTargetWorker(const unsigned int id, const RemoveIscsiTargetWorkerCommand &command);

        RemoveIscsiTargetWorkerResponse & doWork() override;

        void sendNotification() override;

    private:
        RemoveIscsiTargetWorkerCommand command_;
        /**
         * magic, more magic!!!
         * @return
         */
        const std::string generateStringFromRemoveTargetCommand();
        /**
         * @brief generateProgrammerErrorMessage()
         * @return @see documentation AbstractWorker
         */
        const std::string generateProgrammerErrorMessage();
        /**
         * @brief generateSystemErrorMessage()
         * @return @see documentation AbstractScstWorker
         */
        const std::string generateSystemErrorMessage();

        std::string lastSystemError_;
        std::string lastProgrammerError_;
    };
    }
}