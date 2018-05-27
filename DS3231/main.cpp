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

	hwlib::cout << time::currentCentury << "\n";
	time::increaseCentury();
	hwlib::cout << time::currentCentury << "\n";


	for(;;) {
		hwlib::cout << "Sec: " << (unsigned int)realTimeClock.getCurrentSeconds() << "\n";
		hwlib::cout << "Min: " << (unsigned int)realTimeClock.getCurrentMinutes() << "\n";
		hwlib::cout << "Hrs: " << (unsigned int)realTimeClock.getCurrentHours() << "\n";
		hwlib::cout << "Day: " << (unsigned int)realTimeClock.getCurrentDay() << "\n";
		hwlib::cout << "Date: " << (unsigned int)realTimeClock.getCurrentDate() << "\n";
		hwlib::cout << "Month: " << (unsigned int)realTimeClock.getCurrentMonth() << "\n";
		hwlib::cout << "Year: " << (unsigned int)realTimeClock.getCurrentYear() << "\n";
		hwlib::cout << "century: " << (unsigned int)realTimeClock.getCurrentCentury() << "\n";
		hwlib::cout << "Temperature: " << realTimeClock.getCurrentTemperatureCelsius() << "\n";
		hwlib::cout << "Temperature: " << realTimeClock.getCurrentTemperatureFahrenheit() << "\n\n";
		realTimeClock.update();
		hwlib::wait_ms(2000);
	}
}
