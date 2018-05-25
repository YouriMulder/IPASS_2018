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

	realTimeClock.setCurrentSeconds(1);
	realTimeClock.setCurrentMinutes(2);
	realTimeClock.setCurrentHours(3);
	realTimeClock.setCurrentDay(4);
	realTimeClock.setCurrentDate(5);
	realTimeClock.setCurrentYear(2);


	for(;;) {

		hwlib::cout << "Sec: " << (unsigned int)realTimeClock.getCurrentSeconds() << "\n";
		hwlib::cout << "Min: " << (unsigned int)realTimeClock.getCurrentMinutes() << "\n";
		hwlib::cout << "Hrs: " << (unsigned int)realTimeClock.getCurrentHours() << "\n";
		hwlib::cout << "Day: " << (unsigned int)realTimeClock.getCurrentDay() << "\n";
		hwlib::cout << "Date: " << (unsigned int)realTimeClock.getCurrentDate() << "\n";
		hwlib::cout << "Month: " << (unsigned int)realTimeClock.getCurrentMonth() << "\n";
		hwlib::cout << "Year: " << (unsigned int)realTimeClock.getCurrentYear() << "\n";
		hwlib::cout << "Temperature: " << realTimeClock.getCurrentTemperatureCelsius() << "\n\n";
		hwlib::wait_ms(2000);
	}
}
