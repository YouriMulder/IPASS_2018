#include "hwlib.hpp"
#include "DS3231.hpp"
#include "bitParser.hpp"
#include "i2cBus.hpp"
#include "spiBus.hpp"
#include "MFRC522.hpp"
#include "HCSR501.hpp"

#include "alarm.hpp"

int main(int argc, char **argv) {

	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;

	// wait for the terminal to start on the PC side
	hwlib::wait_ms(200);

	// I2C Bus
	auto I2CScl = hwlib::target::pin_oc(hwlib::target::pins::scl);
	auto I2CSda = hwlib::target::pin_oc(hwlib::target::pins::sda);
	auto I2CBus = i2cBus(I2CScl, I2CSda);

	// SPI bus
	auto SPIMosi 	 	= 	hwlib::target::pin_out(hwlib::target::pins::d11);
	auto SPIMiso	 	= 	hwlib::target::pin_in(hwlib::target::pins::d12);
	auto SPIScl  	 	=	hwlib::target::pin_out(hwlib::target::pins::scl1);

	auto SPIBus = spiBus(SPIScl, SPIMosi, SPIMiso);

	// MFRC522
	auto SPISSMFRC522	= hwlib::target::pin_out(hwlib::target::pins::d10);
	auto MFRC522Reset 	= hwlib::target::pin_out(hwlib::target::pins::d9);

	// PIR HCSR501
	auto HCSR501Input	= hwlib::target::pin_in(hwlib::target::pins::d2);

	auto rfidReader 	= MFRC522(SPIBus, SPISSMFRC522, MFRC522Reset);
	auto motionSensor	= HCSR501(HCSR501Input);

	DS3231 realTimeClock(I2CBus, 0x68);

	realTimeClock.setCurrentSeconds(0); // 0 - 59
	realTimeClock.setCurrentMinutes(21); // 0 - 59
	realTimeClock.setCurrentHours(17);
	realTimeClock.setCurrentDay(5);
	realTimeClock.setCurrentDate(1);
	realTimeClock.setCurrentMonth(6);
	realTimeClock.setCurrentYear(18);

	alarm theftAlarm(realTimeClock, rfidReader);
	timestamp ts;

	for(;;) {
		theftAlarm.test();
	}


	/*for(;;) {
		rtc.getCurrentTimestamp(ts);
		hwlib::cout << ts << "\n";
		hwlib::cout << "century: " << rtc.getCurrentCenturyBit() << "\n";
		hwlib::cout << "Temperature: " << rtc.getCurrentTemperatureCelsius() << "\n";
		hwlib::cout << "Temperature: " << rtc.getCurrentTemperatureFahrenheit() << "\n\n";

		hwlib::cout << "Alarm one hours: " << (unsigned)rtc.getAlarmHours(1) << "\n\n";
		rtc.update();
	}
	hwlib::cout << (unsigned) rfid.getVersion() << "\n";
	hwlib::cout << "Self Test: " << rfid.selfTest() << "\n";

	*/
//
//	for(;;) {
//		if(rfid.isCardInRange()) {
//			uint8_t UID[4] = {0};
//			hwlib::cout << "status: " << rfid.getCardUID(UID) << "\n";
//			for(auto d : UID) {
//				hwlib::cout << (unsigned)d << " , ";
//			}
//			hwlib::cout << "\n";
//		}
//		hwlib::wait_ms(1000);
//	}
//
	/*	for(;;) {
			hwlib::cout << motionSensor.getInput() << "\n";

		}*/

}
