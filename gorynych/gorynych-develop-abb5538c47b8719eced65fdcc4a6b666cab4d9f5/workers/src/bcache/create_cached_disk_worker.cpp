#include "../../include/commands/create_cached_disk_worker_command.hpp"
#include "../../include/bcache/create_cached_disk_worker.hpp"
#include "../../../utils/include/start_custom_programm.hpp"

#include <regex>

namespace gorynych {
    namespace workers {

        CreateCachedDiskWorker::CreateCachedDiskWorker(const unsigned int id,
                                                       const CreateCachedDiskWorkerCommand &command):
                command_(command) { }

        inline std::string trim(std::string& str, char trimmedChar = '\n', bool needLeftTrim = true)
        {
            if(needLeftTrim) {
                str.erase(0, str.find_first_not_of(trimmedChar));
            }
            str.erase(str.find_last_not_of(trimmedChar) + 1);
            return str;
        }

        inline std::string getUnmountCommand(const std::string &path) {
            return "umount " + path + " || /bin/true"; // do not fail if device is unmounted
        }

        inline std::string getFormatBaseDiskCommand(const CreateCachedDiskWorkerCommand &command) {
            return "make-bcache -B " + command.baseDevicePath();
        }

        inline std::string getFormatCachingDiskCommand(const CreateCachedDiskWorkerCommand &command) {
            return "make-bcache -C " + command.cachingDevicePath();
        }

        inline std::string getCsetUuidCommand(const CreateCachedDiskWorkerCommand &command) {
            return "bcache-super-show " + command.cachingDevicePath() + " | grep cset.uuid | cut -c 12-1000";
        }

        inline std::string getAttachCacheCommand(const std::string &csetUuid, int bcacheIndex) {
            return "echo " + csetUuid + " > /sys/block/bcache" + std::to_string(bcacheIndex) + "/bcache/attach";
        }

        inline std::string getBcacheIndexCommand() {
            return "ls -l -t /sys/block | grep -Po bcache[0-9]+ | sed -n '1p' | cut -c 7-100";
        }

        inline std::string getSetWritebackCommand(const CreateCachedDiskWorkerCommand &command, int bcacheIndex) {
            if(command.cachingMode() == CachingMode::Writeback) {
                return "echo writeback > /sys/block/bcache" + std::to_string(bcacheIndex) + "/bcache/cache_mode";
            } else { // command.cachingMode() == CachingMode::Writethrough
                return "echo writethrough > /sys/block/bcache" + std::to_string(bcacheIndex) + "/bcache/cache_mode";
            }
        }

        SilentWorkerResponse *CreateCachedDiskWorker::doWork() {
            using utils::startCustomProgramm;
            std::string lastCommandOutput="";

            int unmountCachingCode = startCustomProgramm(getUnmountCommand(command_.cachingDevicePath()), lastCommandOutput);
            trim(lastCommandOutput);
            if(unmountCachingCode != 0) {
                return new SilentWorkerResponse(false, lastCommandOutput, "failed to unmount caching device");
            }
            lastCommandOutput = "";

            int unmountBaseCode = startCustomProgramm(getUnmountCommand(command_.baseDevicePath()), lastCommandOutput);
            trim(lastCommandOutput);
            if(unmountBaseCode != 0) {
                return new SilentWorkerResponse(false, lastCommandOutput, "failed to unmount base device");
            }
            lastCommandOutput = "";

            int formatCachingDeviceCode = startCustomProgramm(getFormatCachingDiskCommand(command_), lastCommandOutput);
            trim(lastCommandOutput);
            if(formatCachingDeviceCode != 0) {
                return new SilentWorkerResponse(false, lastCommandOutput, "failed to format caching device");
            }
            lastCommandOutput = "";

            int formatBaseDiskCode = startCustomProgramm(getFormatBaseDiskCommand(command_), lastCommandOutput);
            trim(lastCommandOutput);
            if(formatBaseDiskCode != 0) {
                return new SilentWorkerResponse(false, lastCommandOutput, "failed to format base device");
            }
            lastCommandOutput = "";

            int getCsetUuidRawCode = startCustomProgramm(getCsetUuidCommand(command_), lastCommandOutput);
            trim(lastCommandOutput);
            if(getCsetUuidRawCode != 0) {
                return new SilentWorkerResponse(false, lastCommandOutput, "failed get UUID of caching device set");
            }
            std::string csetUUID = lastCommandOutput;
            lastCommandOutput = "";

            // FIXME by and large does not guarantee to be the last device added in async mode
            int bcacheIndex=-1;
            int getBcacheDevicesSortedByDateCode = -1;
            for (int i = 0; i < 5 && lastCommandOutput == ""; i++) {
                usleep(500000);
                getBcacheDevicesSortedByDateCode = startCustomProgramm(getBcacheIndexCommand(), lastCommandOutput);
                trim(lastCommandOutput);
            }
            if(getBcacheDevicesSortedByDateCode != 0) {
                return new SilentWorkerResponse(false, lastCommandOutput, "failed get last added bcache device index");
            } else {
                try {
                    std::cout << "bcacheid:" << lastCommandOutput << "end" << std::endl;
                    if(lastCommandOutput == "0") {
                        bcacheIndex = 0;
                    } else {
                        bcacheIndex = std::stoi(lastCommandOutput);
                    }

                } catch (std::exception const& ex) {
                    return new SilentWorkerResponse(false, ex.what(), "failed parse last added bcache device index");
                }
            }
            lastCommandOutput = "";

            int attachCacheCommand = startCustomProgramm(getAttachCacheCommand(csetUUID, bcacheIndex), lastCommandOutput);
            trim(lastCommandOutput);
            if(attachCacheCommand != 0) {
                return new SilentWorkerResponse(false, lastCommandOutput, "failed to attach caching device by UUID");
            }
            lastCommandOutput = "";

            int getSetWritebackCode = startCustomProgramm(getSetWritebackCommand(command_, bcacheIndex), lastCommandOutput);
            trim(lastCommandOutput);
            if(getSetWritebackCode != 0) {
                return new SilentWorkerResponse(false, lastCommandOutput, "failed to set write mode for cache");
            }
            lastCommandOutput = "";
            return new SilentWorkerResponse(true ,"", "");
        }
    }
}