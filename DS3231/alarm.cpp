#include "alarm.hpp"

alarm::alarm(realTimeClock& rtc, rfid& rfidReader, motionSensor& motionDetector,
             bool isActive):
	rtc(rtc), rfidReader(rfidReader), motionDetector(motionDetector), isActive(isActive)
{}


bool alarm::getIsActive() {
	return isActive;
}

bool alarm::getIsRinging() {
	return isRinging;
}

void alarm::clearUID() {
	for(uint8_t & digit : UID) {
		digit = 0;
	}
}

bool alarm::toggle(bool newValue) {
	if(isActive == newValue) {
		return false;
	}

	if(rfidReader.getCardUIDSimple(UID)) {
		if(rfidReader.isUIDEqual(UID, card, UIDSize)) {
			clearUID();
			isActive = newValue;
			return true;
		}
	}
	clearUID();

	return false;
}

bool alarm::activate() {
	return toggle(1);
}

bool alarm::deactivate() {
	return toggle(0);
}
