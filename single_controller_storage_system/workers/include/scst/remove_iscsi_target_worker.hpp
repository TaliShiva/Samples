
#include "abstract_scst_worker.hpp"
#include "../commands/remove_iscsi_target_command.hpp"

namespace gorynych{
    namespace workers{
    class RemoveIscsiTargetWorker : public AbstractScstWorker{
    public:
        RemoveIscsiTargetWorker(const unsigned int id, const RemoveIscsiTargetWorkerCommand &command);

        IWorkerResponse &doWork() override;

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