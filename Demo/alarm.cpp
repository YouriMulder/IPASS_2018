#include "alarm.hpp"

alarm::alarm(realTimeClock& rtc, rfid& rfidReader, motionSensor& motionDetector, buzzer& horn,
             displayManager& dManager, bool isActive):
	rtc(rtc), rfidReader(rfidReader), motionDetector(motionDetector),
	horn(horn), dManager(dManager), isActive(isActive)
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
			dManager.updateMessage("Known card");
			// When ringing you should've full control
			if(newValue) {
				return turnOn();
			}
			return turnOff(foundMember);
		}
	}
	dManager.updateMessage("Unknown card");
	horn.wrongSound();
	return false;
}

bool alarm::turnOff(personalData& member) {
	if(isRinging) {
		if(member.accessLevel == FullControl) {
			horn.alarmDisabled();
			isActive = false;
			isRinging = false;
			return true;
		}
		dManager.updateMessage("Not allowed");
		horn.wrongSound();
		return false;
	}

	horn.alarmDisabled();
	isActive = false;
	isRinging = false;
	return true;
}


bool alarm::turnOn() {
	horn.alarmEnabled();
	isActive = true;
	isRinging = false;
	dManager.updateMessage("15 sec to leave!");
	dManager.draw();

	uint8_t endSeconds = rtc.getCurrentSeconds() + 15;
	if(endSeconds > rtc.maxSeconds) {
		endSeconds -= rtc.maxSeconds;
	}
	while(rtc.getCurrentSeconds() != endSeconds) {}

	dManager.updateMessage("");

	return true;
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

	// Turn on the horn
	if(isRinging) {
		horn.turnOn();
		dManager.updateMessage("INTRUDER!");
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

	dManager.updateAlarm(isActive);
}
