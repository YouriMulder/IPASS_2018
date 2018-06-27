// -----------------------------------------------------------
// (C) Copyright Youri Mulder 2018.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// -----------------------------------------------------------

#include "time.hpp"

int time::currentCentury = 2000;

void time::increaseCentury() {
	currentCentury += centuryIncreaseValue;
}

bool time::isSecondsValid(uint8_t seconds) const {
	return (seconds >= minSeconds && seconds <= maxSeconds);
}

bool time::isMinutesValid(uint8_t minutes) const {
	return (minutes >= minMinutes && minutes <= maxMinutes);
}

bool time::isHoursValid(uint8_t hours) const {
	return (hours >= minHours && hours <= maxHours);
}

bool time::isDayValid(uint8_t day) const {
	return (day >= minDay && day <= maxDay);
}

bool time::isDateValid(uint8_t date) const {
	return (date >= minDate && date <= maxDate);
}

bool time::isMonthValid(uint8_t month) const {
	return (month >= minMonth && month <= maxMonth);
}

bool time::isYearValid(uint8_t year) const {
	return (year >= minYear && year <= maxYear);
}

bool time::isCenturyValid(int century) const {
	return (century % 100) == 0;
}
