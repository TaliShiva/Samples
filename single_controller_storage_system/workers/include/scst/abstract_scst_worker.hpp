#pragma once

#include "../abstract_worker.hpp"

namespace gorynych {
    namespace workers {
        class AbstractScstWorker : public AbstractWorker {
        public:
            AbstractScstWorker(const unsigned int id, const WORKER_TYPE type = WORKER_TYPE::ABSTRACT_SCST_WORKER);

        protected:
            /**
             * @brief - магический путь к файлам
             */
            const std::string fileIoHandlerPath_ = "/sys/kernel/scst_tgt/handlers/vdisk_fileio/mgmt";
            const std::string vDiskPath_ =         "/sys/kernel/scst_tgt/handlers/vdisk_blockio/mgmt";

            /**
             * @brief - основной путь к файлам
             */
            const std::string iscsiTargetsPathPrefix_ = "/sys/kernel/scst_tgt/targets/iscsi/";
            /**
             * @brief - путь к ISCSI management файлу,  в который пишутся команды
             */
            const std::string iscsiManagementPath_ = "/sys/kernel/scst_tgt/targets/iscsi/mgmt";

        protected:
            bool writeToSysFs(const std::string &path, const std::string &payLoad);

            virtual const std::string generateSystemErrorMessage() = 0;

            virtual const std::string generateProgrammerErrorMessage() = 0;

            /**
             * @brief writeToSysFsError_ текст ошибки системы при записи в sysfs
             */
            std::string writeToSysFsError_;
        };
    }
}

