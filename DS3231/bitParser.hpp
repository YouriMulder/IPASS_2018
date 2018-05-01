#ifndef bitParser_HPP
#define bitParser_HPP

#include "hwlib.hpp"

namespace bitParser {

// LSB to MSB
void printBytes(uint_least8_t bytes);
int BCDByteToInt(uint_fast8_t byte);
uint8_t intToBCDByte(int digit);


}

#endif // bitParser_HPP
