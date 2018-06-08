#ifndef MFRC522_HPP
#define MFRC522_HPP

#include "hwlib.hpp"
#include "spiBus.hpp"

class MFRC522 {

private:
    spiBus& SPIBus;
    hwlib::pin_out& slaveSelect;
    hwlib::pin_out& reset;

public:
    enum REG {

    // --------------------------------
    // COMMAND AND STATUS REGISTERS
    // --------------------------------
    /* RESERVED     = 0x00,*/
    CommandReg      = 0x01, // Starts/stops command execution
    ComlEnReg,              // Enable/disable interrupt request control bits
    DivlEnReg,              // Enable/disable interrupt request control bits
    ComIrlReg,              // interrupt request bits
    DivLrqReg,              // interrupt request bits
    ErrorReg,               // Error bits, error status of last command
    Status1Reg,             // Communication status bits
    Status2Reg,             // Receiver and transmitter status bits
    FIFODataReg,            // Input/output of 64 byte FIFO buffer
    FIFOLevelReg,           // Number of byte stored in the FIFO buffer
    WaterLevelReg,          // Level for FIFO underflow and overflow warning
    ControlReg,             // Miscellaneous control register
    BitFarmingReg,          // Adjustments for bit-oriented frames
    CollReg,                // Bit position of the first bit-collision detected of RF interface
    /* RESERVED     = 0x0F,*/

    // --------------------------------
    // COMMAND REGISTERS
    // --------------------------------
    /* RESERVED     = 0x10,*/
    ModeReg         = 0x11, // Defines general modes for transmitting and receiving
    TxModeReg,              // Defines transmission data rate and framing
    RxModeReg,              // Defines reception data rate and framing
    TxControlReg,           // Controls the logical behaviour of the antenna driver pins TX1/2
    TxASKReg,               // Controls the setting of the transmission modulation
    TxSelReg,               // Selects internal sources for the antenna driver
    RxSelReg,               // Selects interal reciever settings
    rxThresholdReg,         // Selects thresholds for the bit decoder
    DemodReg,               // Defines demodulator settings
    /* RESERVED     = 0x1A,*/
    /* RESERVED     = 0x1B,*/
    MfTxReg         = 0x1C, // Controls some MIFARE communication transmit parameters
    MfRxReg,                // Controls some MIFARE communication receive parameters
    /* RESERVED     = 0x1E,*/
    SerialSpeedReg  = 0x1F, // Selects the speed of the serial UART interface

    // --------------------------------
    //  CONFIGURATION REGISTERS
    // --------------------------------
    /* RESERVED     = 0x20,*/
    CRCResult1Reg   = 0x21, // Shows the MSB and LSB values of the CRC calculation
    CRCResult2Reg,          // Shows the MSB and LSB values of the CRC calculation
    /* RESERVED     = 0x23,*/
    ModWidthReg     = 0x24, // Control the ModWidth setting
    /* RESERVED     = 0x25,*/
    RFCfgReg        = 0x26, // Configures the receiver gain
    GsNReg,                 // Selects the conductance of the antenna driver pins tx1/2
    CWGsPReg,               // Defines the conductance of the p-driver output during periods of no modulation
    ModGsPReg,              // Defines the conductance of the p-driver output during periods of modulation
    TModeReg,               // Defines settings for the internal timer
    TPrescalerReg,          // Defines the 16-bit timer reload value
    TCounterValReg,         // Shows the 16-bit times value

    // --------------------------------
    //  TEST REGISTERS
    // --------------------------------
    /* RESERVED     = 0x30,*/
    TestSel1Reg     = 0x31, // General test signal configuration
    TestSel2Reg,            // General test signal configuration and PRBS control
    TestPinEnReg,           // Enables pin output driver on pins D1-7
    TestPinValueReg,        // Defines the values for D1-7 when it is used as an I/O bus
    TestBusReg,             // Shows the status of the interal test bus
    AutoTestReg,            // Controls the digital self test
    VersionReg,             // Shows the software version
    AnalogTestReg,          // Controls the pins AUX1/2
    TestDAC1Reg,            // Defines the test value for TestDAC1
    TestDAC2Reg,            // Defines the test value for TestDAC2
    TestADCReg             // Shows the value of ADC I and Q channels
    /* RESERVED     = 0x3C,*/
    /* RESERVED     = 0x3D,*/
    /* RESERVED     = 0x3E,*/
    /* RESERVED     = 0x3F,*/
};

public:
    MFRC522(spiBus& SPIBus,
        hwlib::pin_out& slaveSelect,
        hwlib::pin_out& reset);

public:
    uint8_t readRegister(REG registerAddress);
    void writeRegister(REG registerAddress, uint8_t byte);
    void setBitsInRegister(REG registerAddress, uint8_t mask);
public:

    uint8_t getVersion();

};

#endif // MFRC522_HPP
