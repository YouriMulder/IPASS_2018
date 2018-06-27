// -----------------------------------------------------------
// (C) Copyright Youri Mulder 2018.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// -----------------------------------------------------------

#ifndef DISPLAYMANAGER_HPP
#define DISPLAYMANAGER_HPP

#include "hwlib.hpp"
#include "timeStamp.hpp"

class displayManager {
private:
	hwlib::window& display;
	int currentTemperature = 0;
	bool tempPartChanged = true;
	bool alarmPartChanged = true;
	bool currentAlarmState = false;

public:
	displayManager(hwlib::window& display);

private:
	hwlib::window_part timePart = hwlib::window_part(
	                                  display,
	                                  hwlib::location(0, 0),
	                                  hwlib::location(90, 32));

	hwlib::window_part  tempPart = hwlib::window_part(
	                                   display,
	                                   hwlib::location(90, 0),
	                                   hwlib::location(90, 33));



	hwlib::window_part alarmPart = hwlib::window_part(
	                                   display,
	                                   hwlib::location(0, 32),
	                                   hwlib::location(128, 32));

	hwlib::font_default_8x8 f1 = hwlib::font_default_8x8();
	hwlib::window_ostream timeWindow = hwlib::window_ostream(timePart, f1);
	hwlib::window_ostream tempWindow = hwlib::window_ostream(tempPart, f1);
	hwlib::window_ostream alarmWindow = hwlib::window_ostream(alarmPart, f1);

public:
	void init();

	void updateTime(timestamp& ts);
	void updateTemperature(int temperature);
	void updateAlarm(bool alarmState);
	void updateMessage(const char message[]);

	void draw();
};

#endif // DISPLAYMANAGER_HPP
