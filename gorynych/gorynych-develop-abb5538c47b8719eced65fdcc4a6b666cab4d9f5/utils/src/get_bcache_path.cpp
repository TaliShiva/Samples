//

#include "../include/get_bcache_path.hpp"
namespace gorynych {
    namespace utils {
        const std::string getBcachePath(const std::string &baseDevicePath){
            return std::string("/dev/bcahe0");
        }
    }
}