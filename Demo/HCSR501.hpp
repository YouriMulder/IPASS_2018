#ifndef HCSR501_HPP
#define HCSR501_HPP

#include "hwlib-pin.hpp"
#include "motionSensor.hpp"

/// @brief
///	This class is used to communicate with the HCSR501 chip.
/// @details
/// This is a basic library for the HCSR501 chip.
/// Using the pure virtual class @ref motionSensor.
/// Execute the tests when you're not sure the chip is connected correctly.
/// @warning
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
class HCSR501 : public motionSensor {
	/// @brief This is the input pin for the motion sensor data.
	/// @details Note that hwlib::pin_in is a class made by (wouter@voti.nl 2017).
	hwlib::pin_in& input;

public:
	/// @brief the constructor for the HCSR501
	/// @param input the input pin for the HCSR501 data.
	HCSR501(hwlib::pin_in & input);

public:
	bool detect() override;
};

#endif // HCSR501_HPP
