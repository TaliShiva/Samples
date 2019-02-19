#include "../include/bcache_utils.hpp"

namespace gorynych {
    namespace utils {
        std::string getBcacheIndexFromPath(const std::string &path) {
            std::string out = path;
            startCustomProgramm("lsblk " + path + " | grep -Po bcache[0-9]+ | sed -n '1p' | cut -c 7-100", out);
            if ((out.find_first_not_of("0123456789") != std::string::npos)) {
                throw std::runtime_error("Ошибка получения bcache номера " + out);
            }
            return "/dev/bcache" + out;
        }
    }
}

