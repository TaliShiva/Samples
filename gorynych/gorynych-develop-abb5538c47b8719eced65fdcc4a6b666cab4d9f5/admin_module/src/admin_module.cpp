#include "../include/admin_module.hpp"

#include "../../transport/include/transport_api.hpp"
#include "../../transport/include/client.hpp"
#include "../../transport/include/struct/list/state_items.hpp"


#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>

namespace gorynych {
    namespace admin_module {
        static std::string OPEN_COMMAND = "open";
        static std::string CLOSE_COMMAND = "close";
        static std::string CREATE_ISCSI_TARGET_COMMAND = "create_iscsi_target";
        static std::string CREATE_LVM_COMMAND = "create_lvm";
        static std::string ADD_DISK_TO_SCST_COMMAND = "add_disk_to_scst";
        static std::string REMOVE_ISCSI_TARGET_COMMAND = "remove_iscsi_target";
        static std::string REMOVE_DISK_FROM_SCST_COMMAND = "remove_disk_from_scst";
        static std::string CREATE_RAID_COMMAND = "create_raid";
        static std::string CREATE_CACHED_DISK_COMMAND = "create_cached_disk";
        static std::string DETACH_CACHED_DISK_COMMAND = "detach_cached_disk";
        static std::string DESTROY_RAID_COMMAND = "destroy_raid";
        static std::string CREATE_LOGICAL_VOLUME_COMMAND = "create_logical_volume";
        static std::string DESTROY_LVM_COMMAND = "destroy_lvm";
        static std::string DELETE_LOGICAL_VOLUME_COMMAND = "delete_logical_volume";
        static std::string DISABLE_ISCSI_TARGET_COMMAND = "disable_iscsi_target";
        static std::string CONNECT_DEVICE_TO_ISCSI_TARGET_COMMAND = "connect_device_to_iscsi_target";
        static std::string DISCONNECT_DEVICE_TO_ISCSI_TARGET_COMMAND = "disconnect_device_from_iscsi_target";
        static std::string ENABLE_ISCSI_TARGET_COMMAND = "enable_iscsi_target";

        static std::string LIST_RAID_COMMAND = "list_raid";
        static std::string LIST_LOGICAL_VOLUME_COMMAND = "list_logical_volume";
        static std::string LIST_SCST_COMMAND = "list_scst";
        inline bool isInteger(const std::string &s) {
            if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) {
                return false;
            }
            char *p;
            strtol(s.c_str(), &p, 10);
            return (*p == 0);
        }

        bool isValidCreateCachingDeviceFunc(const std::vector<std::string> &tokens) {
            unsigned long size = tokens.size();
            if(size < 3 || tokens[0] != CREATE_CACHED_DISK_COMMAND) {
                return false;
            } else if(size == 3) {
                return true;
            } else if(size == 4) {
                return tokens[3] == "lfu" || tokens[3] == "fifo" || tokens[3] == "random";
            } else if(size == 5) {
                return (tokens[3] == "lfu" || tokens[3] == "fifo" || tokens[3] == "random")
                       && (tokens[4] == "writeback" || tokens[4] == "writethrough");
            } else {
                return false;
            }
        }

        bool processUserCommand(const std::string &command, std::string &result) {
            std::istringstream buf(command);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> tokens(beg, end);
            transport::Sender sender("/tmp/gorynych_control.sock"); // FIXME вынести из модуля путь к сокету

            transport::TextResponse textResponse;
            bool isValidOpen = tokens.size() == 4 && tokens[0] == OPEN_COMMAND && isInteger(tokens[3]);
            bool isValidClose = tokens.size() == 4 && tokens[0] == CLOSE_COMMAND && isInteger(tokens[3]);

            bool isValidCreateIscsiTarget = tokens.size() == 2 && tokens[0] == CREATE_ISCSI_TARGET_COMMAND;
            bool isValidCreateRaid = tokens.size() >= 4 && tokens[0] == CREATE_RAID_COMMAND && isInteger(tokens[2]) &&
                                                                                               isInteger(tokens[3]);
            bool isValidCreateCachingDevice = isValidCreateCachingDeviceFunc(tokens);
            bool isValidDetachCachingDevice = tokens.size() == 3 && tokens[0] == DETACH_CACHED_DISK_COMMAND;
            bool isValidRemoveIscsiTarget = tokens.size() == 2 && tokens[0] == REMOVE_ISCSI_TARGET_COMMAND;

            bool isValidAddDiskToScst = tokens.size() == 2 && tokens[0] == ADD_DISK_TO_SCST_COMMAND;
            bool isValidRemoveDiskFromScst = tokens.size() == 2 && tokens[0] == REMOVE_DISK_FROM_SCST_COMMAND;

            bool isValidDestroyRaid = tokens.size() >= 2 && tokens[0] == DESTROY_RAID_COMMAND;

            bool isValidCreateLvm = tokens.size() == 3 && tokens[0] == CREATE_LVM_COMMAND;
            bool isValidDestroyLvm = tokens.size() == 3 && tokens[0] == DESTROY_LVM_COMMAND;
            bool isValidCreateLogicalVolume = tokens.size() == 4 && tokens[0] == CREATE_LOGICAL_VOLUME_COMMAND;
            bool isValidDeleteLogicalVolume = tokens.size() == 3 && tokens[0] == DELETE_LOGICAL_VOLUME_COMMAND;
            bool isValidDisableIscsiTarget = tokens.size() == 2 && tokens[0] == DISABLE_ISCSI_TARGET_COMMAND;
            bool isValidConnectDeviceToIscsiTarget =
                    tokens.size() == 4 && tokens[0] == CONNECT_DEVICE_TO_ISCSI_TARGET_COMMAND && isInteger(tokens[3]);
            bool isValidDisconnectDeviceToIscsiTarget =
                    tokens.size() == 4 && tokens[0] == DISCONNECT_DEVICE_TO_ISCSI_TARGET_COMMAND &&
                    isInteger(tokens[3]);
            bool isValidListRaidCommand = tokens.size() == 1 && tokens[0] == LIST_RAID_COMMAND;
            bool isValidListLogicalVolumeCommand = tokens.size() == 1 && tokens[0] == LIST_LOGICAL_VOLUME_COMMAND;
            bool isValidListScstCommand = tokens.size() == 1 && tokens[0] == LIST_SCST_COMMAND;

            bool isValidEnableIscsiTarget = tokens.size() == 2 && tokens[0] == ENABLE_ISCSI_TARGET_COMMAND;

            if (!isValidOpen && !isValidClose && !isValidCreateIscsiTarget && !isValidRemoveIscsiTarget
                && !isValidAddDiskToScst && !isValidAddDiskToScst
                && !isValidRemoveDiskFromScst && !isValidCreateRaid && !isValidDestroyRaid
                && !isValidCreateLvm && !isValidCreateLogicalVolume && !isValidDestroyLvm
                && !isValidDeleteLogicalVolume && !isValidDisableIscsiTarget
                && !isValidConnectDeviceToIscsiTarget && !isValidDisconnectDeviceToIscsiTarget
                && !isValidCreateCachingDevice && !isValidDetachCachingDevice
                && !isValidEnableIscsiTarget
                && !isValidListRaidCommand && !isValidListLogicalVolumeCommand
                && !isValidListScstCommand
                    ) {

                result = "please specify a command:\n";
                result += "create_iscsi_target <target_name> | \n";
                result += "remove_iscsi_target <target_name> \n";
                result += "create_raid </dev/md{X}> <raid_level> <device count> [<devices>...] \n";
                result += "destroy_raid </dev/md{X}> [<devices>...] \n";
                result += "create_lvm <volume_group_name> </dev/md{X}>\n";
                result += "destroy_lvm <volume_group_name> </dev/md{X}>\n";
                result += "add_disk_to_scst </dev/{Volume_Group}/{Logical_Volume}>\n";
                result += "remove_disk_from_scst </dev/{Volume_Group}/{Logical_Volume}>\n";
                result += "create_logical_volume <parent_volume_group> <logical_volume_name> <logical_volume_size> \n";
                result += "delete_logical_volume <volume_group_name> <logical_volume_name>\n";
                result += "connect_device_to_iscsi_target </dev/{Volume_Group}/{Logical_Volume}> <target_name> <lun_number>\n";
                result += "disconnect_device_from_iscsi_target </dev/{Volume_Group}/{Logical_Volume}> <target_name> <lun_number>\n";
                result += "disable_iscsi_target <target_name>\n";
                result += "create_cached_disk </dev/{Volume_Group}/{Logical_Volume}> <caching_device_path> "
                        "[(lfu|fifo|random)] [(writeback|writethrough)]\n";
                result += "enable_iscsi_target <target_name>\n";
                result += "detach_cached_disk </dev/{Volume_Group}/{Logical_Volume}> <caching_device_path>\n";
                result += "list_raid\n";
                result += "list_logical_volume\n";
                result += "list_scst\n";
                return false;
            } else if (isValidOpen) {
                transport::OpenCommand openCommand;
                openCommand.setDevicePath(tokens[1]);
                openCommand.setTargetName(tokens[2]);
                int lun = std::stoi(tokens[3]);
                openCommand.setLun(lun);
                textResponse = sender.sendCommand(openCommand);
            } else if (isValidClose) {
                transport::CloseCommand closeCommand;
                closeCommand.setDevicePath(tokens[1]);
                closeCommand.setTargetName(tokens[2]);
                int lun = std::stoi(tokens[3]);
                closeCommand.setLun(lun);
                textResponse = sender.sendCommand(closeCommand);
            } else if (isValidCreateIscsiTarget) {
                transport::CreateIscsiTargetCommand createIscsiTargetCommand;
                createIscsiTargetCommand.setTargetName(tokens[1]);
                textResponse = sender.sendCommand(createIscsiTargetCommand);
            } else if (isValidConnectDeviceToIscsiTarget) {
                transport::ConnectDeviceToIscsiTargetCommand connectDeviceToIscsiTargetCommand;
                connectDeviceToIscsiTargetCommand.setDevicePath(tokens[1]);
                connectDeviceToIscsiTargetCommand.setTargetName(tokens[2]);
                connectDeviceToIscsiTargetCommand.setLunNumber(std::stoi(tokens[3]));
                textResponse = sender.sendCommand(connectDeviceToIscsiTargetCommand);
            } else if (isValidDisconnectDeviceToIscsiTarget) {
                transport::DisconnectDeviceToIscsiTargetCommand disconnectDeviceToIscsiTargetCommand;
                disconnectDeviceToIscsiTargetCommand.setDevicePath(tokens[1]);
                disconnectDeviceToIscsiTargetCommand.setTargetName(tokens[2]);
                disconnectDeviceToIscsiTargetCommand.setLunNumber(std::stoi(tokens[3]));
                textResponse = sender.sendCommand(disconnectDeviceToIscsiTargetCommand);
            } else if (isValidAddDiskToScst) {
                transport::AddDiskToScstCommand addDiskToScstCommand;
                addDiskToScstCommand.setDevicePath(tokens[1]);
                textResponse = sender.sendCommand(addDiskToScstCommand);
            } else if (isValidRemoveIscsiTarget) {
                transport::RemoveIscsiTargetCommand removeIscsiTargetCommand;
                removeIscsiTargetCommand.setTargetName(tokens[1]);
                textResponse = sender.sendCommand(removeIscsiTargetCommand);
            } else if (isValidRemoveDiskFromScst) {
                transport::RemoveDiskFromScstCommand removeDiskFromScstCommand;
                removeDiskFromScstCommand.setDevicePath(tokens[1]);
                textResponse = sender.sendCommand(removeDiskFromScstCommand);
            } else if (isValidCreateRaid) {
                transport::CreateRaidCommand createRaidCommand;
                createRaidCommand.setRaidPath(tokens[1]);
                createRaidCommand.setRaidLevel(std::stoi(tokens[2]));
                createRaidCommand.setDevicesCount(std::stoi(tokens[3]));
                std::vector<std::string> devices;
                for (std::vector<std::string>::iterator it = tokens.begin() + 4; it != tokens.end(); ++it) {
                    devices.push_back(*it);
                }
                createRaidCommand.setDevices(devices);
                textResponse = sender.sendCommand(createRaidCommand);
            } else if(isValidCreateCachingDevice) {
                transport::CreateCachedDiskCommand createCachedDiskCommand;
                createCachedDiskCommand.setBaseDevicePath(tokens[1]);
                createCachedDiskCommand.setCachingDevicePath(tokens[2]);
                if(tokens.size() > 3) {
                    createCachedDiskCommand.setCachingAlgorithm(tokens[3]);
                }
                if(tokens.size() > 4) {
                    createCachedDiskCommand.setCachingMode(tokens[4]);
                }
                textResponse = sender.sendCommand(createCachedDiskCommand);
            } else if(isValidDetachCachingDevice) {
                transport::DetachCachedDiskCommand detachCachedDiskCommand;
                detachCachedDiskCommand.setBaseDevicePath(tokens[1]);
                detachCachedDiskCommand.setCachingDevicePath(tokens[2]);
                textResponse = sender.sendCommand(detachCachedDiskCommand);
            } else if (isValidDestroyRaid) {
                transport::DestroyRaidCommand destroyRaidCommand;
                destroyRaidCommand.setRaidPath(tokens[1]);
                std::vector<std::string> devices;
                for (std::vector<std::string>::iterator it = tokens.begin() + 2; it != tokens.end(); ++it) {
                    devices.push_back(*it);
                }
                destroyRaidCommand.setDevices(devices);
                textResponse = sender.sendCommand(destroyRaidCommand);
            } else if (isValidCreateLvm) {
                transport::CreateLvmCommand createLvmCommand;
                createLvmCommand.setVolumeGroupName(tokens[1]);
                createLvmCommand.setDevicePath(tokens[2]);
                textResponse = sender.sendCommand(createLvmCommand);
            } else if (isValidCreateLogicalVolume) {
                transport::CreateLogicalVolumeCommand createLogicalVolumeCommand;
                createLogicalVolumeCommand.setParentVolumeGroupName(tokens[1]);
                createLogicalVolumeCommand.setLogicalVolumeName(tokens[2]);
                createLogicalVolumeCommand.setlogicalVolumeSize(tokens[3]);
                textResponse = sender.sendCommand(createLogicalVolumeCommand);
            } else if (isValidDestroyLvm) {
                transport::DestroyLvmCommand destroyLvmCommand;
                destroyLvmCommand.setVolumeGroupName(tokens[1]);
                destroyLvmCommand.setDevicePath(tokens[2]);
                textResponse = sender.sendCommand(destroyLvmCommand);
            } else if (isValidDeleteLogicalVolume) {
                transport::DeleteLogicalVolumeCommand deleteLogicalVolumeCommand;
                deleteLogicalVolumeCommand.setVolumeGroupName(tokens[1]);
                deleteLogicalVolumeCommand.setLogicalVolumeName(tokens[2]);
                textResponse = sender.sendCommand(deleteLogicalVolumeCommand);
            } else if (isValidEnableIscsiTarget) {
                transport::EnableIscsiTargetCommand enableIscsiTargetCommand;
                enableIscsiTargetCommand.setTargetName(tokens[1]);
                textResponse = sender.sendCommand(enableIscsiTargetCommand);
            } else if (isValidDisableIscsiTarget) {
                transport::DisableIscsiTargetCommand disableIscsiTargetCommand;
                disableIscsiTargetCommand.setTargetName(tokens[1]);
                textResponse = sender.sendCommand(disableIscsiTargetCommand);
            } else if (isValidListRaidCommand) {
                transport::ListRaidCommand listRaidCommand;
                transport::ListRaidResponse response = sender.sendCommand(listRaidCommand);
                print(response);
                return true;
            } else if (isValidListLogicalVolumeCommand) {
                transport::ListLogicalVolumeCommand listLogicalVolumeCommand;
                transport::ListLogicalVolumeResponse response = sender.sendCommand(listLogicalVolumeCommand);
                print(response);
                return true;
            } else if (isValidListScstCommand) {
                transport::ListScstCommand listScstCommand;
                transport::ListScstResponse response = sender.sendCommand(listScstCommand);
                print(response);
                return true;
            }
            result = "";
            if (textResponse.success()) {
                result = "Успешно\n";
                return true;
            } else {
                result = "an error occurred while processing the command; see the log for details\n";
                result += textResponse.logicErrorMessage() + "\n";
                result += textResponse.systemErrorMessage() + "\n";
                return false;
            }
        }

        std::string appendColumn(const std::string input, unsigned int columnSize) {
            std::string output = input;
            output.append(abs(columnSize - input.size()), ' ');
            return output;
        }

        void print(const transport::ListScstResponse response) {
            std::string output;
            const unsigned int columnSize = 40;
            const unsigned int columnCount = 4;
            output += appendColumn("targetName", columnSize) +
                      appendColumn("enabled", columnSize) +
                      appendColumn("lunNumber", columnSize) +
                      appendColumn("vDiskName", columnSize) +
                      "\n";
            output += getSeparator(columnCount * columnSize);
            for (auto item : response.targetItemList()) {
                output += appendColumn(item.targetName, columnSize) +
                          appendColumn(item.enabled ? "enabled" : "disabled", columnSize) + "\n";
                for (auto lunItem : item.lunItems) {
                    output += appendColumn("", columnSize);
                    output += appendColumn("", columnSize);
                    output += appendColumn(std::to_string(lunItem.lunNumber), columnSize);
                    output += appendColumn(lunItem.vDiskName, columnSize);
                    output += "\n";
                }
            }
            std::cout << output << getSeparator(columnCount * columnSize);
        }



        void print(const transport::ListRaidResponse response) {
            std::string output;
            const unsigned int columnSize = 20;
            const unsigned int columnCount = 5;
            output += appendColumn("VG Name", columnSize) +
                      appendColumn("raid name", columnSize) +
                      appendColumn("raid level", columnSize) +
                      appendColumn("raid size", columnSize) +
                      appendColumn("Use percentage", columnSize) +
                      "\n";

            output += getSeparator(columnSize * columnCount);
            auto raidList = response.raidItemList();
            for (auto item : raidList) {
                output += appendColumn(item.volumeGroupName, columnSize);
                output += appendColumn(item.raidPath, columnSize);
                output += appendColumn(item.raidLevel, columnSize);
                output += appendColumn(item.raidSize, columnSize);
                output += appendColumn(item.volumeGroupUsedPercentile, columnSize);
                output += "\n";
            }
            std::cout << output << getSeparator(columnSize * columnCount);
        }

        void print(const transport::ListLogicalVolumeResponse response) {
            std::string output;
            const unsigned int columnSize = 20;
            const unsigned int columnCount = 6;
            output += appendColumn("logicalVolumeName", columnSize) +
                      appendColumn("volumeGroupName", columnSize) +
                      appendColumn("logicalVolumeSize", columnSize) +
                      appendColumn("vDiskName", columnSize) +
                      appendColumn("cached", columnSize) +
                      appendColumn("cachedDeviceName", columnSize) +
                      "\n";
            output += getSeparator(columnSize * columnCount);
            for (auto item : response.logicalVolumeItemList()) {
                output += appendColumn(item.logicalVolumeName, columnSize) +
                          appendColumn(item.volumeGroupName, columnSize) +
                          appendColumn(item.logicalVolumeSize, columnSize) +
                          appendColumn(item.vDiskName, columnSize) +
                          appendColumn(item.cached ? "on" : "off", columnSize) +
                          appendColumn(item.cachedDeviceName, columnSize) +
                          "\n";
            }
            std::cout << output << getSeparator(columnSize * columnCount);
        }

        std::string getSeparator(const unsigned int size) {
            std::string result = "";
            result.append(size, '-');
            return result += "\n";
        }
    }
}