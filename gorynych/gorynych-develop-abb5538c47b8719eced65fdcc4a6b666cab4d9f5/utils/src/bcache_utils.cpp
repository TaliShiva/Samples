#include "../include/bcache_utils.hpp"
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/trim_all.hpp>

namespace gorynych {
    namespace utils {
        std::string getBcacheIndexFromPath(const std::string &path) {
            std::string out = path;
            startCustomProgramm("lsblk " + path + " | grep -Po bcache[0-9]+ | sed -n '1p' | cut -c 7-100", out);
            boost::algorithm::trim_all_if(out, boost::algorithm::is_any_of("\n"));
            boost::algorithm::trim(out);
            if ((out.find_first_not_of("0123456789") != std::string::npos)) {
                throw std::runtime_error("Ошибка получения bcache номера " + out);
            }
            return "/dev/bcache" + out;
        }
    }
}

