
#include <iostream>

#include <boost/asio.hpp>

#include <fstream>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/bind.hpp>
#include <iomanip>


#include "packet.h"

#include "cmake-build-debug/command_api.pb.h"

using namespace boost::asio;

io_service service_;

std::string handle_request(std::string data) {
    gorynych::Command command;
    if(!command.ParseFromString(data)){
        throw std::runtime_error("Protobuf: Ошибка парсинга ответа");
    }
    // Обрабатываем ответ
    std::cout << "Команда клиента. " << std::endl;
    std::cout << "Тип команды: " << command.command_type()  << std::endl;
    std::cout << "Данные: " << command.blah()  << std::endl;

    gorynych::Response response;
    response.set_ok(true);
    response.set_data("Работает!");
    return response.SerializeAsString();
}
size_t read_complete(char * buf, const boost::system::error_code & err, size_t bytes)
{
    if ( err) {
        throw std::runtime_error("asio: Ошибка чтения из сокета: " + err.message());
    }
    // Получаем заголовок пакета
    if(bytes < Packet::HEADER_SIZE) {
        return Packet::HEADER_SIZE - bytes;
    }
    // Получаем пакет целиком
    auto packet_size = Packet::getBodySizeFromPacket(buf) + Packet::HEADER_SIZE;
    if(bytes < packet_size) {
        return packet_size - bytes;
    }
    return 0;
}

void handle_connections(const ::std::string &file)
{
    local::stream_protocol::acceptor  acceptor(service_, local::stream_protocol::endpoint(file));
    char buff[Packet::MAX_PACKET_SIZE];
    while ( true)
    {
        local::stream_protocol::socket sock(service_);
        acceptor.accept(sock); // TODO Добавить обработку ошибок соединения
        size_t bytes = read(sock, buffer(buff), boost::bind(read_complete,buff,_1,_2));//чтени от клиента
        std::string request(buff, bytes);//сообщение от клиента
        std::string request_data = Packet::parsePacket(request);//парсим сообщение от клиента
        
        auto response = Packet::buildPacket(handle_request(request_data));//создаем ответ клиенту
        
        sock.write_some(buffer(response));//пишем его в сокет
        sock.close();
    }
}

int main(int argc, char* argv[])
{
    auto file = "/tmp/testprotobuf";
    // Удаляем старый сокет от предидущей программы
    std::remove(file);
    // Запускаем обработку новых соединений
    handle_connections(file);
}

/*
void t() {

    namespace io = boost::iostreams;
    using src = io::file_descriptor_source;
    io::stream<src> fifo(src(open("./fifo", O_RDONLY), boost::iostreams::file_descriptor_flags::close_handle ));

    std::string word;
    size_t number = 0;
    while (fifo >> word) {
        std::cout << "word: " << ++number << "\t" << word << "\n";
    }

    boost::asio::streambuf b;
    std::ostream os(&b);

    info.SerializeToOstream(&os);

    boost::asio::write(*sock, b);
}

void read_tt() {
    boost::asio::io_service service_;
    int fifo_d = open("/tmp/fifo", O_CREAT);
    boost::asio::posix::stream_descriptor fifo(service_, fifo_d);
    while (true) {
        try {
            boost::asio::read(fifo, boost::asio::buffer(buffer));
        }
        catch (boost::system::system_error &err) {
// It loops here with "read: End of file" error
            std::cout << err.what() << std::endl;
        }
    }
}
 */