#include "i2cBus.hpp"
#include "bitparser.hpp"

i2cBus::i2cBus(hwlib::target::pin_oc& scl, hwlib::target::pin_oc& sda):
	hwlib::i2c_bus_bit_banged_scl_sda(scl, sda)
{}

void i2cBus::setCurrentChipAddress(uint8_t newChipAddress) {
	currentChipAddress = newChipAddress;
}

uint8_t i2cBus::getCurrentChipAddress() {
	return currentChipAddress;
}

void i2cBus::setRegister(uint8_t chipRegAddress) {
	const uint8_t amountOfBytes = 1;
	uint8_t chipReg[amountOfBytes] = {chipRegAddress};
	write(currentChipAddress, chipReg, amountOfBytes);
}

uint8_t i2cBus::getByteFromRegister(uint8_t chipRegAddress) {
	const uint8_t amountOfBytes = 1;
	setRegister(chipRegAddress);
	uint8_t data[amountOfBytes] = {};
	read(currentChipAddress, data, amountOfBytes);
	return data[0];
}

void i2cBus::setByteInRegister(uint8_t chipRegAddress, uint8_t byte) {
	const uint8_t amountOfBytes = 1;
	uint8_t data[amountOfBytes + 1] = { chipRegAddress, bitParser::DECToBCD(byte) };
	setRegister(chipRegAddress);
	write(currentChipAddress, data, amountOfBytes + 1);
}

uint8_t i2cBus::getDECFromBCDRegister(uint8_t chipRegAddress) {
	return bitParser::BCDToDEC(getByteFromRegister(chipRegAddress));
}
