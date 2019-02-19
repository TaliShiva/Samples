#pragma once

namespace gorynych {
    namespace workers {
        /**
         * @enum WorkerCommandType - описание типов команд для воркеров
         */
        enum class WorkerCommandType {
            CREATE_TARGET,
            CREATE_RAID,
            DESTROY_RAID,
            ADD_DISK_TO_SCST,
            REMOVE_TARGET,
            REMOVE_DISC_FROM_SCST,
            CREATE_LVM,
            DESTROY_LVM,
            CREATE_LOGICAL_VOLUME,
            CREATE_CACHED_DISK,
            DETACH_CACHED_DISK,
            DELETE_LOGICAL_VOLUME,
            DISABLE_ISCSI_TARGET_WORKER,
            CONNECT_DEVICE_TO_ISCSI_TARGET,
            DISCONNECT_DEVICE_TO_ISCSI_TARGET,
            ENABLE_ISCSI_TARGET_WORKER,
        };

        class IWorkerCommand {

        };
    }
}


