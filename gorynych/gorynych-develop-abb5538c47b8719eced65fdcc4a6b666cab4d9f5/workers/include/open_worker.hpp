#pragma once

#include <boost/algorithm/string/replace.hpp>
#include "abstract_worker.hpp"
#include "../../transport/include/command.hpp"
#include "../../transport/include/command/open.hpp"
#include "abstract_worker_old.hpp"
#include <string>
namespace gorynych {
    namespace workers {
        using namespace transport;

        class OpenWorker : public AbstractWorkerOld {
        public:
            OpenWorker(const unsigned int id, const WORKER_TYPE_OLD workerType = WORKER_TYPE_OLD::OPEN_WORKER);


            IResponse &doWork();

            void init(const OpenCommand &command);
        public:
            void sendNotification() override;

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
            /**
             * @brief  addDevice() добавляет устройтсво куда-то там
             * @return 0, есди операция выполнена успешна, иначе код ошибки
             */
            int addDevice();

            /**
             * @brief createTarget() - создает непосредственно таргет
             * @return 0, есди операция выполнена успешна, иначе код ошибки
             */
            int createTarget();

            /**
             * @brief connectDeviceToTarget() - подключает устройство к таргету
             * @return 0, есди операция выполнена успешна, иначе код ошибки
             */
            int connectDeviceToTarget();

            /**
             * @brief enableTarget() - включает таргет
             * @return  0, есди операция выполнена успешна, иначе код ошибки
             */
            int enableTarget();

            /**
             * @brief - имя SCSI цстройства
             */
            std::string deviceScstName_;

            /**
             * @brief - магический путь к файлам
             */
            const std::string fileIoHandlerPath_ = "/sys/kernel/scst_tgt/handlers/vdisk_fileio/mgmt";

            /**
             * @brief - основной путь к файлам
             */
            const std::string pathPrefix_ = "/sys/kernel/scst_tgt/targets/iscsi/";

            /**
             * @brief generateStringForAddCommand() - генерирует строку, которая будет записана в файл при выполнении
             * команды addDevice()
             * @return - сгенерированная строка
             */
            const std::string generateStringForAddCommand() const;

            /**
             * @brief generateStringForCreateTargetCommand()  - генерирует строку, которая будет записана
             * в файл при выполнении команды createTarget()
             * @return - сгенерированная строка
             */
            const std::string generateStringForCreateTargetCommand() const;

            /**
             * @brief generateStringForConnectDeviceToTargetCommand()  - генерирует строку,
             * которая будет записана в файл при выполнении команды connectDeviceToTarget()
             * @return - сгенерированная строка
             */
            const std::string generateStringForConnectDeviceToTargetCommand() const;

            /**
             * @brief generatePathForConnectDeviceToTargetCommand()  - генерирует строку,
             * содержащую путь к  файлу, в который будет произведена запись  при выполнении
             * команды connectDeviceToTarget()
             * @return - сгенерированная строка
             */
            const std::string generatePathForConnectDeviceToTargetCommand() const;


            /**
             * @brief generatePathForEnableTargetCommand() генерирует строку,
             * содержащую путь к  файлу, в который будет произведена запись  при выполнении
             * команды enableTarget()
             * @return - сгенерированная строка
             */
            const std::string generatePathForEnableTargetCommand() const;


            TextResponse response_;
        };

    }
}

