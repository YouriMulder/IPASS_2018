// -----------------------------------------------------------
// (C) Copyright Youri Mulder 2018.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// -----------------------------------------------------------

#ifndef REALTIMECLOCK_HPP
#define REALTIMECLOCK_HPP

#include "timestamp.hpp"

/// @brief
///	A pure virtual class for a real-time clock chip like the DS3231.
/// @details
/// This class is a pure virtual class.
/// This means that you can access methods of the derived class when using reference or pointers.
/// This makes the code easier to expand.
/// @warning
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
class realTimeClock : public time {
public:
	/// @brief
	/// Get the current value of the seconds register.
	/// @return
	/// An uint8_t that contains the current value of the seconds register. (0 - 59)
	virtual uint8_t getCurrentSeconds() = 0;

	/// @brief
	/// Set a new value in the seconds register.
	/// @param newSeconds the value you want to set into the seconds register. (0 - 59)
	/// @warning
	/// This method will override the current value in the seconds register.
	virtual void setCurrentSeconds(uint8_t newSeconds) = 0;

	/// @brief
	/// Get the current value of the minutes register of the realtimeclock chip.
	/// @return
	/// An uint8_t that contains the current value of the minutes register. (0 - 59)
	virtual uint8_t getCurrentMinutes() = 0;

	/// @brief
	/// Set a new value in the minutes register.
	/// @param newMinutes the value you want to set into the minutes register.
	/// @warning
	/// This method will override the current value in the minutes register. (0 - 59)
	virtual void setCurrentMinutes(uint8_t newMinutes) = 0;

	/// @brief
	/// Get the current value of the hours register.
	/// @return
	/// An uint8_t that contains the current value of the hours register. (0 - 23)
	virtual uint8_t getCurrentHours() = 0;

	/// @brief
	/// Set a new value in the hours register.
	/// @param newHours the value you want to set into the hours register. (0 - 23)
	/// @warning
	/// This method will override the current value in the hours register.
	virtual void setCurrentHours(uint8_t newHours) = 0;

	/// @brief
	/// Get the current value in the day register.
	/// @return
	/// An uint8_t that contains the current value of the day register
	/// of the realtimeclock chip. (1 = monday 7 == sunday)
	virtual uint8_t getCurrentDay() = 0;

	/// @brief
	/// Set a new value in the day register.
	/// @param newDay the value you want to set into the day register. (1 = monday 7 == sunday)
	/// @warning
	/// This method will override the current value in the day register.
	virtual void setCurrentDay(uint8_t newDay) = 0;

	/// @brief
	/// Get the current value in the date register.
	/// @return
	/// An uint8_t that contains the current value of the date register. (1 - ~31)
	virtual uint8_t getCurrentDate() = 0;

	/// @brief
	/// Set a new value in the date register.
	/// @param newDate the value you want to set into the date register. (1 - ~32)
	/// @warning
	/// This method will override the current value in the date register.
	virtual void setCurrentDate(uint8_t newDate) = 0;

	/// @brief
	/// Get the current value in the month register.
	/// @return
	/// A uint8_t that contains the current value of the month register. (1 - 12)
	virtual uint8_t getCurrentMonth() = 0;

	/// @brief
	/// Set a new value in the month register.
	/// @param newMonth the value you want to set into the month register. (1 - 12)
	/// @warning
	/// This method will override the current value in the month register.
	virtual void setCurrentMonth(uint8_t newMonth) = 0;

	/// @brief
	/// Get the current century bit in the centrury register.
	/// @return
	/// A bool that contains the current value of the month register. (0 or 1)
	virtual bool getCurrentCenturyBit() = 0;

	/// @brief
	/// Set a new value in the month register.
	/// @details
	/// The currentCentury in @ref time.hpp will be updated after this bit was high
	/// when you call update.
	/// @warning
	/// This method will override the current value in the month register.
	/// @warning Only use this function if you know what you're doing.
	/// The currentCentury in @ref time.hpp will be updated after this bit was high
	/// when you call #update.
	virtual void ResetCurrentCenturyBit() = 0;

	/// @brief
	/// Get the current value in the year register.
	/// @return
	/// A uin8_t containing the current value of the year register (0 - 99)
	/// @warning
	/// Most chips will set the century bit when the year register went past 99.
	/// Note when the century bit is high you're in a new century.
	/// #update will update the currentCentury in @ref time.hpp
	/// and reset the century bit.
	virtual uint8_t getCurrentYear() = 0;

	/// @brief
	/// Set a new value in the year register.
	/// @param newYear the value you want to set into the year register. (0 - 99)
	/// @warning
	/// This method will override the current value in the year register.
	/// @warning
	/// Most chips will set the century bit when the year register went past 99.
	/// Note when the century bit is high you're in a new century.
	/// #update will update the currentCentury in @ref time.hpp
	/// and reset the century bit.
	virtual void setCurrentYear(uint8_t newYear) = 0;


	/// @brief
	/// Get the current timestamp in an array.
	/// @param data[] is a pointer to an array where the current timestamp will be stored in.
	/// @details
	/// This method returns a array with raw data (BCD values) of the following registers:
	/// array[0] = seconds
	/// array[1] = minutes
	/// array[2] = hours
	/// array[3] = day
	/// array[4] = date
	/// array[5] = month
	/// array[6] = year
	/// array[7] = century (@ref time.hpp currentCentury)
	/// @warning
	/// The array will be filled with raw data. Most registers are BCD register.
	/// This means that the decimal value might not be what you expected.
	/// @warning
	/// Note that the array must have a size of 7.
	/// All the data in the array will be overritten.
	virtual void getCurrentTimeData(uint8_t data[7]) = 0;

	/// @brief
	/// Get the a current timestamp @ref timestamp.hpp.
	/// @return a timestamp with the containing the current time.
	/// @details
	/// This method returns a timestamp with the same data as #getCurrentTimeData.
	/// You might want to use this over #getCurrentTimeData
	/// because there is extra functionality in the timestamp class.
	/// Look at @ref timestamp.hpp for further information about the timestamp format.
	virtual timestamp getCurrentTimestamp() = 0;

	/// @brief
	/// Update a existing timestamp.
	/// @param ts the timestamp you want to update.
	/// @details
	/// This method will change the given timestamp ts its value to the current time.
	/// @warning The given timestamp ts will be changed when this method is executed.
	virtual void getCurrentTimestamp(timestamp& ts) = 0;

	/// @brief
	/// Get the value of the alarm one seconds register.
	/// @return An uint8_t containing the current value in alarm 1 seconds register.
	virtual uint8_t getAlarmOneSeconds() = 0;

	/// @brief
	/// Set a new value in the alarm one seconds register.
	/// @param newSeconds The value you want to store in the alarm 1 seconds register.
	/// @warning
	/// The value in the alarm one seconds register will change.
	virtual void setAlarmOneSeconds(uint8_t newSeconds) = 0;

	/// @brief
	/// Get the value of the alarm 1/2 minutes register.
	/// @param alarm The alarm you want the value of (0 or 1).
	/// @return An uint8_t containing the current value in alarm 1/2 minutes register.
	/// @details
	/// This method will get you the current value of the any alarm minutes register.
	/// You can choose which alarm register using the parameter alarm.
	/// 0 = alarm one, 1 = alarm two.
	/// @warning Note that the paramether is a boolean.
	/// Therefore alarm one = 0 and alarm two = 1.
	virtual uint8_t getAlarmMinutes(bool alarm) = 0;

	/// @brief
	/// Set a new value in the alarm 1/2 minutes register.
	/// @param alarm The alarm you want the value of (0 or 1).
	/// @param newMinutes The value you want to store in the alarm 1/2 register.
	/// @details
	/// This method will set a new value into the chosen alarm minutes register.
	/// You can choose which alarm register using the parameter alarm.
	/// 0 = alarm one, 1 = alarm two.
	/// @warning note that the paramether is a boolean.
	/// Therefore alarm one = 0 and alarm two = 1.
	/// @warning The value in the chosen alarm minutes register will change.
	virtual void setAlarmMinutes(bool alarm, uint8_t newMinutes) = 0;

	/// @brief
	/// Get the value of the alarm 1/2 hours register.
	/// @param alarm The alarm you want the value of (0 or 1).
	/// @return An uint8_t containing the current value in alarm 1/2 hours register.
	/// @details
	/// This method will get you the current value of the any alarm hours register.
	/// You can choose which alarm register using the parameter alarm.
	/// 0 = alarm one, 1 = alarm two.
	/// @warning Note that the paramether is a boolean.
	/// Therefore alarm one = 0 and alarm two = 1.
	virtual uint8_t getAlarmHours(bool alarm) = 0;

	/// @brief
	/// Set a new value in the alarm 1/2 hours register.
	/// @param alarm The alarm you want the value of (0 or 1).
	/// @param newHours The value you want to store in the alarm 1/2 register.
	/// @details
	/// This method will set a new value into the chosen alarm hours register.
	/// You can choose which alarm register using the parameter alarm.
	/// 0 = alarm one, 1 = alarm two.
	/// @warning Note that the paramether is a boolean.
	/// Therefore alarm one = 0 and alarm two = 1.
	/// @warning The value in the chosen alarm hours register will change.
	virtual void setAlarmHours(bool alarm, uint8_t newHours) = 0;

	/// @brief
	/// Get the value of the alarm 1/2 day and date register.
	/// @param alarm The alarm you want the value of (0 or 1).
	/// @return An uint8_t containing the current value in alarm 1/2 day and date register.
	/// @details
	/// This method will get you the current value of the any alarm day and date register.
	/// You can choose which alarm register using the parameter alarm.
	/// 0 = alarm one, 1 = alarm two.
	/// @warning Note that the paramether is a boolean.
	/// Therefore alarm one = 0 and alarm two = 1.
	virtual uint8_t getAlarmDayDate(bool alarm) = 0;

	/// @brief
	/// Set a new value in the alarm 1/2 day and date register.
	/// @param alarm The alarm you want the value of (0 or 1).
	/// @param newDayDate The value you want to store in the alarm 1/2 day and date register.
	/// @details
	/// This method will set a new value into the chosen alarm day and date register.
	/// You can choose which alarm register using the parameter alarm.
	/// 0 = alarm one, 1 = alarm two.
	/// @warning Note that the paramether is a boolean.
	/// Therefore alarm one = 0 and alarm two = 1.
	/// @warning The value in the chosen alarm day and date register will change.
	virtual void setAlarmDayDate(bool alarm, uint8_t newDayDate) = 0;

public:
	/// @brief
	/// Get the current temperature in degrees celsius.
	/// @return An int16_t containing the current temperature in degrees celsius.
	/// @details
	/// Note that it is a int16_t, this means that the value IS NOT be a floating point number.
	/// Most chips will support a floating point number.
	/// But it's not very smart to use those because of the small computer we are using (Arduino due).
	/// The floating point numbers are in my opinion not really needed to display a accurate temperature.
	virtual int16_t getCurrentTemperatureCelsius() = 0;

	/// @brief
	/// Get the current temperature in degrees fahrenheit.
	/// @return An int16_t containing the current temperature in degrees farhenheit.
	/// @details
	/// Note that it is a int16_t, this means that the value IS NOT be a floating point number.
	/// Most chips will support a floating point number.
	/// But it's not very smart to use those because of the small computer we are using (Arduino due).
	/// The floating point numbers are in my opinion not really needed to display a accurate temperature.
	/// The used formula for correct convertion can be found here:
	/// <a href="https://www.rapidtables.com/convert/temperature/how-celsius-to-fahrenheit.html">Celcius to Farhenheit formula</a>
	virtual int16_t getCurrentTemperatureFahrenheit() = 0;

public:
	/// @brief
	/// Get the current value in the control register.
	/// @return An uint8_t containing the current value in the control register.
	/// @details
	/// DS3231 control register bits: \n
	/// Bit 0 	= Alarm one interrupt enable. (logic 1)
	/// Bit 1 	= Alarm two interrupt enable. (logic 1)
	/// Bit 2 	= Interrupt control. (SQW pin)
	/// Bit 3/4 = Rate select. (SQW frequency)
	/// Bit 5	= Convert temperature.
	/// Bit 6 	= Battery-Backed Square-Wave enable
	/// Bit 7 	= Enable oscillator (logic 0)
	/// For further information about the bits look at the datasheet of the chip you're using.
	/// <a href="https://datasheets.maximintegrated.com/en/ds/DS3231.pdf">DS3231 Datasheet page 13</a>
	virtual uint8_t getControlRegister();

	/// @brief
	/// Set a new value in the control register.
	/// @param newByte the new value you want to store in the control register.
	/// @details
	/// DS3231 control register bits: <br>
	/// Bit 0 	= Alarm one interrupt enable. (logic 1) <br>
	/// Bit 1 	= Alarm two interrupt enable. (logic 1) <br>
	/// Bit 2 	= Interrupt control. (SQW pin) <br>
	/// Bit 3/4 = Rate select. (SQW frequency) <br>
	/// Bit 5	= Convert temperature. <br>
	/// Bit 6 	= Battery-Backed Square-Wave enable <br>
	/// Bit 7 	= Enable oscillator (logic 0) <br>
	/// For further information about the bits look at the datasheet of the chip you're using.
	/// <a href="https://datasheets.maximintegrated.com/en/ds/DS3231.pdf">DS3231 Datasheet page 13</a>
	virtual void setControlRegister(uint8_t newByte);

	/// @brief
	/// Get only one bit from the control register.
	/// @param bitNumber the bit you want to set in the control register.
	/// @return A bool containing the value of the bitNumber in the control register.
	/// @details
	/// DS3231 control register bits: <br>
	/// Bit 0 	= Alarm one interrupt enable. (logic 1) <br>
	/// Bit 1 	= Alarm two interrupt enable. (logic 1) <br>
	/// Bit 2 	= Interrupt control. (SQW pin) <br>
	/// Bit 3/4 = Rate select. (SQW frequency) <br>
	/// Bit 5	= Convert temperature. <br>
	/// Bit 6 	= Battery-Backed Square-Wave enable <br>
	/// Bit 7 	= Enable oscillator (logic 0) <br>
	/// For further information about the bits look at the datasheet of the chip you're using.
	/// <a href="https://datasheets.maximintegrated.com/en/ds/DS3231.pdf">DS3231 Datasheet page 13</a>
	virtual bool getControlRegisterBit(uint8_t bitNumber);

	/// @brief
	/// Set only one bit in the control register.
	/// @param bitNumber the bit you want to set in the control register.
	/// @param newBit the value the bitNumber will be set to.
	/// @details
	/// DS3231 control register bits: <br>
	/// Bit 0 	= Alarm one interrupt enable. (logic 1) <br>
	/// Bit 1 	= Alarm two interrupt enable. (logic 1) <br>
	/// Bit 2 	= Interrupt control. (SQW pin) <br>
	/// Bit 3/4 = Rate select. (SQW frequency) <br>
	/// Bit 5	= Convert temperature. <br>
	/// Bit 6 	= Battery-Backed Square-Wave enable <br>
	/// Bit 7 	= Enable oscillator (logic 0) <br>
	/// For further information about the bits look at the datasheet of the chip you're using.
	/// <a href="https://datasheets.maximintegrated.com/en/ds/DS3231.pdf">DS3231 Datasheet page 13</a>
	virtual void setControlRegisterBit(uint8_t bitNumber, bool newBit);

public:
	/// @brief
	/// Get a new value in the status register.
	/// @return An uint8_t containing the current value in the status register.
	/// @details
	/// DS3231 status register bits: <br>
	/// Bit 0 = Alarm one flag. (Time matched in the alarm registers) <br>
	/// Bit 1 = Alarm two flag. (Time matched in the alarm registers) <br>
	/// Bit 2 = Busy. (TCXO functions executing) <br>
	/// Bit 3 = Enable 32kHz output. <br>
	/// Bit 4 = RESERVED. <br>
	/// Bit 5 = RESERVED. <br>
	/// Bit 6 = RESERVED. <br>
	/// Bit 7 = Oscillator stop flag. (logic 1) <br>
	/// For further information about the bits look at the datasheet of the chip you're using.
	/// <a href="https://datasheets.maximintegrated.com/en/ds/DS3231.pdf">DS3231 Datasheet page 14</a>
	virtual uint8_t getStatusRegister() = 0;

	/// @brief
	/// Set only one bit in the control register.
	/// @param newByte the new value you want to store in the status register
	/// @details
	/// DS3231 status register bits: <br>
	/// Bit 0 = Alarm one flag. (Time matched in the alarm registers) <br>
	/// Bit 1 = Alarm two flag. (Time matched in the alarm registers) <br>
	/// Bit 2 = Busy. (TCXO functions executing) <br>
	/// Bit 3 = Enable 32kHz output. <br>
	/// Bit 4 = RESERVED. <br>
	/// Bit 5 = RESERVED. <br>
	/// Bit 6 = RESERVED. <br>
	/// Bit 7 = Oscillator stop flag. (logic 1) <br>
	/// For further information about the bits look at the datasheet of the chip you're using.
	/// <a href="https://datasheets.maximintegrated.com/en/ds/DS3231.pdf">DS3231 Datasheet page 14</a>
	/// @warning
	/// Most of the bits in the status register are not meant to be changed by the user.
	virtual void setStatusRegister(uint8_t newByte) = 0;

public:
	/// @brief
	/// Get the current value in the aging offset register.
	/// @return An int8_t containing the current value in the aging offset register.
	/// @details
	/// "Positive aging values add capacitance to the array, slowing
	/// the oscillator frequency. Negative values remove
	/// capacitance from the array, increasing the oscillator frequency."
	/// For further information about the aging offset look at the datasheet of the chip you're using.
	/// <a href="https://datasheets.maximintegrated.com/en/ds/DS3231.pdf">DS3231 Datasheet page 14</a>
	virtual int8_t getAgingOffset() = 0;

	/// @brief
	/// Set a new value in the aging offset register.
	/// @param newAgingOffset the new value you want to set into the aging offset register.
	/// @details
	/// "Positive aging values add capacitance to the array, slowing
	/// the oscillator frequency. Negative values remove
	/// capacitance from the array, increasing the oscillator frequency."
	/// For further information about the aging offset look at the datasheet of the chip you're using.
	/// <a href="https://datasheets.maximintegrated.com/en/ds/DS3231.pdf">DS3231 Datasheet page 14</a>
	/// @warning The real-time clock might become inaccurate after changing this value.
	virtual void setAgingOffset(int8_t newAgingOffset) = 0;

public:

	/// @brief
	/// Every time this method is called the century bit will be checked and further action will be taken.
	/// @details
	/// When the century bit is active it means that we are in a new century from now on.
	/// The currentCentury value will be changed accordingly in @ref time.hpp.
	/// @warning
	/// Note that the currentCentury value in @ref time.hpp is shared between instances. Because it is static.
	/// You should only call this function if you want to change the currentCentury of all the instances.
	virtual void update() = 0;

	/// @brief
	/// This checks if the chip is functioning correctly.
	/// Make sure you connected everything correctly before executing.
	/// @details
	/// Testing might take a while. Wait till the end test message appears.
	virtual void test() = 0;
};

#endif // REALTIMECLOCK_HPP
