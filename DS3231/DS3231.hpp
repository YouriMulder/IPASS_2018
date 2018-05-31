#ifndef DS3231_HPP
#define DS3231_HPP

#include "hwlib.hpp"
#include "i2cBus.hpp"
#include "time.hpp"
#include "timestamp.hpp"

class DS3231 : public time {
private:
	i2cBus& I2CBus;
	uint8_t DS3231Address;

	int newCentury;

	static const uint8_t defaultDS3231Address = 0x68;

	const uint8_t REG_SECONDS = 0x00;
	const uint8_t REG_MINUTES = 0x01;
	const uint8_t REG_HOURS = 0x02;
	const uint8_t REG_DAY = 0x03;
	const uint8_t REG_DATE = 0x04;
	const uint8_t REG_MONTH_CENTURY = 0x05;
	const uint8_t REG_YEAR = 0x06;

	const uint8_t REG_ALARM_1_SEC = 0x07;
	const uint8_t REG_ALARM_1_MIN = 0x08;
	const uint8_t REG_ALARM_1_HOURS = 0x09;
	const uint8_t REG_ALARM_1_DAY_DATE = 0x0A;

	const uint8_t REG_ALARM_2_MIN = 0x0B;
	const uint8_t REG_ALARM_2_HOURS = 0x0C;
	const uint8_t REG_ALARM_2_DAY_DATE = 0x0D;

	const uint8_t REG_CONTROL = 0x0E;
	const uint8_t REG_STATUS = 0x0F;
	const uint8_t REG_AGING_OFFSET = 0x10;

	const uint8_t REG_TEMPERATURE_MSB = 0x11;
	const uint8_t REG_TEMPERATURE_LSB = 0x12;

	const uint8_t ALARM_AxMx_BIT = 7;

public:
	DS3231(i2cBus& I2CBus, uint8_t address = defaultDS3231Address);

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

	bool getCurrentCenturyBit();
	void ResetCurentCenturyBit();

	uint8_t getCurrentYear();
	void setCurrentYear(uint8_t newYear);

	int getCurrentTemperatureCelsius();
	int getCurrentTemperatureFahrenheit();

	void getCurrentTimeData(uint8_t data[7]);
	timestamp getCurrentTimestamp();
	void getCurrentTimestamp(timestamp& ts);

public:
	uint8_t getAlarmBCDRegisterExMSB(uint8_t alarmRegister);
	void setAlarmBCDRegisterExMSB(uint8_t alarmRegister, uint8_t newByte);
	// Alarm 1 only
	uint8_t getAlarmOneSeconds();
	void setAlarmOneSeconds(uint8_t newSeconds);

	// Alarm 1 = 0 | Alarm 2 = 1
	uint8_t getAlarmMinutes(bool alarm);
	void setAlarmMinutes(bool alarm, uint8_t newMinutes);

	uint8_t getAlarmHours(bool alarm);
	void setAlarmHours(bool alarm, uint8_t newHours);

	uint8_t getAlarmDayDate(bool alarm);
	void setAlarmDayDate(bool alarm, uint8_t newDayDate);

public:
	void update();
};

#endif // DS3231_HPP
