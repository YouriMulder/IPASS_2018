#include "hwlib.hpp"
#include "DS3231.hpp"
#include "bitParser.hpp"

int main(int argc, char **argv) {

	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;

	// wait for the terminal to start on the PC side
	hwlib::wait_ms(200);

	namespace target = hwlib::target;
	auto scl = target::pin_oc(target::pins::scl1);
	auto sda = target::pin_oc(target::pins::sda1);
	auto I2CBus = hwlib::i2c_bus_bit_banged_scl_sda(scl,sda);



	DS3231 realTimeClock(I2CBus, 0x68);

	for(;;) {
		hwlib::cout << "Sec: " << (unsigned int)realTimeClock.getCurrentSeconds() << "\n";
		hwlib::cout << "Min: " << (unsigned int)realTimeClock.getCurrentMinutes() << "\n";
		hwlib::cout << "Hrs: " << (unsigned int)realTimeClock.getCurrentHours() << "\n";
		hwlib::cout << "Day: " << (unsigned int)realTimeClock.getCurrentDay() << "\n";
		hwlib::cout << "Month: " << (unsigned int)realTimeClock.getCurrentMonth() << "\n";
		hwlib::cout << "Year: " << (unsigned int)realTimeClock.getCurrentYear() << "\n";
		hwlib::cout << "Temperature: " << realTimeClock.getCurrentTemperatureCelsius() << "\n\n";
		hwlib::wait_ms(2000);
	}
}
