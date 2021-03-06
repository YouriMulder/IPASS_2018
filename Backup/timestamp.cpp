#include "timestamp.hpp"

timestamp::timestamp(uint8_t seconds, uint8_t minutes, uint8_t hours,
                     uint8_t day, uint8_t date, uint8_t month,
                     uint16_t year):
	seconds(seconds), minutes(minutes), hours(hours), day(day),
	date(date),	month(month), year(year) {
	setCentury(time::currentCentury);
}

timestamp::timestamp():
	seconds(minSeconds), minutes(minMinutes), hours(minHours), day(minDay),
	date(minDate),	month(minMonth), year(minYear) {
	setCentury(time::currentCentury);
}

void timestamp::setSeconds(uint8_t newSeconds) {
	seconds = time::isSecondsValid(newSeconds) ? newSeconds : minSeconds;
}

uint8_t timestamp::getSeconds() const {
	return seconds;
}

void timestamp::setMinutes(uint8_t newMinutes) {
	minutes = time::isMinutesValid(newMinutes) ? newMinutes : minMinutes;
}
uint8_t timestamp::getMinutes() const {
	return minutes;
}

void timestamp::setHours(uint8_t newHours) {
	hours = time::isHoursValid(newHours) ? newHours : minHours;
}

uint8_t timestamp::getHours() const {
	return hours;
}

void timestamp::setDay(uint8_t newDay) {
	day = time::isDayValid(newDay) ? newDay : minDay;
}

uint8_t timestamp::getDay() const {
	return day;
}

void timestamp::setDate(uint8_t newDate) {
	date = time::isDateValid(newDate) ? newDate : minDate;
}

uint8_t timestamp::getDate() const {
	return date;
}

void timestamp::setMonth(uint8_t newMonth) {
	month = time::isMonthValid(newMonth) ? newMonth : minMonth;
}

uint8_t timestamp::getMonth() const {
	return month;
}

void timestamp::setYear(uint16_t newYear) {
	year = time::isYearValid(newYear) ? newYear : minYear;
}

uint8_t timestamp::getYear() const {
	return year;
}

void timestamp::setCentury(int newCentury) {
	century = time::isCenturyValid(newCentury) ? newCentury : 0;
}

int timestamp::getCentury() const {
	return century;
}

hwlib::ostream& operator<<(hwlib::ostream& lhs, const timestamp& rhs) {
	lhs  <<	(unsigned)rhs.hours << "::" << (unsigned)rhs.minutes << "::" <<	(unsigned)rhs.seconds << "\n"
	     <<	(unsigned)rhs.date << '/' << (unsigned)rhs.month << '/' << (rhs.century + (unsigned)rhs.year);
	return lhs;
}
