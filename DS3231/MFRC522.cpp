#include "MFRC522.hpp"

#include "bitParser.hpp"

MFRC522::MFRC522(spiBus& SPIBus,
    hwlib::pin_out& slaveSelect,
    hwlib::pin_out& reset):
        SPIBus(SPIBus), slaveSelect(slaveSelect), reset(reset)
{}

uint8_t MFRC522::readRegister(REG registerAddress) {
    return SPIBus.getByteFromRegister((uint8_t)registerAddress, slaveSelect);
}

void MFRC522::writeRegister(REG registerAddress, uint8_t byte) {
    SPIBus.setByteInRegister((uint8_t)registerAddress, byte, slaveSelect);
}

void MFRC522::setBitsInRegister(REG registerAddress, uint8_t mask) {
    uint8_t currentByte = readRegister(registerAddress);
    writeRegister(registerAddress, currentByte | mask);
}

uint8_t MFRC522::getVersion() {
    return readRegister(REG::VersionReg) & 0x0F;
}
