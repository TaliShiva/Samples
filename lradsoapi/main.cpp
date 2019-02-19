
#include <cctype>
#include <rados/librados.hpp>
#include <iostream>
#include <string>

void exit_func(int ret);

librados::Rados rados;

int main(int argc, const char **argv) {
    int ret = 0;

    // Определяем переменные
    const char *pool_name = "rbd";
    std::string object_string("Я представляю некий атомарный объект\n");
    std::string attribute_string("I am an atomic attribute\n");
    std::string object_name("atomic_object");
    librados::IoCtx io_ctx;

    // Создаём необходимый объект Rados и инициализируем его
    {
        ret = rados.init("admin"); // По умолчанию применяем client.admin
        keyring
        if (ret < 0) {
            std::cerr << "Failed to initialize rados! error " << ret << std::endl;
            ret = EXIT_FAILURE;
        }
    }

    // Считываем файл настроек ceph config в определённом для него по умолчанию местоположении
    ret = rados.conf_read_file("/etc/ceph/ceph.conf");
    if (ret < 0) {
        std::cerr << "Отказ в проведении синтаксического разбора настроек "
                  << "! Ошибка" << ret << std::endl;
        ret = EXIT_FAILURE;
    }

    // Соединяемся с нашим кластером Ceph
    ret = rados.connect();
    if (ret < 0) {
        std::cerr << "Отказ в соединении со своим кластером! Ошибка " << ret
                  << std::endl;
        ret = EXIT_FAILURE;
    } else {
        std::cout << "Подключён к кластеру Ceph" << std::endl;
    }

    // Создаём соединение с необходимым пулом Rados
    ret = rados.ioctx_create(pool_name, io_ctx);
    if (ret < 0) {
        std::cerr << "Отказ в соединении с пулом! Ошибка: " << ret
                  << std::endl;
        ret = EXIT_FAILURE;
    } else {
        std::cout << "Подключён к пулу: " << pool_name <<
                  std::endl;
    }

}

librados::bufferlist object_bl; // Инициализация списка буферов
object_bl.
append(object_string); // Добавление строки текста нашего объекта в список буфера
librados::ObjectWriteOperation write_op; // Создание транзакции записи
write_op.
write_full(object_bl); // Запись нашего списка буфера в транзакцию
std::cout << "Object: " << object_name << " был записан в транзакции" <<
std::endl;
char c;
std::cout << "Вы хотите прервать транзакцию? (Y/N)? ";
std::cin >>
c;
if (
toupper( c )
== 'Y') {
std::cout << "Транзакция была прервана, поэтому в действительности объект не записан" <<
std::endl;
exit_func(99);
}
librados::bufferlist attr_bl; // Инициализация другого списка буфера
attr_bl.
append(attribute_string); // Добавляем наш атрибут в список буфера
write_op.setxattr("atomic_attribute", attr_bl); // Записываем на атрибут в своей транзакции
std::cout << "Атрибут был записан в транзакцию"
<<
std::endl;
ret = io_ctx.operate(object_name, &write_op); // Фиксируем транзакцию
if (ret < 0) {
std::cerr << "failed to do compound write! error " << ret
<<
std::endl;
ret = EXIT_FAILURE;
} else {
std::cout << "Мы записали транзакцию, содержащую наши объект и атрибут" << object_name <<
std::endl;
}
}

void exit_func(int ret) {
    // Выполняем очистку и выход
    rados.shutdown();
    exit(ret);
}