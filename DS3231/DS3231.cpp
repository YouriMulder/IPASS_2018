#include "DS3231.hpp"

#include "bitParser.hpp"

DS3231::DS3231(i2cBus& I2CBus, uint8_t DS3231Address):
	I2CBus(I2CBus), DS3231Address(DS3231Address) {
}

void DS3231::setI2CBusCurrentAddress() {
	I2CBus.setCurrentChipAddress(DS3231Address);
}

uint8_t DS3231::getCurrentSeconds() {
	setI2CBusCurrentAddress();
	return I2CBus.getDECFromBCDRegister(REG_SECONDS);
}

void DS3231::setCurrentSeconds(uint8_t newSeconds) {
	setI2CBusCurrentAddress();
	I2CBus.setByteInRegister(REG_SECONDS, bitParser::DECToBCD(newSeconds));
}

uint8_t DS3231::getCurrentMinutes() {
	setI2CBusCurrentAddress();
	return I2CBus.getDECFromBCDRegister(REG_MINUTES);
}

void DS3231::setCurrentMinutes(uint8_t newMinutes) {
	setI2CBusCurrentAddress();
	I2CBus.setByteInRegister(REG_MINUTES, bitParser::DECToBCD(newMinutes));
}

uint8_t DS3231::getCurrentHours() {
	setI2CBusCurrentAddress();
	return I2CBus.getDECFromBCDRegister(REG_HOURS);
}

void DS3231::setCurrentHours(uint8_t newHours) {
	setI2CBusCurrentAddress();
	I2CBus.setByteInRegister(REG_HOURS, bitParser::DECToBCD(newHours));
}

uint8_t DS3231::getCurrentDay() {
	setI2CBusCurrentAddress();
	return I2CBus.getDECFromBCDRegister(REG_DAY);
}

void DS3231::setCurrentDay(uint8_t newDay) {
	setI2CBusCurrentAddress();
	I2CBus.setByteInRegister(REG_DAY, bitParser::DECToBCD(newDay));
}

uint8_t DS3231::getCurrentDate() {
	setI2CBusCurrentAddress();
	return I2CBus.getDECFromBCDRegister(REG_DATE);
}

void DS3231::setCurrentDate(uint8_t newDate) {
	setI2CBusCurrentAddress();
	I2CBus.setByteInRegister(REG_DATE, bitParser::DECToBCD(newDate));
}

uint8_t DS3231::getCurrentMonth() {
	setI2CBusCurrentAddress();
	return bitParser::BCDToDEC(I2CBus.getByteFromRegister(REG_MONTH_CENTURY) & 0x1F);
}

uint8_t DS3231::getCurrentCentury() {
	setI2CBusCurrentAddress();
	return (I2CBus.getByteFromRegister(REG_MONTH_CENTURY) & 0x80) >> 7;
}

uint8_t DS3231::getCurrentYear() {
	setI2CBusCurrentAddress();
	return I2CBus.getDECFromBCDRegister(REG_YEAR);
}

void DS3231::setCurrentYear(uint8_t newYear) {
	setI2CBusCurrentAddress();
	I2CBus.setByteInRegister(REG_YEAR, bitParser::DECToBCD(newYear));
}

int DS3231::getCurrentTemperatureCelsius() {
	setI2CBusCurrentAddress();
	uint16_t temperature = (I2CBus.getByteFromRegister(REG_TEMPERATURE_MSB) << 2)
	                       | (I2CBus.getByteFromRegister(REG_TEMPERATURE_LSB) >> 6);
	return temperature * 0.25;
}
