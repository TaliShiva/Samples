#include "../include/client.hpp"



namespace gorynych {
    namespace transport {
        using namespace boost::asio;

        Sender::Sender(std::string file) : file_(file) {

        }

        TextResponse Sender::sendCommand(OpenCommand &command) {
            std::string response = sendData(command);
            TextResponse resp(response);
            return resp;
        }

        TextResponse Sender::sendCommand(CloseCommand &command) {
            std::string response = sendData(command);
            TextResponse resp(response);
            return resp;
        }

        TextResponse Sender::sendCommand(CreateIscsiTargetCommand &command) {
            std::string response = sendData(command);
            TextResponse resp(response);
            return resp;
        }

        TextResponse Sender::sendCommand(RemoveIscsiTargetCommand &command) {
            return TextResponse(sendData(command));
        }

        TextResponse Sender::sendCommand(RemoveDiskFromScstCommand &command) {
            return TextResponse(sendData(command));
        }

        TextResponse Sender::sendCommand(CreateRaidCommand &command) {
            std::string response = sendData(command);
            TextResponse resp(response);
            return resp;
        }

        TextResponse Sender::sendCommand(DestroyRaidCommand &command) {
            std::string response = sendData(command);
            TextResponse resp(response);
            return resp;
        }

        TextResponse Sender::sendCommand(CreateLvmCommand &command) {
            std::string response = sendData(command);
            TextResponse resp(response);
            return resp;
        }

        TextResponse Sender::sendCommand(DestroyLvmCommand &command) {
            std::string response = sendData(command);
            TextResponse resp(response);
            return resp;
        }

        TextResponse Sender::sendCommand(DeleteLogicalVolumeCommand &command) {
            std::string response = sendData(command);
            TextResponse resp(response);
            return resp;
        }

        std::string Sender::sendData(ICommand &command) {
            if (!command.isInitializedCorrect()) {
                throw std::logic_error("Команда не инициализирована корректно");
            }
            std::string data = command.getCodedData();
            io_service service_;
            local::stream_protocol::endpoint ep(file_);
            local::stream_protocol::socket sock(service_);
            sock.connect(ep); // TODO: добавить обработку ошибок соединения и записи
            auto send_packet = Packet::buildPacket(data);
            sock.send(buffer(send_packet));
            // Получаем ответ
            char buf[Packet::MAX_PACKET_SIZE];
            size_t bytes = read(sock, buffer(buf), boost::bind(read_complete, buf, _1, _2));
            sock.close();
            std::string packet(buf, bytes);
            std::string returned_data = Packet::parsePacket(packet);
            // Debug
            // std::cout << returned_data << std::endl;
            return returned_data;
        }

        TextResponse Sender::sendCommand(ConnectDeviceToIscsiTargetCommand &command) {
            std::string response = sendData(command);
            std::cout << response << std::endl;
            return TextResponse(response);
        }

        TextResponse Sender::sendCommand(DisconnectDeviceToIscsiTargetCommand &command) {
            std::string response = sendData(command);
            TextResponse resp(response);
            return TextResponse(response);
        }

        TextResponse Sender::sendCommand(AddDiskToScstCommand &command) {
            std::string response = sendData(command);
            return TextResponse(response);
        }

        TextResponse Sender::sendCommand(CreateLogicalVolumeCommand &command) {
            std::string response = sendData(command);
            TextResponse resp(response);
            return resp;
        }

        TextResponse Sender::sendCommand(CreateCachedDiskCommand &command) {
            std::string response = sendData(command);
            TextResponse resp(response);
            return resp;
        }

        TextResponse Sender::sendCommand(DetachCachedDiskCommand &command) {
            std::string response = sendData(command);
            TextResponse resp(response);
            return resp;
        }

        TextResponse Sender::sendCommand(EnableIscsiTargetCommand &command) {
            return TextResponse(sendData(command));
        }

        TextResponse Sender::sendCommand(DisableIscsiTargetCommand &command) {
            return TextResponse(sendData(command));
        }

        ListRaidResponse Sender::sendCommand(ListRaidCommand &command) {
            return ListRaidResponse(sendData(command));
        }

        ListLogicalVolumeResponse Sender::sendCommand(ListLogicalVolumeCommand &command) {
            return ListLogicalVolumeResponse(sendData(command));
        }

        ListScstResponse Sender::sendCommand(ListScstCommand &command) {
            return ListScstResponse(sendData(command));
        }

    }
}