/**
 * Project Gorynych
 * @version 0.1
 */

#include "../../include/load/LoadProfile.hpp"


LoadProfile::LoadProfile(std::string read_or_write,
                         std::shared_ptr<SolidDataChain> solid_data_chain,
                         std::chrono::milliseconds length_of_pause) : read_or_write(read_or_write),
                                                          solid_data_chain(solid_data_chain),
                                                          length_of_pause(length_of_pause) {}
