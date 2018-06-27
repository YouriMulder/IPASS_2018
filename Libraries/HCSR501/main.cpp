// -----------------------------------------------------------
// (C) Copyright Youri Mulder 2018.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// -----------------------------------------------------------

#include "hwlib.hpp"
#include "HCSR501.hpp"

int main(int argc, char **argv) {

	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;

	// PIR HCSR501
	auto HCSR501Input		= hwlib::target::pin_in(hwlib::target::pins::d2);
	HCSR501 motionDetector	= HCSR501(HCSR501Input);

	// wait for the terminal to start on the PC side
	hwlib::wait_ms(1000);

	hwlib::cout << "Chip is starting up. Capacitors must be filled\n";
	hwlib::wait_ms(1000);

	// tests chip
	motionDetector.test();
}
