//
//

#ifndef OPEN_AND_CLOSE_FILES_TEST_CLASS_HPP
#define OPEN_AND_CLOSE_FILES_TEST_CLASS_HPP

#include <string>
#include <sstream>

class human {
public:
    human(std::string name, std::string last_name){
        this->name = name;
        this->last_name = last_name;
    }
    std::string get_full_name()
    {
        std::ostringstream full_name;
        full_name << this->last_name << " " << this->name;
        return  full_name.str();
    }

private:
    std::string name;
    std::string last_name;
};







#endif //OPEN_AND_CLOSE_FILES_TEST_CLASS_HPP
