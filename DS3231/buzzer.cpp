#include "buzzer.hpp"

#include "hwlib-wait.hpp"

buzzer::buzzer(hwlib::pin_in_out& output):
	output(output) {
	output.direction_set_output();
}

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
	if(output.get()) {
		toggle(0);
		hwlib::wait_ms(200);
	}
	toggle(1);
	hwlib::wait_ms(delay);
	toggle(0);
}

void buzzer::moreSounds(int amount, int delay) {
	for(int i = 0; i < amount; i++) {
		singleSound(delay);
		hwlib::wait_ms(100);
	}
}

void buzzer::wrongSound() {
	hwlib::wait_ms(200);
	singleSound(200);
	hwlib::wait_ms(200);
}

void buzzer::alarmEnabled() {
	moreSounds(2, 150);
}

void buzzer::alarmDisabled() {
	moreSounds(2, 100);
	moreSounds(3, 50);
}
