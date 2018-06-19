#ifndef ALARM_HPP
#define ALARM_HPP

#include "realTimeClock.hpp"
#include "rfid.hpp"
#include "hwlib.hpp"

class alarm {
private:
	realTimeClock& rtc;
	rfid& rfidReader;

public:
	alarm(realTimeClock& rtc, rfid& rfidReader);

public:
	void test() {
		if(rfidReader.isCardInRange()) {
			uint8_t UID[4] = {0};
			hwlib::cout << "status: " << rfidReader.getCardUID(UID) << "\n";
			for(auto d : UID) {
				hwlib::cout << (unsigned)d << " , ";
			}
			hwlib::cout << "\n";
		}
		hwlib::wait_ms(1000);
	}

};

#endif // ALARM_HPP
