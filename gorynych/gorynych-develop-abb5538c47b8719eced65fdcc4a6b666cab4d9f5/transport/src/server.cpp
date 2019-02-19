
#include "../include/server.hpp"
#include "../../logic_module/include/logic_module.hpp"
#include "../include/command/create_iscsi_target_command.hpp"
#include "../include/command/remove_iscsi_target_command.hpp"
#include "../include/command/create_raid_command.hpp"
#include "../include/command/destroy_raid_command.hpp"
#include "../include/command/delete_logical_volume_command.hpp"
#include "../include/command/create_cached_disk_command.hpp"
#include "../include/command/detach_cached_disk_command.hpp"

namespace gorynych {
    namespace transport {
        using namespace logic;

        Listener::Listener(std::string file) : file_(file) {

        }

        void Listener::listen() {
            std::remove(file_.c_str());
            handleConnections();
        }

        std::string Listener::handleRequest(std::string data) {
            using gorynych::transport::protobuf::Command;
            protobuf::Command command;
            try {
                if (!command.ParseFromString(data)) {
                    throw std::runtime_error("Protobuf: Ошибка парсинга команды от клиента");
                }
                TextResponse response;
                switch (command.type()) {
                    case Command::COMMAND_OPEN : {
                        OpenCommand openCommand(command);
                        std::cout << "Команда клиента Open. " << std::endl;
                        std::cout << "target_wwn: " << command.open().target_wwn() << std::endl;
                        std::cout << "device_path: " << command.open().device_path() << std::endl;
                        std::cout << "lun: " << command.open().lun() << std::endl;
                        response = logic_.execution(openCommand);
                    }
                        break;
                    case Command::COMMAND_CLOSE_ALL : {
                        CloseCommand closeCommand(command);
                        std::cout << "Команда клиента Close. " << std::endl;
                        std::cout << "target_wwn: " << command.close().target_wwn() << std::endl;
                        std::cout << "device_path: " << command.close().device_path() << std::endl;
                        std::cout << "lun: " << command.close().lun() << std::endl;
                        response = logic_.execution(closeCommand);
                    }
                        break;
                    case Command::COMMAND_CREATE_ISCSI_TARGET : {
                        CreateIscsiTargetCommand createIscsiTargetCommand(command);
                        std::cout << "Команда клиента createIscsiTarget. " << std::endl;
                        std::cout << "target_name: " << command.create_iscsi_target().target_name() << std::endl;
                        std::cout << "Command target_name: " << createIscsiTargetCommand.targetName() << std::endl;
                        std::cout << command.DebugString() << std::endl;
                        response = logic_.execution(createIscsiTargetCommand);
                    }
                        break;
                    case Command::COMMAND_CREATE_LVM : {
                        CreateLvmCommand createLvmCommand(command);
                        std::cout << "Команда клиента createLvmCommand. " << std::endl;
                        std::cout << "DebugString: " << command.DebugString() << std::endl;
                        response = logic_.execution(createLvmCommand);
                    }
                        break;
                    case Command::COMMAND_ADD_DISK_TO_SCST: {
                        AddDiskToScstCommand addDiskToScstCommand(command);
                        response = logic_.execution(addDiskToScstCommand);
                    }
                        break;
                    case Command::COMMAND_REMOVE_ISCSI_TARGET: {
                        transport::RemoveIscsiTargetCommand removeIscsiTargetCommand(command);
                        response = logic_.execution(removeIscsiTargetCommand);
                    }
                        break;
                    case Command::COMMAND_REMOVE_DISK_FROM_SCST: {
                        transport::RemoveDiskFromScstCommand removeDiskFromScstCommand(command);
                        response = logic_.execution(removeDiskFromScstCommand);
                    }
                        break;
                    case Command::COMMAND_CREATE_RAID : {
                        CreateRaidCommand createRaidCommand(command);
                        response = logic_.execution(createRaidCommand);
                    }
                        break;
                    case Command::COMMAND_DESTROY_RAID : {
                        DestroyRaidCommand destroyRaidCommand(command);
                        response = logic_.execution(destroyRaidCommand);
                    }
                        break;
                    case Command::COMMAND_CREATE_LOGICAL_VOLUME : {
                        CreateLogicalVolumeCommand createLogicalVolumeCommand(command);
                        response = logic_.execution(createLogicalVolumeCommand);
                    }
                        break;
                    case Command::COMMAND_DESTROY_LVM : {
                        DestroyLvmCommand destroyLvmCommand(command);
                        response = logic_.execution(destroyLvmCommand);
                    }
                        break;
                    case Command::COMMAND_CREATE_CACHED_DISK: {
                        CreateCachedDiskCommand createCachedDiskCommand(command);
                        response = logic_.execution(createCachedDiskCommand);
                    }
                        break;
                    case Command::COMMAND_DETACH_CACHED_DISK: {
                        DetachCachedDiskCommand detachCachedDiskCommand(command);
                        response = logic_.execution(detachCachedDiskCommand);
                    }
                        break;
                    case Command::COMMAND_DELETE_LOGICAL_VOLUME : {
                        DeleteLogicalVolumeCommand deleteLogicalVolumeCommand(command);
                        response = logic_.execution(deleteLogicalVolumeCommand);
                    }
                        break;
                    case Command::COMMAND_DISABLE_ISCSI_TARGET: {
                        transport::DisableIscsiTargetCommand disableIscsiTargetCommand(command);
                        response = logic_.execution(disableIscsiTargetCommand);
                    }
                        break;
                    case Command::COMMAND_CONNECT_DEVICE_TO_ISCSI_TARGET: {
                        ConnectDeviceToIscsiTargetCommand connectDeviceToIscsiTargetCommand(command);
                        response = logic_.execution(connectDeviceToIscsiTargetCommand);
                    }
                        break;
                    case Command::COMMAND_DISCONNECT_DEVICE_TO_ISCSI_TARGET: {
                        DisconnectDeviceToIscsiTargetCommand disconnectDeviceToIscsiTargetCommand(command);
                        response = logic_.execution(disconnectDeviceToIscsiTargetCommand);
                    }
                        break;
                    case Command::COMMAND_LIST_RAID: {
                        try {
                            auto listRaidResponse = logic_.execution(ListRaidCommand(command));
                            if (!listRaidResponse.isInitializedCorrect()) {
                                throw std::runtime_error("Ответ от логики не инициализирован корректно");
                            }
                            return listRaidResponse.getCodedData();
                        } catch (std::exception &exception) {
                            ListRaidResponse listRaidResponse;
                            std::cerr << exception.what() << std::endl;
                            return listRaidResponse.getCodedData();
                        }
                    }
                        break;
                    case Command::COMMAND_LIST_LOGICAL_VOLUME: {
                        try {
                            auto listLogicalVolumeResponse = logic_.execution(ListLogicalVolumeCommand(command));
                            if (!listLogicalVolumeResponse.isInitializedCorrect()) {
                                throw std::runtime_error("Ответ от логики не инициализирован корректно");
                            }
                            return listLogicalVolumeResponse.getCodedData();
                        } catch (std::exception &exception) {
                            ListRaidResponse listRaidResponse;
                            std::cerr << exception.what() << std::endl;
                            return listRaidResponse.getCodedData();
                        }
                    }
                        break;
                    case Command::COMMAND_LIST_SCST: {
                        try {
                            auto listScstResponse = logic_.execution(ListScstCommand(command));
                            if (!listScstResponse.isInitializedCorrect()) {
                                throw std::runtime_error("Ответ от логики не инициализирован корректно");
                            }
                            return listScstResponse.getCodedData();
                        } catch (std::exception &exception) {
                            ListRaidResponse listRaidResponse;
                            std::cerr << exception.what() << std::endl;
                            return listRaidResponse.getCodedData();
                        }
                    }
                        break;
                    case Command::COMMAND_ENABLE_ISCSI_TARGET: {
                        EnableIscsiTargetCommand enableIscsiTargetCommand(command);
                        response = logic_.execution(enableIscsiTargetCommand);
                    }
                        break;
                    default:
                        response.setLogicErrorMessage("Неизвестная команда");
                        std::cout << "Неизвестная команда" << std::endl;
                        break;
                }
                if (!response.isInitializedCorrect()) {
                    throw std::runtime_error("Ответ от логики не инициализирован корректно");
                }
                return response.getCodedData();
            } catch (std::exception &exception) {
                std::cerr << "Exception" << std::endl;
                std::cerr << exception.what() << std::endl;
                TextResponse response;
                response.setSuccess(false);
                response.setLogicErrorMessage("Exception!");
                response.setSystemErrorMessage(std::string("Some error:") + exception.what());
                return response.getCodedData();
            } catch (...) {
                std::cerr << "Unknown Exception" << std::endl;
                TextResponse response;
                response.setSuccess(false);
                response.setLogicErrorMessage("Exception!");
                response.setSystemErrorMessage(std::string("Unknown Exception"));
                return response.getCodedData();
            }
        }

        void Listener::handleConnections() {
            local::stream_protocol::acceptor acceptor(ioservice_, local::stream_protocol::endpoint(file_));
            char buff[Packet::MAX_PACKET_SIZE] = {0};
            while (true) {
                local::stream_protocol::socket sock(ioservice_);
                std::cout << "Debug: socket filename: " << file_ << std::endl;
                acceptor.accept(sock); // TODO Добавить обработку ошибок соединения
                size_t bytes = read(sock, buffer(buff), boost::bind(read_complete, buff, _1, _2));
                std::string request(buff, bytes);
                std::string request_data = Packet::parsePacket(request);
                auto response = Packet::buildPacket(handleRequest(request_data));
                std::cout << "Debug: raw response: " << response << std::endl;
                sock.write_some(buffer(response));
                sock.close();
            }
        }
    }
}