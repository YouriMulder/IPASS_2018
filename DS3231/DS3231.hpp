#ifndef DS3231_HPP
#define DS3231_HPP

#include "hwlib.hpp"
#include "i2cBus.hpp"
#include "time.hpp"

class DS3231 : public time {
private:
	i2cBus& I2CBus;
	uint8_t DS3231Address;

	int newCentury;

	static const uint8_t REG_SECONDS = 			0x00;
	static const uint8_t REG_MINUTES = 			0x01;
	static const uint8_t REG_HOURS = 			0x02;
	static const uint8_t REG_DAY = 				0x03;
	static const uint8_t REG_DATE = 			0x04;
	static const uint8_t REG_MONTH_CENTURY = 	0x05;
	static const uint8_t REG_YEAR = 			0x06;

	static const uint8_t REG_ALARM_1_SEC = 		0x07;
	static const uint8_t REG_ALARM_1_MIN = 		0x08;
	static const uint8_t REG_ALARM_1_HOURS = 	0x09;
	static const uint8_t REG_ALARM_1_DAY_DATE =	0x0A;

	static const uint8_t REG_ALARM_2_MIN = 		0x0B;
	static const uint8_t REG_ALARM_2_HOURS = 	0x0C;
	static const uint8_t REG_ALARM_2_DAY_DATE =	0x0D;

	static const uint8_t REG_CONTROL = 			0x0E;
	static const uint8_t REG_STATUS = 			0x0F;
	static const uint8_t REG_AGING_OFFSET = 	0x10;

	static const uint8_t REG_TEMPERATURE_MSB = 	0x11;
	static const uint8_t REG_TEMPERATURE_LSB =	0x12;

public:
	DS3231(i2cBus& I2CBus, uint8_t address);

private:
	void setI2CBusCurrentAddress();

public:
	uint8_t getCurrentSeconds();
	void setCurrentSeconds(uint8_t newSeconds);

	uint8_t getCurrentMinutes();
	void setCurrentMinutes(uint8_t newMinutes);

	uint8_t getCurrentHours();
	void setCurrentHours(uint8_t newHours);

	uint8_t getCurrentDay();
	void setCurrentDay(uint8_t newDay);

	uint8_t getCurrentDate();
	void setCurrentDate(uint8_t newDate);

	uint8_t getCurrentMonth();
	void setCurrentMonth(uint8_t newMonth);

	bool getCurrentCentury();
	void ResetCurentCenturyBit()

	uint8_t getCurrentYear();
	void setCurrentYear(uint8_t newYear);

	int getCurrentTemperatureCelsius();
	int getCurrentTemperatureFahrenheit();
	uint8_t getCurrentTimestamp();

public:
	void update();

};

#endif // DS3231_HPP
