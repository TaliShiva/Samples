/**
 * Project Gorynych
 * @version 0.1
 */


#ifndef _LOADPARAMETERS_HPP
#define _LOADPARAMETERS_HPP

#include <vector>
#include <boost/property_tree/ptree.hpp>

#include "LoadTemplate.hpp"


/**
 * Struct contains information about load templates and counter of it's repetition
 * @version 1.0
 */
struct LoadParameters {

public:

    std::vector<std::pair<unsigned long, std::vector<LoadTemplate>>> vector_of_load_templates;

    LoadParameters() = delete;
    explicit LoadParameters(boost::property_tree::ptree json_tree);
    LoadParameters(const LoadParameters &other) = delete;
    LoadParameters& operator=(const LoadParameters &other) = delete;
    LoadParameters(LoadParameters &&other) = default;
    LoadParameters& operator=(LoadParameters &&other) = default;
    ~LoadParameters() = default;
};

#endif //_LOADPARAMETERS_HPP
