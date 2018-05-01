#include "i2cbus.hpp"

i2cbus::i2cbus(auto scl, auto sda):
	scl(scl), sda(sda) {
	scl.set(HIGH);
	sda.set(HIGH);
}
