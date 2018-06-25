#ifndef TIME_HPP
#define TIME_HPP

#include <cstdint>

/// @brief
///	Basic time functions like checking if a givens number of seconds is valid.
/// @warning
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
class time {
public:
	const uint8_t minSeconds = 0;
	const uint8_t minMinutes = 0;
	const uint8_t minDate = 0;
	const uint8_t minYear = 0;
	const uint8_t minHours = 1;
	const uint8_t minDay = 1;
	const uint8_t minMonth = 1;
	const uint8_t maxDay = 7;
	const uint8_t maxDate = 31;
	const uint8_t maxMonth = 12;
	const uint8_t maxSeconds = 59;
	const uint8_t maxMinutes = 59;
	const uint8_t maxHours = 23;
	const uint8_t maxYear = 99;

private:
	/// @brief
	/// This is the amount currentCentury will increase
	/// when the century bit in realTimeClock is a logic 1 and the update function is called in @ref realTimeClock.hpp.
	static const uint8_t centuryIncreaseValue = 100;
public:
	/// @brief
	/// This is the current century of the real-time clock you might use.
	/// @details
	/// This is a shared variable between instances.
	/// To return a correct year value the real-time clock has to know the current century.
	/// @warning Changing this means every connected real-time clock his century will increase.
	static int currentCentury;
public:
	/// @brief
	/// Increase the #currentCentury using #centuryIncreaseValue
	/// @details
	/// #currentCentury will be increased by the value of #centuryIncreaseValue <br>
	/// #currentCentury += #centuryIncreaseValue
	/// @warning
	/// Using this method means every connected real-time clock his century will increase.
	static void increaseCentury();

public:
	/// @brief
	/// Check if the given seconds is a valid value.
	/// @param seconds the value you want to check if it's valid
	/// @return A bool containing 1 when the given seconds is valid and 0 when it's not valid.
	/// @details
	/// This methods check whether the given amount of seconds is
	/// between @link minSeconds @endlink and @link maxSeconds @endlink or not.
	bool isSecondsValid(uint8_t seconds) const;

	/// @brief
	/// Check if the given minutes is a valid value.
	/// @param minutes the value you want to check if it's valid
	/// @return A bool containing 1 when the given minutes valid and 0 when it's not valid.
	/// @details
	/// This methods check whether the given amount of minutes is
	/// between @link minMinutes @endlink and @link maxMinutes @endlink or not.
	bool isMinutesValid(uint8_t minutes) const;

	/// @brief
	/// Check if the given hours is a valid value.
	/// @param hours the value you want to check if it's valid
	/// @return A bool containing 1 when the given hours valid and 0 when it's not valid.
	/// @details
	/// This methods check whether the given amount of hours is
	/// between @link minHours @endlink and @link maxHours @endlink or not.
	bool isHoursValid(uint8_t hours) const;

	/// @brief
	/// Check if the given day is a valid value.
	/// @param day the value you want to check if it's valid
	/// @return A bool containing 1 when the given day valid and 0 when it's not valid.
	/// @details
	/// This methods check whether the given day is
	/// between @link minDay @endlink and @link maxDay @endlink or not.
	bool isDayValid(uint8_t day) const;

	/// @brief
	/// Check if the given date is a valid value.
	/// @param date the value you want to check if it's valid
	/// @return A bool containing 1 when the given date valid and 0 when it's not valid.
	/// @details
	/// This methods check whether the given day is
	/// between @link minDate @endlink and @link maxDate @endlink or not.
	/// @warning @link maxDate @endlink is 31. This means there is not a check for leap years.
	/// or any month with less than 31 days.
	bool isDateValid(uint8_t date) const;

	/// @brief
	/// Check if the given month is a valid value.
	/// @param month the value you want to check if it's valid
	/// @return A bool containing 1 when the given month valid and 0 when it's not valid.
	/// @details
	/// This methods check whether the given month is
	/// between @link minMonth @endlink and @link maxMonth @endlink or not.
	bool isMonthValid(uint8_t month) const;

	/// @brief
	/// Check if the given year is a valid value.
	/// @param year the value you want to check if it's valid
	/// @return A bool containing 1 when the given year valid and 0 when it's not valid.
	/// @details
	/// This methods check whether the given year is
	/// between @link minYear @endlink and @link maxYear @endlink or not.
	/// @warning Note that the year value in this case is only the year in the century.
	/// This means it is a two digit number ranging from 0 - 99.
	bool isYearValid(uint8_t year) const;

	/// @brief
	/// Check if the given century is a valid value.
	/// @param century the value you want to check if it's valid
	/// @return A bool containing 1 when the given year valid and 0 when it's not valid.
	/// @details
	/// This methods check whether the given century is valid.
	/// This is basicly a check if the last two digits are zeroes. <br>
	/// For example: <br>
	/// 2200 =   valid <br>
	/// 2202 = invalid <br>
	/// 101200 =   valid <br>
	/// 101210 = invalid <br>
	bool isCenturyValid(int century) const;
};

#endif // TIME_HPP
