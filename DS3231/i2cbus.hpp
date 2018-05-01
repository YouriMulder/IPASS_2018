#ifndef I2CBUS_HPP
#define I2CBUS_HPP

#include "hwlib-pin.hpp"
#include "hwlib-wait.hpp"

class i2cbus {
private:
	const int HIGH = 1;
	const int LOW = 0;

	hwlib::pin_oc scl;
	hwlib::pin_oc sda;



public:
	i2cbus(auto scl, auto sda);


};

#endif // I2CBUS_HPP
