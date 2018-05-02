#include "timestamp.hpp"

timestamp::timestamp(uint8_t seconds, uint8_t minutes, uint8_t hours,
                     uint8_t day, uint8_t date, uint8_t month, uint8_t century,
                     uint16_t year):
	seconds(seconds), minutes(minutes), hours(hours), day(day),
	date(date),	month(month), century(century), year(year)
{}

void timestamp::setSeconds(uint8_t newSeconds) {
	seconds = (newSeconds >= minSeconds && newSeconds <= maxSeconds)
	          ? newSeconds : minSeconds;
}

uint8_t timestamp::getSeconds() const {
	return seconds;
}

void timestamp::setMinutes(uint8_t newMinutes) {
	minutes = (newMinutes >= minMinutes && newMinutes <= maxMinutes)
	          ? newMinutes : minMinutes;
}
uint8_t timestamp::getMinutes() const {
	return minutes;
}

void timestamp::setHours(uint8_t newHours) {
	hours = (newHours >= minHours && newHours <= maxHours)
	        ? newHours : minHours;
}

uint8_t timestamp::getHours() const {
	return hours;
}

void timestamp::setDay(uint8_t newDay) {
	day = (newDay >= minDay && newDay <= maxDay)
	      ? newDay : minDay;
}

uint8_t timestamp::getDay() const {
	return day;
}

void timestamp::setDate(uint8_t newDate) {
	date = (newDate >= minDate && newDate <= maxDate)
	       ? newDate : minDate;
}

uint8_t timestamp::getDate() const {
	return date;
}

void timestamp::setMonth(uint8_t newMonth) {
	month = (newMonth >= minMonth && newMonth <= maxMonth)
	        ? newMonth : minMonth;
}

uint8_t timestamp::getMonth() const {
	return month;
}

void timestamp::setCentury(bool newCentury) {
	Century = (newHours >= minHours && newHours <= maxHours)
	          ? newHours : minHours;
}

uint8_t timestamp::getCentury() const {
	return century;
}

void timestamp::setYear(uint16_t newYear) {

}

uint16_t timestamp::getYear() const {
	return year;
}
