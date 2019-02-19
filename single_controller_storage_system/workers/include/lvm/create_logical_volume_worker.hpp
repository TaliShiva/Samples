
//

#pragma once


#include "../abstract_worker.hpp"
#include "../commands/create_logical_volume_worker_command.hpp"
#include "../responses/create_logical_volume_response.hpp"

namespace gorynych {
    namespace workers {
        class CreateLogicalVolumeWorker: public AbstractWorker {
        public:

            CreateLogicalVolumeWorker(const unsigned int id, CreateLogicalVolumeWorkerCommand command);
            CreateLogicalVolumeWorkerResponse &doWork();
            void sendNotification() override;
        private:

            CreateLogicalVolumeWorkerCommand command_;

            std::string getCreateLogicalVolumeProgramString() const;
        };

    }
}