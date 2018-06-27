// -----------------------------------------------------------
// (C) Copyright Youri Mulder 2018.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// -----------------------------------------------------------

#ifndef MOTIONSENSOR_HPP
#define MOTIONSENSOR_HPP

/// @brief
///	A pure virtual class for a motion sensor chip like the HCSR501.
/// @details
/// This class is a pure virtual class.
/// This means that you can access methods of the derived class when using reference or pointers.
/// This makes the code easier to expand.
/// @warning
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
class motionSensor {
public:
	/// @brief Detect if any movement is in front of the motionsensor.
	/// @details
	/// Detect whether there is anything is moving
	/// in the field of the motion sensor or not.
	/// @return A bool containing
	/// a 0 when nothing is detected
	/// and 1 when somthing is detected.
	virtual bool detect() = 0;

	/// @brief Wait for the motionSensor to go off after detecting.
	/// @warning This is a blocking call.
	/// It will block all the other functions to be called untill the motionsensors is off.
	virtual void waitToGoOff() = 0;

	/// @brief
	/// This checks if the chip is functioning correctly.
	/// Make sure you connected everything correctly before executing.
	/// @details
	/// Testing might take a while. Wait till the end test message appears.
	virtual void test() = 0;
};

#endif // MOTIONSENSOR_HPP
