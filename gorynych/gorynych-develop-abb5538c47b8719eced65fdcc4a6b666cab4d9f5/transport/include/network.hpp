
#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <boost/asio.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "../../cmake-build-debug/command_api.pb.h"
#include "packet.hpp"


namespace gorynych {
    namespace transport {
/**
 * @brief Проверяет, что пакет получен полностью.
 * @param buf Буффер с данными
 * @param err Ошибка
 * @param bytes Полный размер полученных данных
 * @return Сколько данных еще необходимо получить
 */
        size_t read_complete(char *buf, const boost::system::error_code &err, size_t bytes);
    }
}