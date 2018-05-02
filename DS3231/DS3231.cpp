#include "DS3231.hpp"

#include "bitParser.hpp"

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
	return bitParser::BCDToDEC(getByteFromRegister(chipRegAddress));
}

uint8_t DS3231::getCurrentSeconds() {
	return getDECFromBCDRegister(REG_SECONDS);
}

uint8_t DS3231::getCurrentMinutes() {
	return getDECFromBCDRegister(REG_MINUTES);
}

uint8_t DS3231::getCurrentHours() {
	return getDECFromBCDRegister(REG_HOURS);
}

uint8_t DS3231::getCurrentDay() {
	return getDECFromBCDRegister(REG_DAY);
}

uint8_t DS3231::getCurrentDate() {
	return getDECFromBCDRegister(REG_DATE);
}

uint8_t DS3231::getCurrentMonth() {
	return bitParser::BCDToDEC(getByteFromRegister(REG_MONTH_CENTURY) & 0x1F);
}

uint8_t DS3231::getCurrentCentury() {
	return (getByteFromRegister(REG_MONTH_CENTURY) & 0x80) >> 7;
}

uint8_t DS3231::getCurrentYear() {
	return getDECFromBCDRegister(REG_YEAR);
}

int DS3231::getCurrentTemperatureCelsius() {
	uint16_t temperature = (getByteFromRegister(REG_TEMPERATURE_MSB) << 2)
	                       | (getByteFromRegister(REG_TEMPERATURE_LSB) >> 6);
	return temperature * 0.25;
}
