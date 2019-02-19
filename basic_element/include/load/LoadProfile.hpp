/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _LOADPROFILE_HPP
#define _LOADPROFILE_HPP


#include <chrono>

#include "../data_entity/system/SolidDataChain.hpp"

/**
 * Struct contains information about solid chain and its load profile
 * @version 1.0
 */

struct LoadProfile {

public:
    std::string read_or_write;
    std::shared_ptr<SolidDataChain> solid_data_chain;
    std::chrono::milliseconds length_of_pause;

    LoadProfile() = delete;
    LoadProfile(std::string read_or_write,
                std::shared_ptr<SolidDataChain> solid_data_chain,
                std::chrono::milliseconds length_of_pause);
    LoadProfile(const LoadProfile &other) = delete;
    LoadProfile& operator=(const LoadProfile &other) = delete;
    LoadProfile(LoadProfile &&other) = default;
    LoadProfile& operator=(LoadProfile &&other) = default;
    ~LoadProfile() = default;
};

#endif //_LOADPROFILE_HPP
