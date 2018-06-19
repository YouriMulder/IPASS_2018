#include "alarm.hpp"

alarm::alarm(realTimeClock& rtc, rfid& rfidReader):
	rtc(rtc), rfidReader(rfidReader)
{}
