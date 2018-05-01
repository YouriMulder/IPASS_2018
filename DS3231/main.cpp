#include "hwlib.hpp"
#include "DS3231.hpp"
#include "bitParser.hpp"

int main(int argc, char **argv) {

	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;

	// wait for the terminal to start on the PC side

	namespace target = hwlib::target;
	auto scl = target::pin_oc(target::pins::scl1);
	auto sda = target::pin_oc(target::pins::sda1);
	auto I2CBus = hwlib::i2c_bus_bit_banged_scl_sda(scl,sda);

	DS3231 realTimeClock(I2CBus, 0x68);
	for(;;)
		bitParser::printBytes(realTimeClock.getByteFromRegister(0x00));

}
