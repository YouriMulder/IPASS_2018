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
	uint16_t year;
	uint8_t yearShort;

	static const uint8_t minSeconds, minMinutes, minDate = 0;
	static const uint8_t minHours, minDay, minMonth = 1;
	static const uint8_t maxDay = 7;
	static const uint8_t maxDate = 31;
	static const uint8_t maxMonth = 12;
	static const uint8_t maxSeconds, maxMinutes = 59;
	static const uint8_t maxHours = 23;

	static const unsigned int amountOfYearShortDigits = 2;

	int toThePowerOf(int base, int power);
	void updateShortYear();
	void updateYear();


public:
	timestamp(uint8_t seconds, uint8_t minutes, uint8_t hours,
	          uint8_t day, uint8_t date, uint8_t month,
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

	void setYearShort(uint8_t newYearShort);
	uint8_t getYearShort() const;
};

#endif // TIMESTAMP_HPP
