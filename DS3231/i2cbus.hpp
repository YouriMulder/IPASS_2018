#ifndef I2CBUS_HPP
#define I2CBUS_HPP

#include "hwlib.hpp"

class i2cBus : public hwlib::i2c_bus_bit_banged_scl_sda {
public:
	i2cBus(hwlib::target::pin_oc& scl, hwlib::target::pin_oc& sda);
private:
	uint8_t currentChipAddress = 0x00;
public:
	void setCurrentChipAddress(uint8_t newChipAddress);
	uint8_t getCurrentChipAddress();
public:
	void setRegister(uint8_t chipRegAddress);
	uint8_t getByteFromRegister(uint8_t chipRegAddress);
	uint8_t getDECFromBCDRegister(uint8_t chipRegAddress);
	void setByteInRegister(uint8_t chipRegAddress, uint8_t byte);
	void setByteToBCDInRegister(uint8_t chipRegAddress, uint8_t byte);

	bool getBitFromRegister(uint8_t chipRegAddress, uint8_t bitNumber);
	void setBitInRegister(uint8_t chipRegAddress, uint8_t bitNumber);
	void clearBitInRegister(uint8_t chipRegAddress, uint8_t bitNumber);
};

#endif // I2CBUS_HPP
