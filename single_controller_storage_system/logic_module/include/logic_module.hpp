#pragma  once
#include "../../transport/include/transport_api.hpp"
#include "../../worker_manager/include/worker_manager.hpp"
#include "../../transport/include/command/disconnect_device_to_iscsi_target_command.hpp"
#include "state/system_state.hpp"

namespace gorynych {
    namespace logic {
        using namespace transport;
        using namespace workers;
        using namespace worker_manager;
        class Logic {
        public:
            Logic();

            //Получаю пакет


            /**
             * @brief Построить TextResponse на основе любого worker response, который наследует AbstractWorkerResponse
             * @param workerResponse ответ worker'а
             * @return TextResponse - ответ для уровня транспорта
             */
            TextResponse buildTextResponse(const AbstractWorkerResponse &workerResponse);

            TextResponse buildTextResponse(bool success, const std::string &programmerError, const std::string &systemError);

            TextResponse execution(const OpenCommand &command);

            TextResponse execution(const CloseCommand &command);

            TextResponse execution(const CreateIscsiTargetCommand &command);

            TextResponse execution(const AddDiskToScstCommand &command);

            TextResponse execution(const RemoveIscsiTargetCommand &command);
            /**
             * @brief execution(const RemoveDiskFromScstCommand &command)
             * @param command команда удаленния диска из SCST
             * @return статус выполнения операции и служебные сообщения @see TextResponse
             */
            TextResponse execution(const RemoveDiskFromScstCommand &command);

            TextResponse execution(const CreateRaidCommand &command);

            TextResponse execution(const DestroyRaidCommand &command);

            TextResponse execution(const CreateLvmCommand &command);

            TextResponse execution(const CreateLogicalVolumeCommand &command);

            TextResponse execution(const DestroyLvmCommand &command);

            TextResponse execution(const CreateCachedDiskCommand &command);

            TextResponse execution(const DetachCachedDiskCommand &command);

            TextResponse execution(const DeleteLogicalVolumeCommand &command);

            TextResponse execution(const DisableIscsiTargetCommand &command);

            TextResponse execution(const ConnectDeviceToIscsiTargetCommand &command);

            TextResponse execution(const DisconnectDeviceToIscsiTargetCommand &command);

            TextResponse execution(const EnableIscsiTargetCommand &command);

            /**
             *
             * @param command
             * @return
             */
            const ListRaidResponse execution(const ListRaidCommand &command);

            /**
             *
             * @param command
             * @return
             */
            const ListLogicalVolumeResponse execution(const ListLogicalVolumeCommand &command);

            /**
             *
             * @param command
             * @return
             */
            const ListScstResponse execution(const ListScstCommand &command);
        private:
            static unsigned int id_;

            static unsigned int createNewId();

            WorkerManager *workerManager_;
            const std::unique_ptr<SystemState> systemState_;
        private:
            typedef std::tuple<bool, std::string, std::string> TupleSuccessVgNameLvName;

            TupleSuccessVgNameLvName parseDevicePath(const std::string &path);
        };
    }
}
