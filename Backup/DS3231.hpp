#ifndef DS3231_HPP
#define DS3231_HPP

#include "hwlib-ostream.hpp"
#include "i2cBus.hpp"
#include "time.hpp"
#include "timestamp.hpp"
#include "realTimeClock.hpp"

class DS3231 : public realTimeClock {
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

	const uint8_t BIT_ALARM_AxMx = 7;

public:
	const uint8_t BIT_CONTROL_ALARM_1_INTERRUPT_ENABLE = 0;
	const uint8_t BIT_CONTROL_ALARM_2_INTERRUPT_ENABLE = 1;
	const uint8_t BIT_CONTROL_INTERRUPT_CONTROL = 2;
	const uint8_t BIT_CONTOL_RATE_SELECT_1 = 3;
	const uint8_t BIT_CONTROL_RATE_SELECT_2 = 4;
	const uint8_t BIT_CONTROL_TEMPERATURE_CONVERT = 5;
	const uint8_t BIT_CONTROL_BATTERY_BACKED_SQW = 6;
	const uint8_t BIT_CONTROL_OSCILLATOR = 7;

public:
	DS3231(i2cBus& I2CBus, uint8_t address = defaultDS3231Address);

private:
	void setI2CBusCurrentAddress();

public:
	uint8_t getCurrentSeconds() override;
	void setCurrentSeconds(uint8_t newSeconds) override;

	uint8_t getCurrentMinutes() override;
	void setCurrentMinutes(uint8_t newMinutes) override;

	uint8_t getCurrentHours() override;
	void setCurrentHours(uint8_t newHours) override;

	uint8_t getCurrentDay() override;
	void setCurrentDay(uint8_t newDay) override;

	uint8_t getCurrentDate() override;
	void setCurrentDate(uint8_t newDate) override;

	uint8_t getCurrentMonth() override;
	void setCurrentMonth(uint8_t newMonth) override;

	bool getCurrentCenturyBit() override;
	void ResetCurentCenturyBit() override;

	uint8_t getCurrentYear() override;
	void setCurrentYear(uint8_t newYear) override;

	int16_t getCurrentTemperatureCelsius() override;
	int16_t getCurrentTemperatureFahrenheit() override;

	void getCurrentTimeData(uint8_t data[7]) override;
	timestamp getCurrentTimestamp() override;
	void getCurrentTimestamp(timestamp& ts) override;

private:
	uint8_t getAlarmBCDRegisterExMSB(uint8_t alarmRegister);
	void setAlarmBCDRegisterExMSB(uint8_t alarmRegister, uint8_t newByte);

public:
	// Alarm 1 only
	uint8_t getAlarmOneSeconds() override;
	void setAlarmOneSeconds(uint8_t newSeconds) override;

	// Alarm 1 = 0 | Alarm 2 = 1
	uint8_t getAlarmMinutes(bool alarm) override;
	void setAlarmMinutes(bool alarm, uint8_t newMinutes) override;

	uint8_t getAlarmHours(bool alarm) override;
	void setAlarmHours(bool alarm, uint8_t newHours) override;

	uint8_t getAlarmDayDate(bool alarm) override;
	void setAlarmDayDate(bool alarm, uint8_t newDayDate) override;

public:
	// CB = Control Bit
	uint8_t getControlRegister() override;
	void setControlRegister(uint8_t newByte) override;

	bool getControlRegisterBit(uint8_t bitNumber) override;
	void setControlRegisterBit(uint8_t bitNumber, bool newBit) override;

public:
	uint8_t getStatusRegister() override;
	void setStatusRegister(uint8_t newByte) override;

public:
	int8_t getAgingOffset() override;
	void setAgingOffset(int8_t newAgingOffset) override;

public:
	void update() override;
};

#endif // DS3231_HPP
