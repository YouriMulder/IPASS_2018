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
