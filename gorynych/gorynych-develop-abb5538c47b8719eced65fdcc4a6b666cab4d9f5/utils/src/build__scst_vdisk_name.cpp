//

#include <boost/algorithm/string/replace.hpp>
#include "../include/build__scst_vdisk_name.hpp"
namespace gorynych {
    namespace utils {

        const std::string buildScstVdiskName(const std::string &devicePath) {
            return boost::replace_all_copy(devicePath, "/", "_") ;
        }
    }

}
