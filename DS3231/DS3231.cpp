#include "DS3231.hpp"

DS3231::DS3231(hwlib::i2c_bus_bit_banged_scl_sda& I2CBus, uint8_t DS3231Address):
	I2CBus(I2CBus), DS3231Address(DS3231Address) {
}

void DS3231::setRegister(uint8_t chipRegAddress) {
	uint8_t chipReg[1] = {chipRegAddress};
	I2CBus.write(DS3231Address, chipReg, 1);
}

uint8_t DS3231::getByteFromRegister(uint8_t chipRegAddress) {
	uint8_t amountOfBytes = 1;
	uint8_t chipReg[1] = {chipRegAddress};

	setRegister(chipReg[0]);

	uint8_t data[amountOfBytes] = {};
	I2CBus.read(DS3231Address, data, amountOfBytes);
	return data[0];
}

uint8_t DS3231::getDECFromBCDRegister(uint8_t chipRegAddress) {
	return bitParser::DECToBCD(getByteFromRegister(chipRegAddress));
}

uint8_t DS3231::getCurrentSeconds() const {
	return getDECFromBCDRegister(REG_SECONDS);
}

uint8_t DS3231::getCurrentMinutes() const {
	return getDECFromBCDRegister(REG_MINUTES);
}

uint8_t DS3231::getCurrentHours() const {
	return getDECFromBCDRegister(REG_HOURS);
}

uint8_t DS3231::getCurrentDay() const {
	return getDECFromBCDRegister(REG_DAY);
}

uint8_t DS3231::getCurrentDate() const {
	return getDECFromBCDRegister(REG_DATE);
}

uint8_t DS3231::getCurrentMonthCentury() const {
	return getDECFromBCDRegister(REG_MONTH_CENTURY);
}

uint8_t DS3231::getCurrentYear() const {
	return getDECFromBCDRegister(REG_YEAR);
}
