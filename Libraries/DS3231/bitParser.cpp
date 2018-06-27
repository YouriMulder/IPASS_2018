// -----------------------------------------------------------
// (C) Copyright Youri Mulder 2018.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// -----------------------------------------------------------

#include "bitParser.hpp"

namespace bitParser {

void printByte(uint8_t byte) {
	for(unsigned int i = 0; i < nBitsinByte; ++i) {
		hwlib::cout << ((byte >> i) & 1) << ' ';
	}
	hwlib::cout << "\n";
}

void printBytes(uint16_t bytes) {
	for(unsigned int i = 0; i < nBitsinByte * 2; ++i) {
		hwlib::cout << ((bytes >> i) & 1) << ' ';
	}
	hwlib::cout << "\n";
}

uint8_t BCDToDEC(uint8_t BCD) {
	return (BCD / 16 * 10) + (BCD % 16);
}

uint8_t DECToBCD(uint8_t DEC) {
	return (DEC / 10 * 16) + (DEC % 10);
}

int uint8_tToInt(uint8_t byte) {
	return (unsigned int)byte;
}

}
