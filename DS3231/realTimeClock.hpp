#ifndef REALTIMECLOCK_HPP
#define REALTIMECLOCK_HPP

#include "timestamp.hpp"

class realTimeClock : public time {
public:
	virtual uint8_t getCurrentSeconds() = 0;
	virtual void setCurrentSeconds(uint8_t newSeconds) = 0;

	virtual uint8_t getCurrentMinutes() = 0;
	virtual void setCurrentMinutes(uint8_t newMinutes) = 0;

	virtual uint8_t getCurrentHours() = 0;
	virtual void setCurrentHours(uint8_t newHours) = 0;

	virtual uint8_t getCurrentDay() = 0;
	virtual void setCurrentDay(uint8_t newDay) = 0;

	virtual uint8_t getCurrentDate() = 0;
	virtual void setCurrentDate(uint8_t newDate) = 0;

	virtual uint8_t getCurrentMonth() = 0;
	virtual void setCurrentMonth(uint8_t newMonth) = 0;

	virtual bool getCurrentCenturyBit() = 0;
	virtual void ResetCurentCenturyBit() = 0;

	virtual uint8_t getCurrentYear() = 0;
	virtual void setCurrentYear(uint8_t newYear) = 0;


	virtual void getCurrentTimeData(uint8_t data[7]) = 0;
	virtual timestamp getCurrentTimestamp() = 0;
	virtual void getCurrentTimestamp(timestamp& ts) = 0;

	virtual uint8_t getAlarmOneSeconds() = 0;
	virtual void setAlarmOneSeconds(uint8_t newSeconds) = 0;

	// Alarm 1 = 0 | Alarm 2 = 1
	virtual uint8_t getAlarmMinutes(bool alarm) = 0;
	virtual void setAlarmMinutes(bool alarm, uint8_t newMinutes) = 0;

	virtual uint8_t getAlarmHours(bool alarm) = 0;
	virtual void setAlarmHours(bool alarm, uint8_t newHours) = 0;

	virtual uint8_t getAlarmDayDate(bool alarm) = 0;
	virtual void setAlarmDayDate(bool alarm, uint8_t newDayDate) = 0;

public:
	virtual int16_t getCurrentTemperatureCelsius() = 0;
	virtual int16_t getCurrentTemperatureFahrenheit() = 0;

public:
	// CB = Control Bit
	virtual uint8_t getControlRegister();
	virtual void setControlRegister(uint8_t newByte);

	virtual bool getControlRegisterBit(uint8_t bitNumber);
	virtual void setControlRegisterBit(uint8_t bitNumber, bool newBit);

public:
	virtual uint8_t getStatusRegister() = 0;
	virtual void setStatusRegister(uint8_t newByte) = 0;

public:
	virtual int8_t getAgingOffset() = 0;
	virtual void setAgingOffset(int8_t newAgingOffset) = 0;

public:
	virtual void update() = 0;
};

#endif // REALTIMECLOCK_HPP
