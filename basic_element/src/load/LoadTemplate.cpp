/**
 * Project Gorynych
 * @version 0.1
 */


#include "../../include/load/LoadTemplate.hpp"


LoadTemplate::LoadTemplate(std::string read_or_write,
                           unsigned long length_of_data,
                           std::chrono::milliseconds length_of_pause,
                           unsigned long number_of_data_atoms,
                           unsigned long number_of_solid_data) : read_or_write(read_or_write),
                                                                  length_of_data(length_of_data),
                                                                  length_of_pause(length_of_pause),
                                                                  number_of_data_atoms(number_of_data_atoms),
                                                                  number_of_solid_data(number_of_solid_data) {

}

