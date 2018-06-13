#include "MFRC522.hpp"

#include "bitParser.hpp"

MFRC522::MFRC522(spiBus& SPIBus,
    hwlib::pin_out& slaveSelect,
    hwlib::pin_out& reset):
        SPIBus(SPIBus), slaveSelect(slaveSelect), reset(reset)
{
    hardReset();
}

// 8.8 reset has to be low for 100 nanoseconds. I aint got nanoseconds so I do it for 1 microseconds
// Oscilator startuptime is unknown(defined by the crystal). The Internal delay is 37.74 microseconds
// We use 1 ms.
void MFRC522::hardReset() {
    reset.set(0);
    hwlib::wait_us(1);
    reset.set(1);
    hwlib::wait_ms(1);
    while(readRegister(CommandReg) & (1<<4)) {
        hwlib::cout <<"HEYT" ;
    }
}

uint8_t MFRC522::readRegister(REG registerAddress) {
    return SPIBus.getByteFromRegister((uint8_t)registerAddress, slaveSelect);
}

void MFRC522::writeRegister(REG registerAddress, uint8_t byte) {
    SPIBus.setByteInRegister((uint8_t)registerAddress, byte, slaveSelect);
}

void MFRC522::setMaskInRegister(REG registerAddress, uint8_t mask) {
    uint8_t currentByte = readRegister(registerAddress);
    writeRegister(registerAddress, currentByte | mask);
}

uint8_t MFRC522::getVersion() {
    return readRegister(REG::VersionReg) & 0x0F;
}
