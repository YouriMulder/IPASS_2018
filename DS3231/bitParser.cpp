#include "bitParser.hpp"

namespace bitParser {

static const int nBitsinByte = 8;
static const int nBitsinHalfAByte = 4;
static const uint8_t leftHalfByteMask = 0x78;
static const uint8_t rightHalfgByteMask = 0xF;

void printByte(uint8_t byte) {
	for(unsigned int i = 0; i < nBitsinByte; ++i) {
		hwlib::cout << ((byte >> i) & 1) << ' ';
	}
	hwlib::cout << "\n";
}

uint8_t BCDToDEC(uint8_t BCD) {
	return (BCD >> nBitsinHalfAByte) * 10 + (BCD & rightHalfgByteMask);
}

uint8_t DECToBCD(uint8_t DEC) {
	return ((DEC / 10) << nBitsinHalfAByte) | (DEC % 10);
}

int uint8_tToInt(uint8_t byte) {
	return (unsigned int)byte;
}
}
