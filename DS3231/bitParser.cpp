#include "bitParser.hpp"

namespace bitParser {

void printBytes(uint_least8_t bytes) {
	unsigned int amountOfBits = sizeof(bytes) * 8;
	for(unsigned int i = 0; i < amountOfBits; ++i) {
		hwlib::cout << ((bytes >> i) & 1) << ' ';
	}
	hwlib::cout << "\n";
}

int BCDBytesToInt(uint_least8_t bytes) {
	amountOfBytes = sizeof(bytes);
	amountOfBCDFields = amountOfBytes * 2;

	for()
	}

uint8_t intToBCDBytes(unsigned int digit);

}
