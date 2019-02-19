
#include "../include/network.hpp"

namespace gorynych {
    namespace transport {
        using namespace boost::asio;
        
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


    }
}