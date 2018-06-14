#ifndef SPIBUS_HPP
#define SPIBUS_HPP

#include "hwlib.hpp"

class spiBus : public hwlib::spi_bus_bit_banged_sclk_mosi_miso {
private:
	const uint8_t READ_MASK 	= 0x80; // 1000 0000
	const uint8_t REGISTER_MASK	= 0x7E; // 0111 1110
public:
	spiBus(hwlib::pin_out& scl, hwlib::pin_out& mosi, hwlib::pin_in& miso);
private:
	uint8_t getReadByte(const uint8_t chipRegAddress);
	uint8_t getWriteByte(const uint8_t chipRegAddress);
public:
	uint8_t getByteFromRegister(const uint8_t chipRegAddress,
	                            hwlib::pin_out& slaveSelect);
	void getBytesFromRegister(const uint8_t chipRegAddress, uint8_t data[],
	                          const uint8_t amountOfBytes, hwlib::pin_out& slaveSelect);

	void setByteInRegister(const uint8_t chipRegAddress, uint8_t byte,
	                       hwlib::pin_out& slaveSelect);
	void setBytesInRegister(const uint8_t chipRegAddress, uint8_t newBytes[],
	                        const uint8_t amountOfBytes, hwlib::pin_out& slaveSelect);
};

#endif // SPIBUS_HPP
