/**
 * Project Gorynych
 * @version 0.1
 */


#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

#include "../../include/load/LoadParameters.hpp"

using ptree_bad_path =
boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::property_tree::ptree_bad_path>>;
using ptree_bad_data =
boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::property_tree::ptree_bad_data>>;

LoadParameters::LoadParameters(boost::property_tree::ptree json_tree) {
    try {
        for (auto &load: json_tree.get_child("loads")) {
            unsigned long count = load.second.get<unsigned long>("templates_repeat_counter");
            std::vector<LoadTemplate> load_templates;
            for (auto &temp: load.second.get_child("templates")) {
                auto read_or_write = temp.second.get<std::string>("rw");
                auto length_of_data = temp.second.get<unsigned long>("length_of_data_atom");
                auto pause = temp.second.get<unsigned long>("pause_in_milliseconds_after_solid_data_chain");
                std::chrono::milliseconds length_of_pause{pause};
                auto number_of_data_atoms = temp.second.get<unsigned long>("number_of_data_atoms_in_solid_data");
                auto number_of_solid_data = temp.second.get<unsigned long>("number_of_solid_data_in_chain");
                load_templates.emplace_back(LoadTemplate(read_or_write,
                                                         length_of_data,
                                                         length_of_pause,
                                                         number_of_data_atoms,
                                                         number_of_solid_data));
            }
            vector_of_load_templates.emplace_back(count, std::move(load_templates));
        }
    } catch (const ptree_bad_path & ptree_bad_path_error) {
        std::cerr << "File contains incomplete data" << std::endl;
    } catch (const ptree_bad_data & ptree_bad_data_error) {
        std::cerr << "File contains incorrect data" << std::endl;
    }

}
