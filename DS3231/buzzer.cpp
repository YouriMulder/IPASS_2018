#include "buzzer.hpp"

#include "hwlib-wait.hpp"

buzzer::buzzer(hwlib::pin_out& output):
	output(output)
{}

void buzzer::toggle(bool state) {
	output.set(state);
}

void buzzer::turnOn() {
	toggle(1);
}

void buzzer::turnOff() {
	toggle(0);
}

void buzzer::singleSound(int delay) {
	toggle(1);
	hwlib::wait_ms(delay);
	toggle(0);
	hwlib::wait_ms(delay);
}

void buzzer::moreSounds(int amount, int delay) {
	for(int i = 0; i < amount; i++) {
		singleSound(delay);
	}
}

void buzzer::alarmEnabled() {
	moreSounds(2, 150);
}

void buzzer::alarmDisabled() {
	moreSounds(2, 100);
	moreSounds(3, 50);
}
