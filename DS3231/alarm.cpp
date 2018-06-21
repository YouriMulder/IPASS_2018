#include "alarm.hpp"

alarm::alarm(realTimeClock& rtc, rfid& rfidReader, motionSensor& motionDetector, buzzer& horn,
             bool isActive):
	rtc(rtc), rfidReader(rfidReader), motionDetector(motionDetector), horn(horn), isActive(isActive)
{}


bool alarm::getIsActive() {
	return isActive;
}

bool alarm::getIsRinging() {
	return isRinging;
}

bool alarm::isMember(personalData& member, uint8_t UID[]) {
	return rfidReader.isUIDEqual(member.UID, UID, UIDSize);
}

bool alarm::checkAllMembers(personalData& foundMember, uint8_t UID[]) {
	for(unsigned int i = 0; i < amountOfMembers; i++) {
		personalData currentMember = *members[i];
		if(isMember(currentMember, UID)) {
			foundMember = currentMember;
			return true;
		}
	}
	return false;
}

// Turn alarm on and off
bool alarm::toggle(bool newValue) {
	if(isActive == newValue) {
		return false;
	}

	uint8_t UID[UIDSize] = {0};
	if(rfidReader.getCardUIDSimple(UID)) {
		personalData foundMember;
		if(checkAllMembers(foundMember, UID)) {
			// When ringing you should've full control
			if(isRinging) {
				if(foundMember.accessLevel == FullControl) {
					horn.alarmDisabled();
					isRinging = false;
					isActive = false;
					return true;
				}

				return false;
			}

			isActive = newValue;
			if(newValue) {
				horn.alarmEnabled();
			} else {
				horn.alarmDisabled();
			}
			return true;
		} else {
			horn.singleSound(500);
			return false;
		}
	}

	return false;
}

bool alarm::activate() {
	return toggle(1);
}

bool alarm::deactivate() {
	return toggle(0);
}

void alarm::update() {
	// Turns on the horn
	if(isActive && !isRinging && motionDetector.detect()) {
		isRinging = true;
	}

	if(isRinging) {

	}

	// Turn on the horn
	if(isRinging) {
		horn.turnOn();
	} else {
		horn.turnOff();
	}

	if(rfidReader.isCardInRangeCheck()) {
		if(!isActive) {
			activate();
		} else {
			deactivate();
		}

	}
}
