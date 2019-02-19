/**
 * Project Gorynych
 * @version 0.1
 */


#include <vector>

#include "../../include/data_entity/RawDataWrite.hpp"


RawDataWrite::RawDataWrite(unsigned recommended_size) {
    data.reserve(recommended_size);
}

RawDataWrite::RawDataWrite(const payload_data_vector &data) : data(data){
}
