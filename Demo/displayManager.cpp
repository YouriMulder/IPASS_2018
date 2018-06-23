#include "displayManager.hpp"

displayManager::displayManager(hwlib::window& display):
	display(display) {
	display.clear();
	display.flush();
	init();
}

void displayManager::init() {
	updateTemperature(0);
	updateAlarm(0);
	updateMessage("No new message");
	draw();
}

void displayManager::updateTime(timestamp& ts) {
	timeWindow << "\f \t0000" << ts;
}

void displayManager::updateTemperature(int temperature) {
	if(temperature != currentTemperature) {
		currentTemperature = temperature;
		tempPartChanged = true;
		tempWindow << "\f \t0000 TEMP\n";
		tempWindow << "\t0201" << temperature;
	}
}

void displayManager::updateAlarm(bool alarmState) {
	if(currentAlarmState != alarmState) {
		alarmPartChanged = true;
		alarmWindow << "\f";

	}

	// Still have to write it to the screen because of a possible message
	alarmWindow << "\t0000" << "Alarm: ";
	if(alarmState) {
		alarmWindow << "on";
	} else {
		alarmWindow << "off";
	}

	currentAlarmState = alarmState;
}

void displayManager::updateMessage(const char message[]) {
	alarmPartChanged = true;
	alarmWindow << "\f";
	updateAlarm(currentAlarmState);
	alarmWindow << "\t0001" << message;
}

void displayManager::draw() {
	timeWindow << hwlib::flush;
	if(tempPartChanged) {
		tempWindow << hwlib::flush;
		tempPartChanged = false;
	}
	if(alarmPartChanged) {
		alarmWindow << hwlib::flush;
		alarmPartChanged = false;
	}
}
