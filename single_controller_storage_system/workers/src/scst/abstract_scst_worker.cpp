#include <fstream>
#include "../../include/scst/abstract_scst_worker.hpp"

namespace gorynych {
    namespace workers {
        AbstractScstWorker::AbstractScstWorker(const unsigned int id, const WORKER_TYPE type)
                : AbstractWorker(id, type) {}

        /**
         * @brief Запись в sysfs SCST
         * @param path путь файла для записи
         * @param payLoad текст записи
         * @return статус записи
         */
        bool AbstractScstWorker::writeToSysFs(const std::string &path, const std::string &payLoad) {
            std::ofstream device;
            device.open(path);
            if (device.is_open()) {
                device << payLoad;
                device.flush();
                std::cout << "Write to sysfs: path: " << path << "; payload: " << payLoad << std::endl; //Debug
                if (device.fail()) {
                    writeToSysFsError_ = strerror(errno);
                    device.close();
                    return false;
                }
                device.close();
                return true;
            }
            return false;
        }
    }
}

