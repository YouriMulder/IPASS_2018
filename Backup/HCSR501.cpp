#include "HCSR501.hpp"

HCSR501::HCSR501(hwlib::pin_in& input):
	input(input)
{}

bool HCSR501::detect() {
	return input.get();
}
