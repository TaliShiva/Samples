#include "../../include/commands/detach_cached_disk_worker_command.hpp"
#include "../../include/bcache/detach_cached_disk_worker.hpp"
#include "../../../utils/include/start_custom_programm.hpp"

#include <boost/algorithm/string/trim_all.hpp>

#include <boost/filesystem.hpp>


namespace gorynych {
    namespace workers {
        using namespace boost::filesystem;
        DetachCachedDiskWorker::DetachCachedDiskWorker(const unsigned int id,
                                                       const DetachCachedDiskWorkerCommand &command):
                command_(command) { }

        inline std::string getDiskNameFromPath(const std::string& path) {
            std::string delimiter = "/";
            std::string name = path;
            size_t pos = 0;
            std::string token;
            while ((pos = name.find(delimiter)) != std::string::npos) {
                token = name.substr(0, pos);
                name.erase(0, pos + delimiter.length());
            }
            return name;
        }

        inline std::string getStopBaseDiskCommand(const DetachCachedDiskWorkerCommand &command) {
            path path(canonical(command.baseDevicePath()));
            return "echo 1 > /sys/block/" + path.filename().string() + "/bcache/stop";
        }

        inline std::string getCsetUuidCommand(const DetachCachedDiskWorkerCommand &command) {
            return "bcache-super-show " + command.cachingDevicePath() + " | grep cset.uuid | cut -c 12-1000";
        }

        inline std::string getStopCachingDiskCommand(const std::string &csetUuid) {
            return "echo 1 > /sys/fs/bcache/" + csetUuid + "/stop";
        }

        inline std::string getWipeDiskCommand(const std::string& path) {
            return "wipefs -a " + path;
        }

        SilentWorkerResponse *DetachCachedDiskWorker::doWork() {
            using utils::startCustomProgramm;
            std::string lastCommandOutput="";

            int stopBaseDiskCode = startCustomProgramm(getStopBaseDiskCommand(command_), lastCommandOutput);
            boost::algorithm::trim_all_if(lastCommandOutput, boost::algorithm::is_any_of("\n"));
            if(stopBaseDiskCode != 0) {
                return new SilentWorkerResponse(false, lastCommandOutput, "failed to stop base device");
            }

            int getCsetUuidRawCode = startCustomProgramm(getCsetUuidCommand(command_), lastCommandOutput);
            boost::algorithm::trim_all_if(lastCommandOutput, boost::algorithm::is_any_of("\n"));
            if(getCsetUuidRawCode != 0) {
                return new SilentWorkerResponse(false, lastCommandOutput, "failed get UUID of caching device set");
            }
            std::string csetUUID = lastCommandOutput;

            int stopCachingDiskCode = startCustomProgramm(getStopCachingDiskCommand(csetUUID), lastCommandOutput);
            boost::algorithm::trim_all_if(lastCommandOutput, boost::algorithm::is_any_of("\n"));
            if(stopCachingDiskCode != 0) {
                return new SilentWorkerResponse(false, lastCommandOutput, "failed to stop caching device");
            }

            int wipeBaseDiskCode = startCustomProgramm(getWipeDiskCommand(command_.baseDevicePath()), lastCommandOutput);
            if(wipeBaseDiskCode != 0) {
                return new SilentWorkerResponse(false, lastCommandOutput, "failed to wipe base device");
            }

            int wipeCachingDiskCode = startCustomProgramm(getWipeDiskCommand(command_.cachingDevicePath()), lastCommandOutput);
            boost::algorithm::trim_all_if(lastCommandOutput, boost::algorithm::is_any_of("\n"));
            if(wipeCachingDiskCode != 0) {
                return new SilentWorkerResponse(false, lastCommandOutput, "failed to wipe caching device");
            }

            return new SilentWorkerResponse(true ,"", "");
        }
    }
}
