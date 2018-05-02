#ifndef bitParser_HPP
#define bitParser_HPP

#include "hwlib.hpp"

namespace bitParser {

// LSB to MSB
void printByte(uint8_t byte) ;
uint8_t BCDToDEC(uint8_t BCD);
uint8_t DECToBCD(uint8_t DEC);
int uint8_tToInt(uint8_t byte);

}

#endif // bitParser_HPP
