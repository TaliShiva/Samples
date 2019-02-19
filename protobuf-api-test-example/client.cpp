
#include <boost/asio.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "cmake-build-debug/command_api.pb.h"
#include "packet.h"


namespace gorynych {
    using namespace boost::asio;

    io_service service_;
    auto file = "/tmp/testprotobuf";
    local::stream_protocol::endpoint ep(file);

/**
 * @brief Проверяет, что пакет получен полностью.
 * @param buf Буффер с данными
 * @param err Ошибка
 * @param bytes Полный размер полученных данных
 * @return Сколько данных еще необходимо получить
 */
    size_t read_complete(char *buf, const boost::system::error_code &err, size_t bytes) {
        if (err) {
            throw std::runtime_error("asio: Ошибка чтения из сокета: " + err.message());
        }
        // Получаем заголовок пакета
        if (bytes < Packet::HEADER_SIZE) {
            return Packet::HEADER_SIZE - bytes;
        }
        // Получаем пакет целиком
        auto packet_size = Packet::getBodySizeFromPacket(buf) + Packet::HEADER_SIZE;
        if (bytes < packet_size) {
            return packet_size - bytes;
        }
        return 0;
    }

/**
 * @brief Отправляет команду и получает ответ.
 * @param data Сырые данные команды
 * @return Сырые данные ответа
 */
    std::string send_command(const std::string &data) {
        local::stream_protocol::socket sock(service_);
        sock.connect(ep); // TODO: добавить обработку ошибок соединения и записи
        auto send_packet = Packet::buildPacket(data);//создаем пакет для сервера
        sock.send(buffer(send_packet));//посылаем его в сокет

        char buf[Packet::MAX_PACKET_SIZE];
        size_t bytes = read(sock, buffer(buf), boost::bind(read_complete, buf, _1, _2));// Получаем ответ

        std::string packet(buf, bytes);//из буфера принятые данные
        std::string returned_data = Packet::parsePacket(packet);//парсим эти данные
        // Debug
        // std::cout << returned_data << std::endl;
        sock.close();//закрываем сокет
        return returned_data;
    }

/**
 * @brief Создает команду test
 * @return Сырые данные команды
 */
    std::string build_command_test() {
        gorynych::Command test;
        test.set_command_type(gorynych::Command::ADD_DISK_TO_TARGET);
        test.set_blah("fooo!");
        if (!test.IsInitialized()) {
            throw std::logic_error("Protobuf: Ошибка сборки команды");
        }
        return test.SerializeAsString();
    }

/**
 * @brief Обрабатывает ответ на команду.
 * @param data Сырые данные ответа
 */
    void parse_response_from_command_test(const std::string &data) {
        gorynych::Response response;//создаём объект такого же типа, что и посылал сервер
        if (!response.ParseFromString(data)) {
            throw std::runtime_error("Protobuf: Ошибка парсинга ответа");
        }
        // Обрабатываем ответ

        std::cout << "Ответ от сервера. " << std::endl;
        std::cout << "Статус выполнения команды: " << response.ok() << std::endl;
        std::cout << "Данные: " << response.data() << std::endl;
    }
}
int main(int argc, char* argv[])
{
    auto command = gorynych::build_command_test();
    auto returned_data = gorynych::send_command(command);
    gorynych::parse_response_from_command_test(returned_data);//создаём объект протобуфа
    return 0;
}