#ifndef MFRC522_HPP
#define MFRC522_HPP

#include "hwlib.hpp"
#include "spiBus.hpp"
#include "rfid.hpp"

class MFRC522 : public rfid {

private:
	spiBus& SPIBus;
	hwlib::pin_out& slaveSelect;
	hwlib::pin_out& reset;

public:
	enum REG : uint8_t {

		// COMMAND AND STATUS REGISTERS
		// --------------------------------
		RESERVED1     	= 0x00,
		CommandReg,				// Starts/stops command execution
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
		RESERVED2,

		// COMMAND REGISTERS
		// --------------------------------
		RESERVED3,
		ModeReg, 				// Defines general modes for transmitting and receiving
		TxModeReg,              // Defines transmission data rate and framing
		RxModeReg,              // Defines reception data rate and framing
		TxControlReg,           // Controls the logical behaviour of the antenna driver pins TX1/2
		TxASKReg,               // Controls the setting of the transmission modulation
		TxSelReg,               // Selects internal sources for the antenna driver
		RxSelReg,               // Selects interal reciever settings
		rxThresholdReg,         // Selects thresholds for the bit decoder
		DemodReg,               // Defines demodulator settings
		RESERVED4,
		RESERVED5,
		MfTxReg, 				// Controls some MIFARE communication transmit parameters
		MfRxReg,                // Controls some MIFARE communication receive parameters
		RESERVED6,
		SerialSpeedReg, // Selects the speed of the serial UART interface

		//  CONFIGURATION REGISTERS
		// --------------------------------
		RESERVED7,
		CRCResult1Reg, 			// Shows the MSB and LSB values of the CRC calculation
		CRCResult2Reg,          // Shows the MSB and LSB values of the CRC calculation
		RESERVED8,
		ModWidthReg, 			// Control the ModWidth setting
		RESERVED9,
		RFCfgReg, 				// Configures the receiver gain
		GsNReg,                 // Selects the conductance of the antenna driver pins tx1/2
		CWGsPReg,               // Defines the conductance of the p-driver output during periods of no modulation
		ModGsPReg,              // Defines the conductance of the p-driver output during periods of modulation
		TModeReg,               // Defines settings for the internal timer
		TPrescalerReg,          // Defines settings for the internal timer
		TReloadReg1,            // Defines the 16-bit timer reload value
		TReloadReg2,           	// Defines the 16-bit timer reload value
		TCounterValReg1,        // Shows the 16-bit times value
		TCounterValReg2,		// Shows the 16-bit times value

		//  TEST REGISTERS
		// --------------------------------
		RESERVED10,
		TestSel1Reg, 			// General test signal configuration
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


	enum COMMAND : uint8_t {
		Idle        = 0x00,
		Mem,
		Generate_RandomID,
		CalcCRC,
		NoCmdChange	= 0x07,
		Receive,
		Transceive	= 0x0C,
		/* RESERVED = 0x0D, */
		MFAuthent   = 0x0E,
		SoftReset
	};


	// http://www.orangetags.com/wp-content/downloads/datasheet/NXP/Mifare%20EV1%201K.pdf
	// Table 9
	enum MIFARE_COMMAND : uint8_t {
		RequestCommand 			= 0x26,
		WakeUpCommand 			= 0x52,
		CL1Command 				= 0x93,
		CL2Command 				= 0x95,
		AnticollisionCommand 	= 0x20,
		SelectCommand 			= 0x70,
		HaltPart1Command		= 0x50,
		HaltPart2Command		= 0x00,

		// Specific MIFARE commands (Requires authentication)
		AuthKeyACommand				= 0x60,
		AuthKeyBCommand				= 0x61,
		PersonalizeUIDUsageCommand	= 0x40,
		SetModTypeCommand			= 0x43,
		ReadCommand					= 0x30,
		WriteCommand				= 0xA0,
		DecrementCommand			= 0xC0,
		IncrementCommand			= 0xC1,
		RestoreCommand				= 0xC2,
		TransferCommand				= 0xB0
	};


	enum COMMUNICATION_STATUS : uint8_t {
		OkStatus,		// Everything went as planned
		TimeOutStatus,	// No card found in the given time span.
		NoRoom,			// Not big enough received array to store all the data
		// ERRORS
		ProtocolErr,
		ParityErr,
		CRCErr,
		CollErr,
		BufferOvfl,
		TempErr,
		WrErr,
		BCCErr
	};

	// Self test variables
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

public:
	MFRC522(spiBus& SPIBus,
	        hwlib::pin_out& slaveSelect,
	        hwlib::pin_out& reset, bool init = true);

public:
	void initialize() override;
protected:
	void waitTillStarted() override;
public:
	void hardReset() override;
	void softReset() override;
protected:
	// REGISTER FUNCTIONS
	uint8_t readRegister(REG registerAddress);
	void readRegister(REG registerAddress, uint8_t read[], uint8_t amountOfBytes);
	void writeRegister(REG registerAddress, uint8_t newByte);
	void writeRegister(REG registerAddress, uint8_t newBytes[], int amountOfBytes);
	void setMaskInRegister(REG registerAddress, uint8_t mask);
	void clearMaskInRegister(REG registerAddress, uint8_t mask);

private:
	void clearFIFOBuffer(const uint8_t amountOfBytes = 64);
	void clearInternalBuffer();

protected:
	void setAntennas(bool state);
	void calculateCRC(uint8_t *data, int len, uint8_t *result);
	uint8_t checkForErrors();
	uint8_t communicate(COMMAND command, uint8_t transmitData[],
	                    int transmitLength, uint8_t receivedData[],
	                    int & receivedLength);
public:
	bool isCardInRange() override;
	uint8_t getCardUID(uint8_t UID[5]) override;
	bool getCardUIDSimple(uint8_t UID[5]) override;
	void waitForCardUID(uint8_t UID[5]) override;

public:
	// TEST FUNCTIONS
	uint8_t getVersion() override;
	bool selfTest() override;

};

#endif // MFRC522_HPP
