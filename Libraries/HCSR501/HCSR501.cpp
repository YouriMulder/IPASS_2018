// -----------------------------------------------------------
// (C) Copyright Youri Mulder 2018.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// -----------------------------------------------------------

#include "HCSR501.hpp"
#include "hwlib.hpp"

HCSR501::HCSR501(hwlib::pin_in& input):
	input(input)
{}

bool HCSR501::detect() {
	return input.get();
}

void HCSR501::printTest(bool condition, const char testCaseMessage[]) {
	const char normalColor[] = "\x1b[37m";
	const char errorColor[] = "\x1b[31m";
	const char passedColor[] = "\x1b[32m";
	if(condition) {
		hwlib::cout << passedColor << "Test Passed: " << testCaseMessage << "\n";
	} else {
		hwlib::cout << errorColor << "Test Error: " << testCaseMessage << "\n";
	}
	hwlib::cout << normalColor;
}

void HCSR501::waitToGoOff() {
	hwlib::cout << "Wait for the motionsensor to go off\n";
	while(detect()) {
		hwlib::wait_ms(100);
	}
}

void HCSR501::test() {
	hwlib::cout << "HCSR501 test\n";
	waitToGoOff();
	hwlib::cout << "Place object in front of sensor\n";
	bool detected = false;

	for(int i = 0; i < 100; i++) {
		if(detect()) {
			detected = true;
			break;
		}
		hwlib::wait_ms(100);
	}
	printTest(detected, "detecting object");
	hwlib::cout << "End tests\n\n";
}
