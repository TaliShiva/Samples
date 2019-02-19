/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _LOADTEMPLATE_HPP
#define _LOADTEMPLATE_HPP

#include <string>
#include <chrono>

/**
 * Struct contains information about load template
 * @version 1.0
 */
struct LoadTemplate {
public:

    std::string read_or_write;
    unsigned long length_of_data;
    std::chrono::milliseconds length_of_pause;
    unsigned long number_of_data_atoms;
    unsigned long number_of_solid_data;

    LoadTemplate() = delete;
    LoadTemplate(std::string read_or_write,
                 unsigned long length_of_data,
                 std::chrono::milliseconds length_of_pause,
                 unsigned long number_of_data_atoms,
                 unsigned long number_of_solid_data);
    LoadTemplate(const LoadTemplate &other) = delete;
    LoadTemplate& operator=(const LoadTemplate &other) = delete;
    LoadTemplate(LoadTemplate &&other) = default;
    LoadTemplate& operator=(LoadTemplate &&other) = default;
    ~LoadTemplate() = default;

};

#endif //_LOADTEMPLATE_HPP
