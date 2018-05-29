#include "time.hpp"

int time::currentCentury = 2000;

void time::increaseCentury() {
    currentCentury += centuryIncreaseValue;
}

bool time::isSecondsValid(uint8_t seconds) {
    return (seconds >= minSeconds && seconds <= maxSeconds);
}

bool time::isMinutesValid(uint8_t minutes) {
    return (minutes >= minMinutes && minutes <= maxMinutes);
}

bool time::isHoursValid(uint8_t hours) {
    return (hours >= minHours && hours <= maxHours);
}

bool time::isDayValid(uint8_t day) {
    return (day >= minDay && day <= maxDay);
}

bool time::isDateValid(uint8_t date) {
    return (date >= minDate && date <= maxDate);
}

bool time::isMonthValid(uint8_t month) {
    return (month >= minMonth && month <= maxMonth);
}

bool time::isYearValid(uint8_t year) {
    return (year >= minYear && year <= maxYear);
}

bool time::isCenturyValid(int century) {
    return (century % 100) == 0;
}
