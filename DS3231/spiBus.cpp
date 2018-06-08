#include "spiBus.hpp"
#include "bitParser.hpp"


spiBus::spiBus(hwlib::pin_out& scl, hwlib::pin_out& mosi, hwlib::pin_in& miso):
hwlib::spi_bus_bit_banged_sclk_mosi_miso(scl, mosi, miso)
{}

uint8_t spiBus::getReadByte(uint8_t chipRegAddress) {
	return ((chipRegAddress << 1) & REGISTER_MASK) | READ_MASK;
}

uint8_t spiBus::getWriteByte(uint8_t chipRegAddress) {
	return (chipRegAddress << 1) & REGISTER_MASK;
}

uint8_t spiBus::getByteFromRegister(uint8_t chipRegAddress,
									hwlib::pin_out& slaveSelect) {
	const uint8_t amountOfBytes = 2;
	uint8_t write[amountOfBytes] = {getReadByte(chipRegAddress), 0};
	uint8_t read[amountOfBytes] = {0, 0};
	write_and_read(slaveSelect, amountOfBytes, write, read);
	return read[1];
}

void spiBus::setByteInRegister(uint8_t chipRegAddress, uint8_t newByte,
								hwlib::pin_out& slaveSelect) {
	uint8_t write[2] = {getWriteByte(chipRegAddress), newByte};
	hwlib::cout << (unsigned)newByte << "\n";
	write_and_read(slaveSelect, 2, write, nullptr);
}
