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
		I2CBus.setByteInRegister(REG_MONTH_CENTURY, bitParser::DECToBCD(newMonth)
		                         | getCurrentCenturyBit() << 7);
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

int16_t DS3231::getCurrentTemperatureCelsius() {
	setI2CBusCurrentAddress();
	int16_t temp = I2CBus.getByteFromRegister(REG_TEMPERATURE_MSB) << 8 |
	               I2CBus.getByteFromRegister(REG_TEMPERATURE_LSB);
	return temp/256;
}

int16_t DS3231::getCurrentTemperatureFahrenheit() {
	return getCurrentTemperatureCelsius() * 1.8 + 32;
}

void DS3231::getCurrentTimeData(uint8_t data[7]) {
	setI2CBusCurrentAddress();
	I2CBus.setRegister(REG_SECONDS);
	const int amountOfBytes = 7;
	I2CBus.read(DS3231Address, data, amountOfBytes);
}

timestamp DS3231::getCurrentTimestamp() {
	const int amountOfBytes = 7;
	uint8_t data[amountOfBytes];
	getCurrentTimeData(data);

	timestamp ts(
	    bitParser::BCDToDEC(data[0]),
	    bitParser::BCDToDEC(data[1]),
	    bitParser::BCDToDEC(data[2]),
	    bitParser::BCDToDEC(data[3]),
	    bitParser::BCDToDEC(data[4]),
	    bitParser::BCDToDEC(data[5] & 0x1F),
	    bitParser::BCDToDEC(data[6])
	);
	ts.setCentury(time::currentCentury);
	return ts;
}

void DS3231::getCurrentTimestamp(timestamp& ts) {
	const int amountOfBytes = 7;
	uint8_t data[amountOfBytes];
	getCurrentTimeData(data);

	ts.setSeconds(bitParser::BCDToDEC(data[0]));
	ts.setMinutes(bitParser::BCDToDEC(data[1]));
	ts.setHours(bitParser::BCDToDEC(data[2]));
	ts.setDay(bitParser::BCDToDEC(data[3]));
	ts.setDate(bitParser::BCDToDEC(data[4]));
	ts.setMonth(bitParser::BCDToDEC(data[5] & 0x1F));
	ts.setYear(bitParser::BCDToDEC(data[6]));
	ts.setCentury(time::currentCentury);
}

// Alarm
uint8_t DS3231::getAlarmBCDRegisterExMSB(uint8_t alarmRegister) {
	setI2CBusCurrentAddress();
	uint8_t byte = I2CBus.getByteFromRegister(alarmRegister);
	return bitParser::BCDToDEC(byte & ~(0x01 << BIT_ALARM_AxMx));
}

void DS3231::setAlarmBCDRegisterExMSB(uint8_t alarmRegister, uint8_t newByte) {
	setI2CBusCurrentAddress();
	bool MSB = (I2CBus.getByteFromRegister(alarmRegister) >> BIT_ALARM_AxMx) & 1;
	I2CBus.setByteInRegister(alarmRegister,
	                         bitParser::DECToBCD(newByte) | MSB << BIT_ALARM_AxMx);
}

uint8_t DS3231::getAlarmOneSeconds() {
	return getAlarmBCDRegisterExMSB(REG_ALARM_1_SEC);
}

void DS3231::setAlarmOneSeconds(uint8_t newSeconds) {
	if(time::isSecondsValid(newSeconds)) {
		setAlarmBCDRegisterExMSB(REG_ALARM_1_SEC, newSeconds);
	}
}

uint8_t DS3231::getAlarmMinutes(bool alarm) {
	uint8_t alarmRegister = !alarm ? REG_ALARM_1_MIN : REG_ALARM_2_MIN;
	return getAlarmBCDRegisterExMSB(alarmRegister);
}

void DS3231::setAlarmMinutes(bool alarm, uint8_t newMinutes) {
	if(time::isMinutesValid(newMinutes)) {
		uint8_t alarmRegister = !alarm ? REG_ALARM_1_MIN : REG_ALARM_2_MIN;
		setAlarmBCDRegisterExMSB(alarmRegister, newMinutes);
	}
}

uint8_t DS3231::getAlarmHours(bool alarm) {
	uint8_t alarmRegister = !alarm ? REG_ALARM_1_HOURS : REG_ALARM_2_HOURS;
	return getAlarmBCDRegisterExMSB(alarmRegister);
}

void DS3231::setAlarmHours(bool alarm, uint8_t newHours) {
	if(time::isHoursValid(newHours)) {
		uint8_t alarmRegister = !alarm ? REG_ALARM_1_HOURS : REG_ALARM_2_HOURS;
		setAlarmBCDRegisterExMSB(alarmRegister, newHours);
	}
}

uint8_t DS3231::getAlarmDayDate(bool alarm) {
	uint8_t alarmRegister = !alarm ? REG_ALARM_1_DAY_DATE : REG_ALARM_2_DAY_DATE;
	return getAlarmBCDRegisterExMSB(alarmRegister);
}

void DS3231::setAlarmDayDate(bool alarm, uint8_t newDayDate) {
	if(time::isDateValid(newDayDate)) {
		uint8_t alarmRegister = !alarm ? REG_ALARM_1_DAY_DATE : REG_ALARM_2_DAY_DATE;
		setAlarmBCDRegisterExMSB(alarmRegister, newDayDate);
	}
}

uint8_t DS3231::getControlRegister() {
	setI2CBusCurrentAddress();
	return I2CBus.getByteFromRegister(REG_CONTROL);
}

void DS3231::setControlRegister(uint8_t newByte) {
	setI2CBusCurrentAddress();
	I2CBus.setByteInRegister(REG_CONTROL, newByte);
}

bool DS3231::getControlRegisterBit(uint8_t bitNumber) {
	setI2CBusCurrentAddress();
	return I2CBus.getBitFromRegister(REG_CONTROL, bitNumber);
}

void DS3231::setControlRegisterBit(uint8_t bitNumber, bool newBit) {
	setI2CBusCurrentAddress();
	if(newBit) {
		I2CBus.setBitInRegister(REG_CONTROL, bitNumber);
	} else {
		I2CBus.clearBitInRegister(REG_CONTROL, bitNumber);
	}
}

uint8_t DS3231::getStatusRegister() {
	setI2CBusCurrentAddress();
	return I2CBus.getByteFromRegister(REG_STATUS);
}

void DS3231::setStatusRegister(uint8_t newByte) {
	setI2CBusCurrentAddress();
	I2CBus.setByteInRegister(REG_STATUS, newByte);
}

int8_t DS3231::getAgingOffset() {
	setI2CBusCurrentAddress();
	return I2CBus.getByteFromRegister(REG_AGING_OFFSET);
}

void DS3231::setAgingOffset(int8_t newAgingOffset) {
	setI2CBusCurrentAddress();
	I2CBus.setByteInRegister(REG_AGING_OFFSET, newAgingOffset);
}

void DS3231::update() {
	if(getCurrentCenturyBit() && !newCentury) {
		newCentury++;
		time::increaseCentury();
		hwlib::cout << "The century bit is active."
		            << "You should change the currentCentury in the class - time - \n"
		            << "The current century is now: " << time::currentCentury << "\n";
		ResetCurentCenturyBit();
	}
}
