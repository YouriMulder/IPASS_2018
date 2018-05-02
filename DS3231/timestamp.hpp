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
	uint8_t century;
	uint16_t year;

	static const uint8_t minSeconds, minMinutes, minDate, minYear = 0;
	static const uint8_t minHours, minDay, minMonth = 1;

	static const uint8_t maxSeconds, maxMinutes = 59;


public:
	timestamp(uint8_t seconds, uint8_t minutes, uint8_t hours,
	          uint8_t day, uint8_t date, uint8_t month, uint8_t century,
	          uint16_t year);

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
	uint16_t getYear() const;






};

#endif // TIMESTAMP_HPP
