#ifndef MFRC522_HPP
#define MFRC522_HPP

#include "hwlib.hpp"
#include "spiBus.hpp"
#include "rfid.hpp"

/// @brief
///	This class is used to communicate with the MFRC522 chip.
/// @details
/// This is a basic library for the MF522 chip.
/// Using the pure virtual class @ref rfid.
/// Execute the tests when you're not sure the chip is connected correctly.
/// @warning
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
class MFRC522 : public rfid {
private:
	spiBus& SPIBus;
	hwlib::pin_out& slaveSelect;
	hwlib::pin_out& reset;

public:
	/// @brief All the internal register used in the MFRC522 chip
	/// @details
	/// The enums contains all the reigsters in the MFRC522 chip.
	/// For more information about all the registers you should check the datasheet.
	/// @see
	/// <a href="https://www.nxp.com/docs/en/data-sheet/MFRC522.pdf">MFRC522 datasheet page 36</a>
	enum REG : uint8_t {
		// COMMAND AND STATUS REGISTERS
		// --------------------------------
		RESERVED1     	= 0x00,
		CommandReg,				///< @brief Starts/stops command execution <br>
		ComIEnReg,              ///< @brief Enable/disable interrupt request control bits
		DivIEnReg,              ///< @brief Enable/disable interrupt request control bits
		ComIrqReg,              ///< @brief interrupt request bits
		DivIrqReg,              ///< @brief interrupt request bits
		ErrorReg,               ///< @brief Error bits, error status of last command
		Status1Reg,             ///< @brief Communication status bits
		Status2Reg,             ///< @brief Receiver and transmitter status bits
		FIFODataReg,            ///< @brief Input/output of 64 uint8_t FIFO buffer
		FIFOLevelReg,           ///< @brief Number of uint8_t stored in the FIFO buffer
		WaterLevelReg,          ///< @brief Level for FIFO underflow and overflow warning
		ControlReg,             ///< @brief Miscellaneous control register
		BitFramingReg,          ///< @brief Adjustments for bit-oriented frames
		CollReg,                ///< @brief Bit position of the first bit-collision detected of RF interface
		RESERVED2,

		// COMMAND REGISTERS
		// --------------------------------
		RESERVED3,
		ModeReg, 				///< @brief Defines general modes for transmitting and receiving
		TxModeReg,              ///< @brief Defines transmission data rate and framing
		RxModeReg,              ///< @brief Defines reception data rate and framing
		TxControlReg,           ///< @brief Controls the logical behaviour of the antenna driver pins TX1/2
		TxASKReg,               ///< @brief Controls the setting of the transmission modulation
		TxSelReg,               ///< @brief Selects internal sources for the antenna driver
		RxSelReg,               ///< @brief Selects interal reciever settings
		rxThresholdReg,         ///< @brief Selects thresholds for the bit decoder
		DemodReg,               ///< @brief Defines demodulator settings
		RESERVED4,
		RESERVED5,
		MfTxReg, 				///< @brief Controls some MIFARE communication transmit parameters
		MfRxReg,                ///< @brief Controls some MIFARE communication receive parameters
		RESERVED6,
		SerialSpeedReg, 		///< @brief Selects the speed of the serial UART interface

		//  CONFIGURATION REGISTERS
		// --------------------------------
		RESERVED7,
		CRCResult1Reg, 			///< @brief Shows the MSB and LSB values of the CRC calculation
		CRCResult2Reg,          ///< @brief Shows the MSB and LSB values of the CRC calculation
		RESERVED8,
		ModWidthReg, 			///< @brief Control the ModWidth setting
		RESERVED9,
		RFCfgReg, 				///< @brief Configures the receiver gain
		GsNReg,                 ///< @brief Selects the conductance of the antenna driver pins tx1/2
		CWGsPReg,               ///< @brief Defines the conductance of the p-driver output during periods of no modulation
		ModGsPReg,              ///< @brief Defines the conductance of the p-driver output during periods of modulation
		TModeReg,               ///< @brief Defines settings for the internal timer
		TPrescalerReg,          ///< @brief Defines settings for the internal timer
		TReloadReg1,            ///< @brief Defines the 16-bit timer reload value
		TReloadReg2,           	///< @brief Defines the 16-bit timer reload value
		TCounterValReg1,        ///< @brief Shows the 16-bit times value
		TCounterValReg2,		///< @brief Shows the 16-bit times value

		//  TEST REGISTERS
		// --------------------------------
		RESERVED10,
		TestSel1Reg, 			///< @brief General test signal configuration
		TestSel2Reg,            ///< @brief General test signal configuration and PRBS control
		TestPinEnReg,           ///< @brief Enables pin output driver on pins D1-7
		TestPinValueReg,        ///< @brief Defines the values for D1-7 when it is used as an I/O bus
		TestBusReg,             ///< @brief Shows the status of the interal test bus
		AutoTestReg,            ///< @brief Controls the digital self test
		VersionReg,             ///< @brief Shows the software version
		AnalogTestReg,          ///< @brief Controls the pins AUX1/2
		TestDAC1Reg,            ///< @brief Defines the test value for TestDAC1
		TestDAC2Reg,            ///< @brief Defines the test value for TestDAC2
		TestADCReg              ///< @briefShows the value of ADC I and Q channels
		/* RESERVED     = 0x3C,*/
		/* RESERVED     = 0x3D,*/
		/* RESERVED     = 0x3E,*/
		/* RESERVED     = 0x3F,*/
	};

	/// @brief The possible commands the MFRC522 has.
	/// @details
	/// Before using these commands you should have some basic knowledge of what they do.
	/// Check the datasheet before using!
	/// @see
	/// <a href="https://www.nxp.com/docs/en/data-sheet/MFRC522.pdf">MFRC522 datasheet page 70</a>
	/// @warning Check the datasheet before using!
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


	/// @brief All the MIFARE Classic EV1 with 1K commands.
	/// @details
	/// Most of the commands are MIFARE Classic only. But some are defined in the ISO/IEC 14443 Type A.
	/// So some command might be used for more card like the request and wake-up command.
	/// For more information about the MIFARE command take a look at the datasheet.
	/// Most MIFARE commands require authentication!
	/// <a href="http://www.orangetags.com/wp-content/downloads/datasheet/NXP/Mifare%20EV1%201K.pdf">MIFARE datsheet page 13</a>
	/// @warning some commands override the data on the cards! WATCH OUT!
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

	/// @brief All the communication status values.
	/// @details
	/// OkStatus is the best status you can have! Everything went fine!
	/// TimeOutStatus happens when the timer is down to 0
	/// after for example transmitting the bytes to the card. <br><br>
	/// NoRoom occurs when the passed array is smaller than
	/// the amount of bytes received in the #FIFODataReg. (check using #FIFOLevelReg) <br><br>
	/// After for example transceiving the MFRC52 does serveral checks.
	/// The results are stored in the #errorReg.
	/// Any status ending with Err is an Error!
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
		// MIFARE UID last byte (XOR of all the previous UID values)
		BCCErr
	};

	/// @brief The maximum amount of bytes the FIFO can store.
	const uint8_t FIFOAmountOfBytes = 64;

	/// @brief The data that will be in the FIFO
	/// after executing the selfTest on a MFRC522 version 1.
	const uint8_t selfTestFIFOBufferV1[64] {
		0x00, 0xC6, 0x37, 0xD5, 0x32, 0xB7, 0x57, 0x5C,
		0xC2, 0xD8, 0x7C, 0x4D, 0xD9, 0x70, 0xC7, 0x73,
		0x10, 0xE6, 0xD2, 0xAA, 0x5E, 0xA1, 0x3E, 0x5A,
		0x14, 0xAF, 0x30, 0x61, 0xC9, 0x70, 0xDB, 0x2E,
		0x64, 0x22, 0x72, 0xB5, 0xBD, 0x65, 0xF4, 0xEC,
		0x22, 0xBC, 0xD3, 0x72, 0x35, 0xCD, 0xAA, 0x41,
		0x1F, 0xA7, 0xF3, 0x53, 0x14, 0xDE, 0x7E, 0x02,
		0xD9, 0x0F, 0xB5, 0x5E, 0x25, 0x1D, 0x29, 0x79
	};

	/// @brief The data that will be in the FIFO
	/// after executing the selfTest on a MFRC522 version 2.
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
	/// @brief
	/// MFRC522 class constructor.
	/// @param SPIBus the spi bus that we need to use to communicate with the chip @ref spiBus.hpp.
	/// @param slaveSelect the pin out we need to use to select this chip. hwlib::pin_out (wouter@voti.nl) 2017.
	/// @param reset the pin out that is used to reset the MFRC522 chip #hardReset.
	/// @param init whether you want to initilize when creating the MFRC522 object.
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
	void resetAntennas() override;
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
	uint8_t checkForErrors();
	uint8_t communicate(COMMAND command, uint8_t transmitData[],
	                    int transmitLength, uint8_t receivedData[],
	                    int & receivedLength);
public:
	bool isCardInRange() override;
	bool isCardInRangeCheck() override;
	uint8_t getCardUID(uint8_t UID[5]) override;
	bool getCardUIDSimple(uint8_t UID[5]) override;
	void waitForCardUID(uint8_t UID[5]) override;

public:
	// TEST FUNCTIONS
	uint8_t getVersion() override;
	bool selfTest() override;

};

#endif // MFRC522_HPP
