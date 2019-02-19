#pragma once

#include "abstract_scst_worker.hpp"
#include "../responses/enable_iscsi_target_worker_response.hpp"
#include "../commands/enable_iscsi_target_worker_command.hpp"
#include "../abstract_worker.hpp"

namespace gorynych {
    namespace workers {
        class EnableIscsiTargetWorker : public AbstractScstWorker {
        public:
            EnableIscsiTargetWorker(const unsigned int id,
                                    const EnableIscsiTargetWorkerCommand &command);
            void sendNotification() override;
            EnableIscsiTargetWorkerResponse &doWork();

        private:
            EnableIscsiTargetWorkerCommand command_;
            const std::string generatePathForEnableIscsiTargetCommand() const{
                auto pathSuffix = "/enabled";
                return iscsiTargetsPathPrefix_ + command_.targetName() + pathSuffix;
            }
            const std::string generateSystemErrorMessage();
            const std::string generateProgrammerErrorMessage();
        };
    }

}



