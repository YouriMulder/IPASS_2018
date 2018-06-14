#include "hwlib.hpp"
#include "DS3231.hpp"
#include "bitParser.hpp"
#include "i2cBus.hpp"
#include "spiBus.hpp"
#include "MFRC522.hpp"

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

	auto SPISSMFRC522	= hwlib::target::pin_out(hwlib::target::pins::d10);
	auto MFRC522Reset 	= hwlib::target::pin_out(hwlib::target::pins::d9);

	auto rfid = MFRC522(SPIBus, SPISSMFRC522, MFRC522Reset);
	// DS3231 realTimeClock(I2CBus, 0x68);
	//
	// realTimeClock.setCurrentSeconds(0); // 0 - 59
	// realTimeClock.setCurrentMinutes(21); // 0 - 59
	// realTimeClock.setCurrentHours(17);
	// realTimeClock.setCurrentDay(5);
	// realTimeClock.setCurrentDate(1);
	// realTimeClock.setCurrentMonth(6);
	// realTimeClock.setCurrentYear(18);
	// timestamp ts;

	for(;;) {
		// realTimeClock.getCurrentTimestamp(ts);
		// hwlib::cout << ts << "\n";
		// hwlib::cout << "century: " << realTimeClock.getCurrentCenturyBit() << "\n";
		// hwlib::cout << "Temperature: " << realTimeClock.getCurrentTemperatureCelsius() << "\n";
		// hwlib::cout << "Temperature: " << realTimeClock.getCurrentTemperatureFahrenheit() << "\n\n";
		//
		// hwlib::cout << "Alarm one seconds: " << (unsigned)realTimeClock.getAlarmDayDate(1) << "\n\n";
		// realTimeClock.update();
		//hwlib::cout << (unsigned) rfid.getVersion() << "\n";

		hwlib::cout << rfid.isCardPresented() << "\n";
		hwlib::wait_ms(1000);
	}
}
