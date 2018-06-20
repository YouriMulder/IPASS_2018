#ifndef ALARM_HPP
#define ALARM_HPP

#include "realTimeClock.hpp"
#include "rfid.hpp"
#include "motionSensor.hpp"
#include "hwlib.hpp"
#include "personalData.hpp"

class alarm {
private:
	// Hardware
	rfid& rfidReader;
	motionSensor& motionDetector;
	realTimeClock& rtc;

	enum ACCESS_LEVEL : uint8_t {
		Normal = 1,
		FullControl
	};

	// Alarm users
	personalData youri = {"Youri", FullControl, {154, 45, 198, 89, 40}};
	personalData hank = {"Hank", Normal, {0,0,0,0,0}};

	// STATIC WORKAROUND
	// THE VARIABLE ABOVE SHOULD BE THE SAME AS THE ARRAY SIZES
	const uint8_t UIDSize = 5;
	uint8_t UID[5] = {0};


private:
	bool isActive;
	bool isRinging = false;

public:
	bool getIsActive();
	bool getIsRinging();
	void clearUID();
public:
	alarm(realTimeClock& rtc, rfid& rfidReader, motionSensor& motionDetector,
	      bool isActive = false);

private:
	bool toggle(bool newValue);

public:
	bool activate();
	bool deactivate();
};

#endif // ALARM_HPP
