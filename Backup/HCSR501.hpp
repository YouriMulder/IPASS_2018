#ifndef HCSR501_HPP
#define HCSR501_HPP

#include "hwlib-pin.hpp"
#include "motionSensor.hpp"

class HCSR501 : public motionSensor {
	hwlib::pin_in& input;

public:
	HCSR501(hwlib::pin_in & input);

public:
	bool detect() override;

};

#endif // HCSR501_HPP
