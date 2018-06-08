#include "MFRC522.hpp"

#include "bitParser.hpp"

MFRC522::MFRC522(spiBus& SPIBus,
    hwlib::pin_out& slaveSelect,
    hwlib::pin_out& reset):
        SPIBus(SPIBus), slaveSelect(slaveSelect), reset(reset)
{}

uint8_t MFRC522::readRegister(uint8_t registerAddress) {
    return SPIBus.getByteFromRegister(registerAddress, slaveSelect);
}

void MFRC522::writeRegister(uint8_t registerAddress, uint8_t byte) {
    SPIBus.setByteInRegister(registerAddress, byte, slaveSelect);
}

void MFRC522::setBitsInRegister(uint8_t registerAddress, uint8_t mask) {
    uint8_t currentByte = readRegister(registerAddress);
    writeRegister(registerAddress, currentByte | mask);
}


uint8_t MFRC522::getVersion() {
    return readRegister(REG_VERSION) & 0x0F;
}
