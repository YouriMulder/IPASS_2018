#ifndef bitParser_HPP
#define bitParser_HPP

#include "hwlib.hpp"

namespace bitParser {

const int nBitsinByte = 8;
const int nBitsinHalfAByte = 4;
const uint8_t leftHalfByteMask = 0x78;
const uint8_t rightHalfgByteMask = 0xF;

// LSB to MSB
void printByte(uint8_t byte) ;
void printBytes(uint16_t bytes);
uint8_t BCDToDEC(uint8_t BCD);
uint8_t DECToBCD(uint8_t DEC);
int uint8_tToInt(uint8_t byte);

}

#endif // bitParser_HPP
