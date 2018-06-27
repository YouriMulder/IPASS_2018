// -----------------------------------------------------------
// (C) Copyright Youri Mulder 2018.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// -----------------------------------------------------------

#include "hwlib.hpp"
#include "DS3231.hpp"
#include "i2cBus.hpp"
#include "spiBus.hpp"
#include "MFRC522.hpp"
#include "HCSR501.hpp"
#include "buzzer.hpp"
#include "displayManager.hpp"
#include "alarm.hpp"

int main(int argc, char **argv) {

	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;

	// I2C Bus
	auto I2CScl = hwlib::target::pin_oc(hwlib::target::pins::scl);
	auto I2CSda = hwlib::target::pin_oc(hwlib::target::pins::sda);
	auto I2CBus = i2cBus(I2CScl, I2CSda);

	// I2C Bus 2
	auto I2CScl2 = hwlib::target::pin_oc(hwlib::target::pins::scl1);
	auto I2CSda2 = hwlib::target::pin_oc(hwlib::target::pins::sda1);
	auto I2CBus2 = i2cBus(I2CScl2, I2CSda2);

	// SPI bus
	auto SPIMosi = hwlib::target::pin_out(hwlib::target::pins::d11);
	auto SPIMiso = hwlib::target::pin_in(hwlib::target::pins::d12);
	auto SPIScl	 = hwlib::target::pin_out(hwlib::target::pins::d8);
	auto SPIBus  = spiBus(SPIScl, SPIMosi, SPIMiso);

	// MFRC522
	auto SPISSMFRC522 	= hwlib::target::pin_out(hwlib::target::pins::d10);
	auto MFRC522Reset 	= hwlib::target::pin_out(hwlib::target::pins::d9);
	MFRC522 rfidReader	= MFRC522(SPIBus, SPISSMFRC522, MFRC522Reset);

	// PIR HCSR501
	auto HCSR501Input		= hwlib::target::pin_in(hwlib::target::pins::d2);
	HCSR501 motionDetector	= HCSR501(HCSR501Input);

	// Buzzer
	auto buzzerPin = hwlib::target::pin_in_out(hwlib::target::pins::d18);
	auto horn 	   = buzzer(buzzerPin);

	// Screen
	auto w = hwlib::glcd_oled(I2CBus2, 0x3C);
	auto dManager = displayManager(w);

	DS3231 rtc(I2CBus, 0x68);
	alarm theftAlarm(rtc, rfidReader, motionDetector, horn, dManager);

	// wait for the terminal to start on the PC side
	hwlib::wait_ms(1000);

	// tests chips
	rtc.test();
	rfidReader.test();
	motionDetector.test();


	timestamp ts;
	uint8_t sec = rtc.getCurrentSeconds();
	rtc.setCurrentSeconds(0); // 0 - 59
	rtc.setCurrentMinutes(21); // 0 - 59
	rtc.setCurrentHours(17);
	rtc.setCurrentDay(5);
	rtc.setCurrentDate(1);
	rtc.setCurrentMonth(6);
	rtc.setCurrentYear(18);

	for(;;) {
		if(sec != rtc.getCurrentSeconds()) {
			sec = rtc.getCurrentSeconds();
			rtc.getCurrentTimestamp(ts);
			//hwlib::wait_ms(100);
			dManager.updateTime(ts);
			dManager.updateTemperature(rtc.getCurrentTemperatureCelsius());
			dManager.draw();
		}
		theftAlarm.update();
	}
}
