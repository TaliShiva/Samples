#pragma once

#include <boost/algorithm/string/replace.hpp>
#include "abstract_worker.hpp"
#include "../../transport/include/transport_api.hpp"
#include "abstract_worker_old.hpp"

namespace gorynych {
    namespace workers {
        class CloseWorker : public AbstractWorkerOld {
        public:
            CloseWorker(const unsigned int id, const WORKER_TYPE_OLD workerType = WORKER_TYPE_OLD::CLOSE_WORKER);

            IResponse & doWork() override;

            void sendNotification() override;

            void init(const CloseCommand &command);

            /**
             * @brief Возвращает путь к устройству которое должно быть экспортировано
             * @returnпуть к устройству
             */
            inline const std::string devicePath() const { return devicePath_; }

            /**
             * @brief Устанавливает путь к устройству которое должно быть экспортировано
             * @param path
             */
            inline void setDevicePath(const std::string path) {
                devicePath_ = path;
                deviceScstName_ = boost::replace_all_copy(path, "/", "_");
            }

            /**
             * @brief Возвращает имя таргета который должен быть создан
             * @return имя таргета
             */
            inline const std::string targetName() const { return targetName_; }

            /**
             * @brief Устанавливает имя таргета который должен быть создан
             * @param name имя таргета
             */
            inline void setTargetName(const std::string targetName) { targetName_ = targetName; }

            /**
             * @brief Возвращает номер LUN с которым должкен быть экспортирован диск
             * @return LUN
             */
            inline size_t lun() const { return lunNumber_; }

            /**
             * @brief Устанавливает номер LUN с которым должен быть экспортирован диск
             * @param lun LUN
             */
            inline void setLun(size_t lun) { lunNumber_ = lun; }

        private:
            /**
             * @brief devicePath_ - путь к устройству
             */
            std::string devicePath_;
            /**
             * @brief targetName_ - имя таргета
             */
            std::string targetName_;
            /**
             * @brief lunNumber_ - номер LUN'a
             */
            size_t lunNumber_;
            /**
             * @brief nvCache_ - магическая хрень
             */
            int nvCache_ = 1;
            /**
             * @brief iscsiPath_ - путь к ISCSI, по нему лежат файлы, в которые пишутся команды
             */
            const std::string iscsiPath_ = "/sys/kernel/scst_tgt/targets/iscsi/mgmt";


        private:
            TextResponse response_;

            int removeLun();

            int removeTarget();

            int removeDisk();

            std::string deviceScstName_;

            void getLastSystemError();

            const std::string generatePathForRemoveLun() const;

            const std::string generateRemoveLunString() const;

            const std::string generateRemoveTargetString() const;

            const std::string vDiskPath_ = "/sys/kernel/scst_tgt/handlers/vdisk_blockio/mgmt";

            const std::string generateRemoveDiskString() const;
        };

    }
}

