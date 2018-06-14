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
	enum REG : uint8_t {

		// COMMAND AND STATUS REGISTERS
		// --------------------------------
		/* RESERVED     = 0x00,*/
		CommandReg      = 0x01, // Starts/stops command execution
		ComIEnReg,              // Enable/disable interrupt request control bits
		DivIEnReg,              // Enable/disable interrupt request control bits
		ComIrqReg,              // interrupt request bits
		DivIrqReg,              // interrupt request bits
		ErrorReg,               // Error bits, error status of last command
		Status1Reg,             // Communication status bits
		Status2Reg,             // Receiver and transmitter status bits
		FIFODataReg,            // Input/output of 64 uint8_t FIFO buffer
		FIFOLevelReg,           // Number of uint8_t stored in the FIFO buffer
		WaterLevelReg,          // Level for FIFO underflow and overflow warning
		ControlReg,             // Miscellaneous control register
		BitFramingReg,          // Adjustments for bit-oriented frames
		CollReg,                // Bit position of the first bit-collision detected of RF interface
		/* RESERVED     = 0x0F,*/

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
		TPrescalerReg,          // Defines settings for the internal timer
		TReloadReg1,            // Defines the 16-bit timer reload value
		TReloadReg2,           // Defines the 16-bit timer reload value
		TCounterValReg,         // Shows the 16-bit times value

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


	enum COMMANDS : uint8_t {
		Idle        = 0x00,
		Mem,
		Generate_RandomID,
		CalcCRC,
		NoCmdChange,
		Receive,
		Transceive,
		/* RESERVED = 0x0D, */
		MFAuthent   = 0x0E,
		SoftReset
	};

	const uint8_t FIFOAmountOfBytes = 64;

	const uint8_t selfTestFIFOBufferV1[64] = {
		0x00, 0xC6, 0x37, 0xD5, 0x32, 0xB7, 0x57, 0x5C,
		0xC2, 0xD8, 0x7C, 0x4D, 0xD9, 0x70, 0xC7, 0x73,
		0x10, 0xE6, 0xD2, 0xAA, 0x5E, 0xA1, 0x3E, 0x5A,
		0x14, 0xAF, 0x30, 0x61, 0xC9, 0x70, 0xDB, 0x2E,
		0x64, 0x22, 0x72, 0xB5, 0xBD, 0x65, 0xF4, 0xEC,
		0x22, 0xBC, 0xD3, 0x72, 0x35, 0xCD, 0xAA, 0x41,
		0x1F, 0xA7, 0xF3, 0x53, 0x14, 0xDE, 0x7E, 0x02,
		0xD9, 0x0F, 0xB5, 0x5E, 0x25, 0x1D, 0x29, 0x79
	};

	const uint8_t selfTestFIFOBufferV2[64] {
		0x00, 0xEB, 0x66, 0xBA, 0x57, 0xBF, 0x23, 0x95,
		0xD0, 0xE3, 0x0D, 0x3D, 0x27, 0x89, 0x5C, 0xDE,
		0x9D, 0x3B, 0xA7, 0x00, 0x21, 0x5B, 0x89, 0x82,
		0x51, 0x3A, 0xEB, 0x02, 0x0C, 0xA5, 0x00, 0x49,
		0x7C, 0x84, 0x4D, 0xB3, 0xCC, 0xD2, 0x1B, 0x81,
		0x5D, 0x48, 0x76, 0xD5, 0x71, 0x61, 0x21, 0xA9,
		0x86, 0x96, 0x83, 0x38, 0xCF, 0x9D, 0x5B, 0x6D,
		0xDC, 0x15, 0xBA, 0x3E, 0x7D, 0x95, 0x3B, 0x2F
	};

	enum StatusCode : uint8_t {
		STATUS_OK				,	// Success
		STATUS_ERROR			,	// Error in communication
		STATUS_COLLISION		,	// Collission detected
		STATUS_TIMEOUT			,	// Timeout in communication.
		STATUS_NO_ROOM			,	// A buffer is not big enough.
		STATUS_INTERNAL_ERROR	,	// Internal error in the code. Should not happen ;-)
		STATUS_INVALID			,	// Invalid argument.
		STATUS_CRC_WRONG		,	// The CRC_A does not match
		STATUS_MIFARE_NACK		= 0xff	// A MIFARE PICC responded with NAK.
	};

	//request checks
	const uint8_t MI_OK = 0;///Everything is ok return value
	const uint8_t MI_NOTAGERR = 1;///Incorrect data error return value
	const uint8_t MI_ERR = 2;///Error return value

public:
	MFRC522(spiBus& SPIBus,
	        hwlib::pin_out& slaveSelect,
	        hwlib::pin_out& reset);

private:
	void waitTillStarted();
public:
	void hardReset();
	void softReset();
public:
	// REGISTER FUNCTIONS
	uint8_t readRegister(REG registerAddress);
	void readRegister(REG registerAddress, uint8_t read[], uint8_t amountOfBytes);
	void writeRegister(REG registerAddress, uint8_t newByte);
	void writeRegister(REG registerAddress, uint8_t newBytes[], int amountOfBytes);
	void setMaskInRegister(REG registerAddress, uint8_t mask);
	void clearMaskInRegister(REG registerAddress, uint8_t mask);
public:
	void setAntennas(bool state);
	bool isCardPresented();

private:
	void clearFIFOBuffer(const uint8_t amountOfBytes = 64);
	void clearInternalBuffer();

public:
	// TEST FUNCTIONS
	uint8_t getVersion();
	bool selfTest();

};

#endif // MFRC522_HPP
