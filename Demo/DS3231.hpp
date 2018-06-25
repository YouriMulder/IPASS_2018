#ifndef DS3231_HPP
#define DS3231_HPP

#include "hwlib-ostream.hpp"
#include "i2cBus.hpp"
#include "time.hpp"
#include "timestamp.hpp"
#include "realTimeClock.hpp"

/// @brief
///	This class is used to communicate with the DS3231 chip.
/// @details
/// This is a basic library for the DS3231 chip.
/// Using the pure virtual class @ref realTimeClock.
/// Execute the tests when you're not sure the chip is connected correctly.
/// @warning
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
class DS3231 : public realTimeClock {
private:
	/// @brief The bus which is used to communicate with the DS3231.
	/// @see
	/// @ref i2cBus.hpp
	i2cBus& I2CBus;

	/// @brief The address the DS3231 chip uses to communicate. (default 0x68)
	uint8_t DS3231Address;

	/// @brief The amount of centuries have passed when started.
	/// @details
	/// This value will increase when the century bit went high using #update.
	int newCentury;

	/// @brief All the interal registers the DS3231 chip has.
	enum REG : uint8_t {
		REG_SECONDS = 0x00,
		REG_MINUTES,
		REG_HOURS,
		REG_DAY,
		REG_DATE,
		REG_MONTH_CENTURY,
		REG_YEAR,

		REG_ALARM_1_SEC,
		REG_ALARM_1_MIN,
		REG_ALARM_1_HOURS,
		REG_ALARM_1_DAY_DATE,

		REG_ALARM_2_MIN,
		REG_ALARM_2_HOURS,
		REG_ALARM_2_DAY_DATE,

		REG_CONTROL,
		REG_STATUS,
		REG_AGING_OFFSET,

		REG_TEMPERATURE_MSB,
		REG_TEMPERATURE_LSB
	};

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
	/// @brief
	/// Constructor for the DS3231 chip.
	/// @param i2cBus the bus which is used to communicate with the DS3231. @see i2cBus.hpp
	/// @param address the address which is used to communicate with the DS3231 chip. (default = 0x68)
	DS3231(i2cBus& I2CBus, uint8_t address = 0x68);

private:
	/// @brief
	/// Set the i2cBus::currentChipAddress to the address of the DS3231
	/// @details
	/// Everytime before communicating with the DS3231 this function is called.
	/// Because any other chip might have changed the i2cBus::currentChipAddress variable.
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
	/// @brief this used to get a alarm register. The MSB is not needed because that is the alarm rate.
	/// @param alarmRegister the alarm register you want to get the value of.
	/// @return An uint8_t containing the value of the alarm register without the MSB bit.
	/// @details
	/// This method is used to get the alarm registers. The MSB is a part of the alarm rate.
	/// More info about the alarm rate can be found at:
	/// <a href="https://datasheets.maximintegrated.com/en/ds/DS3231.pdf">DS3231 Datasheet page 12, table 2</a>
	uint8_t getAlarmBCDRegisterExMSB(uint8_t alarmRegister);

	/// @brief this used to set a alarm register. The MSB is not set because that is the alarm rate.
	/// @param alarmRegister the alarm register you want to get the value of.
	/// @param newByte the byte you want to set into the alarm register. The MSB will be removed in copy of this value.
	/// @details
	/// This method is used to set the alarm registers. The MSB is a part of the alarm rate which doesn't has to be changed.
	/// More info about the alarm rate can be found at:
	/// <a href="https://datasheets.maximintegrated.com/en/ds/DS3231.pdf">DS3231 Datasheet page 12, table 2</a>
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
