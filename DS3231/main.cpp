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
	realTimeClock.setCurrentMinutes(21); // 0 - 59
	realTimeClock.setCurrentHours(17);
	realTimeClock.setCurrentDay(5);
	realTimeClock.setCurrentDate(1);
	realTimeClock.setCurrentMonth(6);
	realTimeClock.setCurrentYear(18);
	timestamp ts;

	for(;;) {
		bitParser::printByte(realTimeClock.getAgingOffset());
		realTimeClock.getCurrentTimestamp(ts);
		hwlib::cout << ts << "\n";
		hwlib::cout << "century: " << realTimeClock.getCurrentCenturyBit() << "\n";
		hwlib::cout << "Temperature: " << realTimeClock.getCurrentTemperatureCelsius() << "\n";
		hwlib::cout << "Temperature: " << realTimeClock.getCurrentTemperatureFahrenheit() << "\n\n";

		hwlib::cout << "Alarm one seconds: " << (unsigned)realTimeClock.getAlarmDayDate(1) << "\n\n";
		realTimeClock.update();
		hwlib::wait_ms(1000);
	}
}
