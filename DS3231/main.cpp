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

	realTimeClock.setCurrentSeconds(0); // 0 - 59
	realTimeClock.setCurrentMinutes(46); // 0 - 59
	realTimeClock.setCurrentHours(8);
	realTimeClock.setCurrentDay(2);
	realTimeClock.setCurrentDate(29);
	realTimeClock.setCurrentMonth(5);
	realTimeClock.setCurrentYear(18);
	timestamp ts;


	for(;;) {
		realTimeClock.setAlarmOneSeconds(10);
		realTimeClock.getCurrentTimestamp(ts);
		hwlib::cout << ts << "\n";
		hwlib::cout << "century: " << realTimeClock.getCurrentCenturyBit() << "\n";
		hwlib::cout << "Temperature: " << realTimeClock.getCurrentTemperatureCelsius() << "\n";
		hwlib::cout << "Temperature: " << realTimeClock.getCurrentTemperatureFahrenheit() << "\n\n";

		hwlib::cout << "Alarm one seconds: " << (unsigned)realTimeClock.getAlarmOneSeconds() << "\n\n";
		realTimeClock.update();
		hwlib::wait_ms(1000);
	}
}
