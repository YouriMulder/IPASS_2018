#include "timestamp.hpp"

timestamp::timestamp(uint8_t seconds, uint8_t minutes, uint8_t hours,
                     uint8_t day, uint8_t date, uint8_t month,
                     uint16_t year):
	seconds(seconds), minutes(minutes), hours(hours), day(day),
	date(date),	month(month), year(year)
{}

timestamp::timestamp():
	seconds(minSeconds), minutes(minMinutes), hours(minHours), day(minDay),
	date(minDate),	month(minMonth), year(minYear)
{}

int timestamp::toThePowerOf(int base, int power) {
	int result = base;
	if(result == 0) { return 0; }

	for(int i = 1; i < power; power++) { result *= base; }
	return result;
}

int timestamp::sizeOfInt(int number) {
	unsigned int counter = 0;
	while(number > 0) {
		counter++;
		number /= 10;
	}
	return counter;
}

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

void timestamp::setYear(uint16_t newYear) {
	if(newYear < 100) {
		year = (newYear >= minYear && newYear <= maxYear)
		       ? newYear : minYear;
	} else {
		year = newYear / (sizeOfInt(newYear) - 2);
	}
}

uint8_t timestamp::getYear() const {
	return year;
}
