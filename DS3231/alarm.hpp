#ifndef ALARM_HPP
#define ALARM_HPP

#include "realTimeClock.hpp"
#include "rfid.hpp"
#include "motionSensor.hpp"
#include "hwlib.hpp"
#include "personalData.hpp"
#include "buzzer.hpp"
#include "displayManager.hpp"

class alarm {
private:
	// Hardware
	realTimeClock& rtc;
	rfid& rfidReader;
	motionSensor& motionDetector;
	buzzer& horn;
	displayManager dManager;

	enum ACCESS_LEVEL : uint8_t {
		Normal = 1,
		FullControl
	};

	// Alarm users
	personalData youri = {"Youri", FullControl, {154, 45, 198, 89, 40}};

	uint8_t amountOfMembers = 1;
	personalData* members[10] = {&youri};

	// STATIC WORKAROUND
	// THE VARIABLE ABOVE SHOULD BE THE SAME AS THE ARRAY SIZES
	const uint8_t UIDSize = 5;
private:
	bool isActive;
	bool isRinging = false;

public:
	alarm(realTimeClock& rtc, rfid& rfidReader, motionSensor& motionDetector, buzzer& horn,
	      displayManager& dManager, bool isActive = false);

public:
	bool getIsActive();
	bool getIsRinging();
	bool isMember(personalData& member, uint8_t UID[]);
	bool checkAllMembers(personalData& foundMember, uint8_t UID[]);

private:
	bool toggle(bool newValue);
	bool turnOff(personalData & member);
	bool turnOn();

public:
	bool activate();
	bool deactivate();

	void update();
};

#endif // ALARM_HPP
