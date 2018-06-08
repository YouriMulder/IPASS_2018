#ifndef MFRC522_HPP
#define MFRC522_HPP

#include "hwlib.hpp"
#include "spiBus.hpp"

class MFRC522 {
private:
    const uint8_t REG_VERSION = 0x37;

private:
    spiBus& SPIBus;
    hwlib::pin_out& slaveSelect;
    hwlib::pin_out& reset;

public:
    MFRC522(spiBus& SPIBus,
        hwlib::pin_out& slaveSelect,
        hwlib::pin_out& reset);

public:
    uint8_t readRegister(uint8_t registerAddress);
    void writeRegister(uint8_t registerAddress, uint8_t byte);
    void setBitsInRegister(uint8_t registerAddress, uint8_t mask);
public:

    uint8_t getVersion();

};

#endif // MFRC522_HPP
