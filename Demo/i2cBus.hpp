#ifndef I2CBUS_HPP
#define I2CBUS_HPP

#include "hwlib.hpp"

/// @brief
///	Basic I2C functions like write and read a register.
/// @details
/// This class is a wrapper around the hwlib::i2c_bus_bit_banged_scl_sda (wouter@voti.nl 2017).
/// It contains some basic I2C functions for easy access of the used module.
/// @warning
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
class i2cBus : public hwlib::i2c_bus_bit_banged_scl_sda {
public:
	/// @brief
	/// Constructor for the i2cBus.
	/// @param scl Serial clock line.
	/// @param sda Serial Data line.
	i2cBus(hwlib::pin_oc& scl, hwlib::pin_oc& sda);
private:
	/// @brief
	/// This variable stores the address of the chip you want to talk with.
	/// @details
	/// Every function that communicates with a chip
	/// will send this byte first to let all the chips know
	/// we want to communicate with the chip using this address.
	/// @warning
	/// Changing #currentChipAddress means
	/// that you will be communicating with another chip from now on.
	uint8_t currentChipAddress = 0x00;
public:
	/// @brief Set #currentChipAddress to another address.
	/// @param newChipAddress This will be the new value of #currentChipAddress.
	/// @warning
	/// Changing #currentChipAddress means
	/// that you will be communicating with another chip from now on.
	void setCurrentChipAddress(uint8_t newChipAddress);

	/// @brief Returns the value of the current chip you are communicating with.
	/// @return A uint8_t containing the value of #currentChipAddress.
	uint8_t getCurrentChipAddress();
public:
	/// @brief set the interal register pointer of #currentChipAddress.
	/// @param chipRegAddress the register address you want the interal register pointer to set to.
	/// @details
	/// This function sends one byte in a array containing #chipRegAddress.
	/// This array will be sent using hwlib::i2c_bus_bit_banged_scl_sda.write (wouter@voti.nl 2017).
	/// @warning the internal register pointer value will be overridden.
	void setRegister(uint8_t chipRegAddress);

	/// @brief Get byte from a specific register address.
	/// @param chipRegAddress the register address you want the byte from.
	/// @return A uint8_t containing the byte of the give chipRegAddress.
	/// @details
	/// This method will only get one byte from the #currentChipAddress and returns it.
	/// First the internal register pointer is set using #setRegister.
	/// After that the byte is read using hwlib::i2c_bus_bit_banged_scl_sda.read (wouter@voti.nl 2017).
	uint8_t getByteFromRegister(uint8_t chipRegAddress);

	/// @brief Get a decimal value from a register containing BCD value.
	/// @param chipRegAddress the register address you want the decimal value from.
	/// @return A uint8_t containing the decimal value
	/// @details
	/// This method gets the value of the register using #getByteFromRegister.
	/// After getting the byte it uses BCDToDEC() to turn the BCD-code into a decimal value.
	/// the BCDToDEC function is located in the following file: \ref bitParser.hpp.
	uint8_t getDECFromBCDRegister(uint8_t chipRegAddress);

	/// @brief Set byte into a specific register address.
	/// @param chipRegAddress the register address you want to set the byte into.
	/// @param byte this is the byte you want te set into the register.
	/// @details
	/// This method will set a byte into the given register address(#chipRegAddress).
	/// The chip it will be communicating with is specified by #currentChipAddress.
	/// First the internal register pointer is set using #setRegister.
	/// After that the byte is written using hwlib::i2c_bus_bit_banged_scl_sda.write (wouter@voti.nl 2017).
	/// @warning the value of the register will be overridden.
	void setByteInRegister(uint8_t chipRegAddress, uint8_t byte);

	/// @brief set a decimal value into a register containing BCD value.
	/// @param chipRegAddress the register address you want to set the decimal value in.
	/// @param byte the decimal value(byte) you want to set into the register.
	/// @details
	/// This function turns the decimal byte into a BCD-coded value using
	/// the the function DECToBCD which is located the following file: \ref bitParser.hpp.
	/// After turning the decimal value into a BCD-coded byte it sends the value using #setByteInRegister.
	/// @warning The value of the register will be overridden.
	void setByteToBCDInRegister(uint8_t chipRegAddress, uint8_t byte);

	/// @brief Get bit from a specific register address.
	/// @param chipRegAddress the register address you want the bit from.
	/// @param bitNumber the bit you want to get from the register (0 = LSB, 7 = MSB).
	/// @return A boolean containing the the bit value of the give bitNumber.
	/// @details
	/// First it will get the whole byte using #getByteFromRegister.
	/// After achieving the whole byte it will bitshift to the right bit
	/// and return that specific bit.
	bool getBitFromRegister(uint8_t chipRegAddress, uint8_t bitNumber);

	/// @brief Set bit into a specific register address (This function will always set the bit to HIGH/1).
	/// @param chipRegAddress the register address where you want to set the bit.
	/// @param bitNumber the bit you want to set the value of (0 = LSB, 7 = MSB).
	/// @details
	/// First this function gets the current byte in the register.
	/// After achieving the whole byte it will set the bit given by the user(bitNumber).
	/// And last but not least it will set the manipulated byte into the register using #setByteInRegister
	/// @warning The value of the bit will be overridden.
	void setBitInRegister(uint8_t chipRegAddress, uint8_t bitNumber);

	/// @brief Clear bit of specific register address (This function will always set the bit to LOW/0).
	/// @param chipRegAddress the register address where you want to clear the bit.
	/// @param bitNumber the bit you want to clear the value of (0 = LSB, 7 = MSB).
	/// @details
	/// First this function gets the current byte in the register.
	/// After achieving the whole byte it will clear the bit given by the user(bitNumber).
	/// And last but not least it will set the manipulated byte into the register using #setByteInRegister
	/// @warning The value of the bit will be overridden.
	void clearBitInRegister(uint8_t chipRegAddress, uint8_t bitNumber);
};

#endif // I2CBUS_HPP
