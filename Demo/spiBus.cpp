#include "spiBus.hpp"
#include "bitParser.hpp"


spiBus::spiBus(hwlib::pin_out& scl, hwlib::pin_out& mosi, hwlib::pin_in& miso):
	hwlib::spi_bus_bit_banged_sclk_mosi_miso(scl, mosi, miso)
{}

uint8_t spiBus::getReadByte(const uint8_t chipRegAddress) {
	return ((chipRegAddress << 1) & REGISTER_MASK) | READ_MASK;
}

uint8_t spiBus::getWriteByte(const uint8_t chipRegAddress) {
	return (chipRegAddress << 1) & REGISTER_MASK;
}

uint8_t spiBus::getByteFromRegister(const uint8_t chipRegAddress,
                                    hwlib::pin_out& slaveSelect) {
	const uint8_t amountOfBytes = 2;
	uint8_t write[amountOfBytes] = {getReadByte(chipRegAddress), 0};
	uint8_t read[amountOfBytes] = {0, 0};
	write_and_read(slaveSelect, amountOfBytes, write, read);
	return read[1];
}

void spiBus::getBytesFromRegister(const uint8_t chipRegAddress, uint8_t data[],
                                  const uint8_t amountOfBytes, hwlib::pin_out& slaveSelect) {
	const uint16_t arraySize = amountOfBytes + 1;
	uint8_t write[arraySize] = {0};
	uint8_t readByte = getReadByte(chipRegAddress);
	for(auto & element : write) {
		element = readByte;
	}

	uint8_t read[arraySize] = {0};

	write_and_read(slaveSelect, arraySize, write, read);
	for(uint8_t i = 0; i < amountOfBytes; i++) {
		data[i] = read[i + 1];
	}
}

void spiBus::setByteInRegister(const uint8_t chipRegAddress, uint8_t newByte,
                               hwlib::pin_out& slaveSelect) {
	uint8_t write[2] = {getWriteByte(chipRegAddress), newByte};
	write_and_read(slaveSelect, 2, write, nullptr);
}

void spiBus::setBytesInRegister(const uint8_t chipRegAddress, uint8_t newBytes[],
                                const uint8_t amountOfBytes, hwlib::pin_out& slaveSelect) {
	const uint16_t arraySize = amountOfBytes + 1;
	uint8_t write[arraySize] = {0};
	write[0] = getWriteByte(chipRegAddress);
	for(uint8_t i = 0; i < amountOfBytes; i++) {
		if(i + 1 < arraySize) {
			write[i + 1] = newBytes[i];
		}
	}

	write_and_read(slaveSelect, arraySize, write, nullptr);
}
