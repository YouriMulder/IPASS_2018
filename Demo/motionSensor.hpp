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
	/// @details
	/// detect whether there is anything is moving
	/// in the field of the motion sensor or not.
	/// @return A bool containing
	/// a 0 when nothing is detected
	/// and 1 when somthing is detected.
	virtual bool detect() = 0;
};

#endif // MOTIONSENSOR_HPP
