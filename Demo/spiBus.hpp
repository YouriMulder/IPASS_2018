#ifndef SPIBUS_HPP
#define SPIBUS_HPP

#include "hwlib.hpp"

/// @brief
///	Basic SPI functions like write and read a register.
/// @details
/// This class is a wrapper around the hwlib::spi_bus_bit_banged_sclk_mosi_miso (wouter@voti.nl 2017).
/// It contains some basic SPI functions for easy access of the used chip.
/// @warning
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
class spiBus : public hwlib::spi_bus_bit_banged_sclk_mosi_miso {
private:
	/// @brief
	/// This mask should be used before sending the register byte WHEN READING.
	/// @details
	/// This mask will always set the MSB to HIGH/1.
	/// The MSB has to be high to read from a SPI chip.
	/// Setting the same bit to a LOW/0 means it will be writing to a SPI chip.
	/// @warning
	/// Always use the #REGISTER_MASK before sending the register byte(first byte).
	const uint8_t READ_MASK 	= 0x80; // 1000 0000

	/// @brief
	/// This mask should be used before sending the register byte when reading or writing.
	/// @details
	/// This mask will always set the MSB to LOW/0
	/// and will always set the LSB to LOW/0.
	/// The MSB has to be LOW to read from a SPI chip
	/// and the LSB must always be low because it's not used by the chip
	/// All the other bits represent the register address you want to communicate with.
	/// You must always use this mask before sending the register byte(first byte).
	const uint8_t REGISTER_MASK	= 0x7E; // 0111 1110
public:

	/// @brief This is a constructor for the SpiBus class.
	/// @param scl the Serial Clock Line.
	/// @param mosi the Master Output Slave Input. data from master -> slave.
	/// @param miso the Master Input Slave Output. data from slave -> master.
	spiBus(hwlib::pin_out& scl, hwlib::pin_out& mosi, hwlib::pin_in& miso);
private:
	/// @brief this function will create a read byte using a specific register.
	/// @param chipRegAddress the register address you want to get the read chip register byte of.
	/// @return A uint8_t which contains the read register byte.
	/// @details
	/// The read register byte is the chipRegAddress shifted one bit to the left and
	/// the #REGISTER_MASK and #READ_MASK operated on it.
	uint8_t getReadByte(const uint8_t chipRegAddress);

	/// @brief this function will create a write byte using a specific register.
	/// @param chipRegAddress the register address you want to get the write chip register byte of.
	/// @return A uint8_t which contains the write register byte.
	/// @details
	/// The write register byte is the chipRegAddress shifted one bit to the left and
	/// the #REGISTER_MASK operated on it.
	uint8_t getWriteByte(const uint8_t chipRegAddress);
public:
	/// @brief Get only one byte from a specific register.
	/// @param chipRegAddress the register you want to get the byte of.
	/// @param slaveSelect the pin the slave select of the slave you want to read from.
	/// @return A uint8_t which contains the byte of the given register.
	/// @details
	/// This method sends one bytes to the slave over the mosi.
	/// The first byte is the read register byte created by #getReadByte.
	/// After sending the byte the miso will receive the byte of the chipRegAddress.
	/// The data is send and received
	/// by hwlib::spi_bus_bit_banged_sclk_mosi_miso.write_and_read() (wouter@voti.nl 2017)
	uint8_t getByteFromRegister(const uint8_t chipRegAddress,
	                            hwlib::pin_out& slaveSelect);

	/// @brief Get multiple byte from a specific register.
	/// @param chipRegAddress the register you want the bytes from.
	/// @param data[] a pointer to an array where the bytes will be stored in.
	/// @param amountOfBytes the amount of bytes you want to get.
	/// @param slaveSelect the pin the slave select of the slave you want to read from.
	/// @details
	/// First this function creates a new array to store the retreived data in.
	/// This array will be one step bigger than the amountOfBytes you want to retreive.
	/// After creating the array a read byte using the chipRegAddress and #getReadByte
	/// The array will be filled with this read byte.
	/// After using hwlib::spi_bus_bit_banged_sclk_mosi_miso.write_and_read() (wouter@voti.nl 2017)
	/// It will fill your given array with the retreived data.
	/// @warning The size of the array must at least be the amountOfBytes!
	/// @warning The given chipRegAddress will read multiple times.
	/// Some registers will be empty after reading. READ THE DATASHEET BEFORE USING!
	void getBytesFromRegister(const uint8_t chipRegAddress, uint8_t data[],
	                          const uint8_t amountOfBytes, hwlib::pin_out& slaveSelect);

	/// @brief Set a byte into a specific register.
	/// @param chipRegAddress the register you want the byte of.
	/// @param byte the byte you want to set into the chipRegAddress.
	/// @param slaveSelect the pin the slave select of the slave you want to write to.
	/// @details
	/// A array will be created and a write register byte will be set to the first index.
	/// The write register byte will be generated using #getWriteByte.
	/// The second index of the array will be the byte you want to sent.
	/// The bytes will be send using hwlib::spi_bus_bit_banged_sclk_mosi_miso.write_and_read() (wouter@voti.nl 2017)
	/// @warning The value in the register will be overridden.
	void setByteInRegister(const uint8_t chipRegAddress, uint8_t byte,
	                       hwlib::pin_out& slaveSelect);

	/// @brief Set multiple bytes starting from a specific register.
	/// @param chipRegAddress the register you want start getting the bytes from.
	/// @param data[] a pointer to an array where the bytes you want to send are stored.
	/// @param amountOfBytes the amount of bytes you want to set.
	/// @param slaveSelect the pin the slave select of the slave you want to write to.
	/// @details
	/// First a new array will be created one size bigger than amountOfBytes.
	/// The first byte will be the register write byte generated by #getWriteByte.
	/// The rest of the array will be filled with the data in the newBytes array.
	/// After setting up the array it will be send to the chip using
	/// hwlib::spi_bus_bit_banged_sclk_mosi_miso.write_and_read() (wouter@voti.nl 2017).
	/// @warning The size of newBytes[] should be amountOfBytes.
	void setBytesInRegister(const uint8_t chipRegAddress, uint8_t newBytes[],
	                        const uint8_t amountOfBytes, hwlib::pin_out& slaveSelect);
};

#endif // SPIBUS_HPP
