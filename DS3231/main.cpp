#include "hwlib.hpp"
#include "DS3231.hpp"
#include "bitParser.hpp"
#include "i2cBus.hpp"

int main(int argc, char **argv) {

	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;

	// wait for the terminal to start on the PC side
	hwlib::wait_ms(200);

	auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
	auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
	auto I2CBus = i2cBus(scl,sda);

	DS3231 realTimeClock(I2CBus, 0x68);

	realTimeClock.setCurrentSeconds(58); // 0 - 59
	realTimeClock.setCurrentMinutes(59); // 0 - 59
	realTimeClock.setCurrentHours(23);
	realTimeClock.setCurrentDay(7);
	realTimeClock.setCurrentDate(31);
	realTimeClock.setCurrentMonth(12);
	realTimeClock.setCurrentYear(99);
	timestamp ts;
	for(;;) {
		realTimeClock.getCurrentTimestamp(ts);
		hwlib::cout << ts << "\n";
		hwlib::cout << "century: " << realTimeClock.getCurrentCenturyBit() << "\n";
		hwlib::cout << "Temperature: " << realTimeClock.getCurrentTemperatureCelsius() << "\n";
		hwlib::cout << "Temperature: " << realTimeClock.getCurrentTemperatureFahrenheit() << "\n\n";
		realTimeClock.update();
		hwlib::wait_ms(1000);
	}
}
