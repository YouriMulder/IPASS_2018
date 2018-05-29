#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP

#include "hwlib-ostream.hpp"
#include <stdint.h>
#include "time.hpp"

class timestamp : public time {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;
	int century;

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

	void setYear(uint16_t newYear);
	uint8_t getYear() const;

	void setCentury(int newCentury);
	int getCentury() const;

	friend hwlib::ostream& operator<<(hwlib::ostream& lhs, const timestamp& rhs);
};

#endif // TIMESTAMP_HPP
