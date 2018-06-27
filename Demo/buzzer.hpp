// -----------------------------------------------------------
// (C) Copyright Youri Mulder 2018.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// -----------------------------------------------------------

#ifndef BUZZER_HPP
#define BUZZER_HPP

#include "hwlib-pin.hpp"

class buzzer {
	hwlib::pin_in_out& output;
public:
	buzzer(hwlib::pin_in_out& output);

public:
	void toggle(bool state);
	void turnOn();
	void turnOff();
	void singleSound(int delay = 150);
	void moreSounds(int amount = 2, int delay = 150);
	void alarmEnabled();
	void alarmDisabled();
	void wrongSound();
};

#endif // BUZZER_HPP
