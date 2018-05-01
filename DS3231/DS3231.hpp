#ifndef DS3231_HPP
#define DS3231_HPP

#include "hwlib.hpp"

struct timeStamp {
	uint16_t year;
	uint8_t month;
	uint8_t day;
};


class DS3231 {
private:
	hwlib::i2c_bus_bit_banged_scl_sda& I2CBus;
	uint8_t DS3231Address;

	static const uint8_t REG_SECONDS = 			0x00;
	static const uint8_t REG_MINUTES = 			0x01;
	static const uint8_t REG_HOURS = 			0x02;
	static const uint8_t REG_DAY = 				0x03;
	static const uint8_t REG_DATE = 			0x04;
	static const uint8_t REG_MONTH_CENTURY = 	0x05;
	static const uint8_t REG_YEAR = 			0x06;

	static const uint8_t REG_ALARM_1_SEC = 		0x07;
	static const uint8_t REG_ALARM_1_MIN = 		0x08;
	static const uint8_t REG_ALARM_1_HOURS = 	0x09;
	static const uint8_t REG_ALARM_1_DAY_DATE =	0x0A;

	static const uint8_t REG_ALARM_2_MIN = 		0x0B;
	static const uint8_t REG_ALARM_2_HOURS = 	0x0C;
	static const uint8_t REG_ALARM_2_DAY_DATE =	0x0D;

	static const uint8_t REG_CONTROL = 			0x0E;
	static const uint8_t REG_STATUS = 			0x0F;
	static const uint8_t REG_AGING_OFFSET = 	0x10;

	static const uint8_t REG_TEMPERATURE_MSB = 	0x11;
	static const uint8_t REG_TEMPERATURE_LSB =	0x12;


public:
	DS3231(hwlib::i2c_bus_bit_banged_scl_sda& I2CBus, uint8_t address);

	void setRegister(uint8_t regAddress);
	uint8_t getByteFromRegister(uint8_t chipRegAddress);

	int getCurrentSeconds();

};

#endif // DS3231_HPP
