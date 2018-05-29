#include "DS3231.hpp"

#include "bitParser.hpp"

DS3231::DS3231(i2cBus& I2CBus, uint8_t DS3231Address):
	I2CBus(I2CBus), DS3231Address(DS3231Address), newCentury(0)
{}

void DS3231::setI2CBusCurrentAddress() {
	I2CBus.setCurrentChipAddress(DS3231Address);
}

uint8_t DS3231::getCurrentSeconds() {
	setI2CBusCurrentAddress();
	return I2CBus.getDECFromBCDRegister(REG_SECONDS);
}

void DS3231::setCurrentSeconds(uint8_t newSeconds) {
	if(time::isSecondsValid(newSeconds)) {
		setI2CBusCurrentAddress();
		I2CBus.setByteToBCDInRegister(REG_SECONDS, newSeconds);
	}
}

uint8_t DS3231::getCurrentMinutes() {
	setI2CBusCurrentAddress();
	return I2CBus.getDECFromBCDRegister(REG_MINUTES);
}

void DS3231::setCurrentMinutes(uint8_t newMinutes) {
	if(time::isMinutesValid(newMinutes)) {
		setI2CBusCurrentAddress();
		I2CBus.setByteToBCDInRegister(REG_MINUTES, newMinutes);
	}
}

uint8_t DS3231::getCurrentHours() {
	setI2CBusCurrentAddress();
	return I2CBus.getDECFromBCDRegister(REG_HOURS);
}

void DS3231::setCurrentHours(uint8_t newHours) {
	if(time::isHoursValid(newHours)) {
		setI2CBusCurrentAddress();
		I2CBus.setByteToBCDInRegister(REG_HOURS, newHours);
	}

}
uint8_t DS3231::getCurrentDay() {
	setI2CBusCurrentAddress();
	return I2CBus.getDECFromBCDRegister(REG_DAY);
}

void DS3231::setCurrentDay(uint8_t newDay) {
	if(time::isDayValid(newDay)) {
		setI2CBusCurrentAddress();
		I2CBus.setByteToBCDInRegister(REG_DAY, newDay);
	}
}

uint8_t DS3231::getCurrentDate() {
	setI2CBusCurrentAddress();
	return I2CBus.getDECFromBCDRegister(REG_DATE);
}

void DS3231::setCurrentDate(uint8_t newDate) {
	if(time::isDateValid(newDate)) {
		setI2CBusCurrentAddress();
		I2CBus.setByteToBCDInRegister(REG_DATE, newDate);
	}
}

uint8_t DS3231::getCurrentMonth() {
	setI2CBusCurrentAddress();
	return bitParser::BCDToDEC(I2CBus.getByteFromRegister(REG_MONTH_CENTURY) & 0x1F);
}

void DS3231::setCurrentMonth(uint8_t newMonth) {
	if(time::isMonthValid(newMonth)) {
		setI2CBusCurrentAddress();
		I2CBus.setByteInRegister(REG_MONTH_CENTURY, bitParser::DECToBCD(newMonth) | getCurrentCenturyBit() << 7);
	}
}

bool DS3231::getCurrentCenturyBit() {
	setI2CBusCurrentAddress();
	return I2CBus.getByteFromRegister(REG_MONTH_CENTURY) >> 7;
}

void DS3231::ResetCurentCenturyBit() {
	setI2CBusCurrentAddress();
	uint8_t currentByte = I2CBus.getByteFromRegister(REG_MONTH_CENTURY);
	currentByte &= 0x7F;
	I2CBus.setByteInRegister(REG_MONTH_CENTURY, currentByte);
}

uint8_t DS3231::getCurrentYear() {
	setI2CBusCurrentAddress();
	return I2CBus.getDECFromBCDRegister(REG_YEAR);
}

void DS3231::setCurrentYear(uint8_t newYear) {
	if(time::isYearValid(newYear)) {
		setI2CBusCurrentAddress();
		I2CBus.setByteToBCDInRegister(REG_YEAR, newYear);
	}
}

int DS3231::getCurrentTemperatureCelsius() {
	setI2CBusCurrentAddress();
	uint16_t temperature = (I2CBus.getByteFromRegister(REG_TEMPERATURE_MSB) << 2)
	                       | (I2CBus.getByteFromRegister(REG_TEMPERATURE_LSB) >> 6);
	return temperature * 0.25;
}

int DS3231::getCurrentTemperatureFahrenheit() {
	return getCurrentTemperatureCelsius() * 1.8 + 32;
}

timestamp DS3231::getCurrentTimestamp() {
	setI2CBusCurrentAddress();
	I2CBus.setRegister(REG_SECONDS);
	const int amountOfBytes = 7;
	uint8_t data[amountOfBytes];
	I2CBus.read(DS3231Address, data, amountOfBytes);

	timestamp ts;
	ts.setSeconds(bitParser::BCDToDEC(data[0]));
	ts.setMinutes(bitParser::BCDToDEC(data[1]));
	ts.setHours(bitParser::BCDToDEC(data[2]));
	ts.setDay(bitParser::BCDToDEC(data[3]));
	ts.setDate(bitParser::BCDToDEC(data[4]));
	ts.setMonth(bitParser::BCDToDEC(data[5] & 0x1F));
	ts.setYear(bitParser::BCDToDEC(data[6]));
	ts.setCentury(time::currentCentury);

	return ts;
}

void DS3231::update() {
	if(getCurrentCenturyBit() && !newCentury) {
		newCentury++;
		time::increaseCentury();
		hwlib::cout << "The century bit is active. You should change the currentCentury in the class - time - \n"
		<< "The current century is now: " << time::currentCentury << "\n";
		ResetCurentCenturyBit();
	}
}
