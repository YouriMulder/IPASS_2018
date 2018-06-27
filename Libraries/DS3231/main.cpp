// -----------------------------------------------------------
// (C) Copyright Youri Mulder 2018.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// -----------------------------------------------------------

#include "hwlib.hpp"
#include "DS3231.hpp"
#include "i2cBus.hpp"

int main(int argc, char **argv) {

	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;

	// I2C Bus
	auto I2CScl = hwlib::target::pin_oc(hwlib::target::pins::scl);
	auto I2CSda = hwlib::target::pin_oc(hwlib::target::pins::sda);
	auto I2CBus = i2cBus(I2CScl, I2CSda);

	DS3231 rtc(I2CBus, 0x68);

	// wait for the terminal to start on the PC side
	hwlib::wait_ms(1000);

	// tests chip
	rtc.test();
}
