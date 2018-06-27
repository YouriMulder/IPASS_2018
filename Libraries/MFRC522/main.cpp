// -----------------------------------------------------------
// (C) Copyright Youri Mulder 2018.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// -----------------------------------------------------------

#include "hwlib.hpp"
#include "spiBus.hpp"
#include "MFRC522.hpp"

/// RFID reader test MFRC522
int main(int argc, char **argv) {

	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;

	// SPI bus
	auto SPIMosi = hwlib::target::pin_out(hwlib::target::pins::d11);
	auto SPIMiso = hwlib::target::pin_in(hwlib::target::pins::d12);
	auto SPIScl	 = hwlib::target::pin_out(hwlib::target::pins::d8);
	auto SPIBus  = spiBus(SPIScl, SPIMosi, SPIMiso);

	// MFRC522
	auto SPISSMFRC522 	= hwlib::target::pin_out(hwlib::target::pins::d10);
	auto MFRC522Reset 	= hwlib::target::pin_out(hwlib::target::pins::d9);
	MFRC522 rfidReader	= MFRC522(SPIBus, SPISSMFRC522, MFRC522Reset);

	// wait for the terminal to start on the PC side
	hwlib::wait_ms(1000);

	rfidReader.test();
}
