#include "DS3231.hpp"

DS3231::DS3231(hwlib::i2c_bus_bit_banged_scl_sda& I2CBus, uint8_t DS3231Address):
	I2CBus(I2CBus), DS3231Address(DS3231Address) {
}

void DS3231::setRegister(uint8_t chipRegAddress) {
	uint8_t chipReg[1] = {chipRegAddress};
	I2CBus.write(DS3231Address, chipReg, 1);
}

uint8_t DS3231::getByteFromRegister(uint8_t chipRegAddress) {
	int amountOfBytes = 1;
	uint8_t chipReg[1] = {chipRegAddress};

	setRegister(chipReg[0]);

	uint8_t data[amountOfBytes] = {};
	I2CBus.read(DS3231Address, data, amountOfBytes);
	return data[0];
}

int DS3231::getCurrentSeconds() {
	return 1;
}
