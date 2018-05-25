#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP

#include <stdint.h>

class timestamp {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;

	uint8_t minSeconds, minMinutes, minDate, minYear = 0;
	uint8_t minHours, minDay, minMonth = 1;
	uint8_t maxDay = 7;
	uint8_t maxDate = 31;
	uint8_t maxMonth = 12;
	uint8_t maxSeconds, maxMinutes = 59;
	uint8_t maxHours = 23;
	uint16_t maxYear = 99;

	unsigned int amountOfYearShortDigits = 2;

	int toThePowerOf(int base, int power);
	int sizeOfInt(int number);


public:
	timestamp(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t day,
	          uint8_t date, uint8_t month, uint16_t year);
	timestamp();

	void setSeconds(uint8_t newSeconds);
	uint8_t getSeconds() const;

	void setMinutes(uint8_t newMinutes);
	uint8_t getMinutes() const;

	void setHours(uint8_t newHours);
	uint8_t getHours() const;

	void setDay(uint8_t newDay);
	uint8_t getDay() const;

	void setDate(uint8_t newDate);
	uint8_t getDate() const;

	void setMonth(uint8_t newMonth);
	uint8_t getMonth() const;

	void setCentury(uint8_t newCentury);
	uint8_t getCentury() const;

	void setYear(uint16_t newYear);
	uint8_t getYear() const;
};

#endif // TIMESTAMP_HPP
