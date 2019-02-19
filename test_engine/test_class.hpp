//
//

#pragma once

#include <string>
#include <sstream>

class human {
public:
    human(std::string name, std::string last_name){
        this->name = name;
        this->last_name = second_name;
    }
    std::string get_full_name()
    {
        std::ostingstream full_name;
        full_name << this->last_name << " " << this->name;
        return  full_name.str();
    }

private:
    std::string name;
    std::string last_name;
};



