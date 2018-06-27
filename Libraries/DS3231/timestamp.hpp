// -----------------------------------------------------------
// (C) Copyright Youri Mulder 2018.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// -----------------------------------------------------------

#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP

#include "hwlib-ostream.hpp"
#include <stdint.h>
#include "time.hpp"

/// @brief
///	This class is used to store a timestamp.
/// Using a timestamp makes it easier to store and get any time value.
/// @details
/// This timestamp is made to make it easier for the user to store a given point in time.
/// The class checks the values before storing for extra safety.
/// @warning
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
class timestamp : public time {
protected:
	/// @brief The seconds you want to store. (0 - 59)
	uint8_t seconds;
	/// @brief The minutes you want to store. (0 - 59)
	uint8_t minutes;
	/// @brief The hours you want to store. (0 - 23)
	uint8_t hours;
	/// @brief The hours you want to store. (1 = monday - 7 = sunday)
	uint8_t day;
	/// @brief The date you want to store. (0 - 31)
	uint8_t date;
	/// @brief The month you want to store. (1 - 12)
	uint8_t month;
	/// @brief The year you want to store. (0 - 99)
	/// @warning Note that the value ranges between 0 - 99.
	/// The century is store in another variable @link century @endlink.
	uint8_t year;
	/// @brief The century you want to store
	/// @details The century will be set using the time::currentCentury variable.
	int century;

public:
	/// @brief The constructor to set every variable in this class.
	/// @details
	/// I recommend using this constructor when you already know the values you want to store.
	/// When you use the default constructor every variable will set to the minimum value. <br>
	/// @see
	/// For the minimum values check @ref time.hpp.
	timestamp(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t day,
	          uint8_t date, uint8_t month, uint16_t year);
	/// @brief The default constructor.
	/// @details
	/// Every variable will set to the minimum value. <br>
	/// @see
	/// For the minimum values check @ref time.hpp.
	timestamp();

	/// @brief Set the amount of seconds of the timestamp.
	/// @param newSeconds the amount of seconds you want to store in #seconds.
	/// @details
	/// Before setting the value in #seconds, newSeconds is checked.
	/// Using a function in @ref time.hpp
	/// @see
	/// time::isSecondsValid
	void setSeconds(uint8_t newSeconds);

	/// @brief Get the value of #seconds.
	/// @return An uint8_t containing the value of #seconds.
	uint8_t getSeconds() const;

	/// @brief Set the amount of minutes of the timestamp.
	/// @param newMinutes the amount of minutes you want to store in #minutes.
	/// @details
	/// Before setting the value in #minutes, newMinutes is checked.
	/// Using a function in @ref time.hpp
	/// @see
	/// time::isMinutesValid
	void setMinutes(uint8_t newMinutes);


	/// @brief Get the value of #minutes.
	/// @return An uint8_t containing the value of #minutes.
	uint8_t getMinutes() const;

	/// @brief Set the amount of hours of the timestamp.
	/// @param newHours the amount of hours you want to store in #hours.
	/// @details
	/// Before setting the value in #hours, newHours is checked.
	/// Using a function in @ref time.hpp
	/// @see
	/// time::isHoursValid
	void setHours(uint8_t newHours);

	/// @brief Get the value of #hours.
	/// @return An uint8_t containing the value of #hours.
	uint8_t getHours() const;

	/// @brief Set the the day of the timestamp.
	/// @param newDay the the day you want to store in #day.
	/// @details
	/// Before setting the value in #day, newDay is checked.
	/// Using a function in @ref time.hpp
	/// @see
	/// time::isDayValid
	void setDay(uint8_t newDay);


	/// @brief Get the value of #day.
	/// @return An uint8_t containing the value of #day.
	uint8_t getDay() const;

	/// @brief Set the the date of the timestamp.
	/// @param newDate the the date you want to store in #date.
	/// @details
	/// Before setting the value in #date, newDate is checked.
	/// Using a function in @ref time.hpp
	/// @see
	/// time::isDateValid
	void setDate(uint8_t newDate);

	/// @brief Get the value of #date.
	/// @return An uint8_t containing the value of #date.
	uint8_t getDate() const;

	/// @brief Set the the month of the timestamp.
	/// @param newMonth the the month you want to store in #month.
	/// @details
	/// Before setting the value in #month, newMonth is checked.
	/// Using a function in @ref time.hpp
	/// @see
	/// time::isMonthValid
	void setMonth(uint8_t newMonth);

	/// @brief Get the value of #month.
	/// @return An uint8_t containing the value of #month.
	uint8_t getMonth() const;

	/// @brief set the the year of the timestamp.
	/// @param newYear the the year you want to store in #year.
	/// @details
	/// Before setting the value in #year, newYear is checked.
	/// Using a function in @ref time.hpp
	/// @see
	/// time::isYearValid
	void setYear(uint16_t newYear);

	/// @brief Get the value of #year.
	/// @return An uint8_t containing the value of #year.
	uint8_t getYear() const;

	/// @brief set the the century of the timestamp.
	/// @param newCentury the the century you want to store in #century.
	/// @details
	/// Before setting the value in #century, newCentury is checked.
	/// Using a function in @ref time.hpp
	/// @see
	/// time::isCenturyValid
	void setCentury(int newCentury);

	/// @brief Get the value of #century.
	/// @return An int containing the value of #century.
	int getCentury() const;

	/// @brief Send the current timestamp to an ostream.
	/// @param lhs the ostream you want to change.
	/// @param rhs the timestamp you want to set in the ostream. (lhs)
	/// @return A hwlib::ostream (wouter@voti.nl 2017) containing the previous values and the timestamp.
	/// @details
	/// This method is used to for example print a timestamp the simple way.
	/// @warning Note that the given ostream will be changed during the execution.
	friend hwlib::ostream& operator<<(hwlib::ostream& lhs, const timestamp& rhs);
};

#endif // TIMESTAMP_HPP
