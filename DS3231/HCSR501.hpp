#ifndef HCSR501_HPP
#define HCSR501_HPP

#include "hwlib-pin.hpp"


class HCSR501 {
	hwlib::pin_in& input;

public:
	HCSR501(hwlib::pin_in & input);

	bool getInput() {
		return input.get();
	}

};

#endif // HCSR501_HPP
