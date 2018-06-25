#include "MFRC522.hpp"

#include "bitParser.hpp"
#include "rfid.hpp"

MFRC522::MFRC522(spiBus& SPIBus,
                 hwlib::pin_out& slaveSelect,
                 hwlib::pin_out& reset, bool init):
	SPIBus(SPIBus), slaveSelect(slaveSelect), reset(reset) {
	if(init) {
		initialize();
	}
}

void MFRC522::initialize() {
	hardReset();

	writeRegister(TModeReg, 0x80);       // Timer auto start timer
	writeRegister(TxModeReg, 0); 		// Set speed to 106 kBd to be able to use some extra functionality
	writeRegister(TxModeReg, 0);		// Set speed to 106 kBd to be able to use some extra functionality

	writeRegister(TPrescalerReg, 0xA9); // 0x0A9 = 30khz timer aka 25 us
	writeRegister(TReloadReg1, 0x03);	// 25 us x 1000 = 25ms timeout
	writeRegister(TReloadReg2, 0xE8);	// 25 us x 1000 = 25ms timeout

	writeRegister(TxASKReg, 0x40);      // 100%ASK http://www.rfwireless-world.com/Terminology/10-ASK-modulation-vs-100-ASK-modulation.html 100% is used for type A which i'm using
	writeRegister(ModeReg, 0x3D);       // CRC initial value 0x6363
	setAntennas(1);						// Resetting causes the antennas to go off.
}

void MFRC522::waitTillStarted() {
	while(readRegister(CommandReg) & (1 << 4)) {}
}

// 8.8 reset has to be low for 100 nanoseconds. I aint got nanoseconds so I do it for 1 microseconds
// Oscilator startuptime is unknown(defined by the crystal).
// The Internal delay is 37.74 microseconds
// We use 1 ms.
// The first attempt to read from a register returns some weird numbers
void MFRC522::hardReset() {
	reset.set(0);
	hwlib::wait_us(1);
	reset.set(1);
	hwlib::wait_ms(1);
	waitTillStarted();
}

void MFRC522::softReset() {
	writeRegister(CommandReg, (uint8_t)SoftReset);
	hwlib::wait_ms(150);
	waitTillStarted();
}

void MFRC522::resetAntennas() {
	setAntennas(0);
	setAntennas(1);
}

uint8_t MFRC522::readRegister(REG registerAddress) {
	return SPIBus.getByteFromRegister((uint8_t)registerAddress, slaveSelect);
}

void MFRC522::readRegister(REG registerAddress, uint8_t read[],
                           uint8_t amountOfBytes) {
	SPIBus.getBytesFromRegister(static_cast<uint8_t>(registerAddress), read, amountOfBytes, slaveSelect);
}

void MFRC522::writeRegister(REG registerAddress, uint8_t newByte) {
	SPIBus.setByteInRegister(static_cast<uint8_t>(registerAddress), newByte, slaveSelect);
}

void MFRC522::writeRegister(REG registerAddress, uint8_t newBytes[],
                            int amountOfBytes) {
	SPIBus.setBytesInRegister(registerAddress, newBytes,
	                          amountOfBytes, slaveSelect);
}

void MFRC522::setMaskInRegister(REG registerAddress, uint8_t mask) {
	uint8_t currentByte = readRegister(registerAddress);
	writeRegister(registerAddress, currentByte | mask);
}

void MFRC522::clearMaskInRegister(REG registerAddress, uint8_t mask) {
	uint8_t currentByte = readRegister(registerAddress);
	currentByte &= ~mask;
	writeRegister(registerAddress, currentByte);
}

// sets the first 2 bits to turn the antenna on and clears to set off
void MFRC522::setAntennas(bool state) {
	if(state) {
		setMaskInRegister(TxControlReg, 0x03);
	} else {
		clearMaskInRegister(TxControlReg, 0x03);
	}
}

void MFRC522::clearFIFOBuffer(const uint8_t amountOfBytes) {
	// clears the FIFO read and write pointer, ErrorReg and BufferOvfl
	writeRegister(FIFOLevelReg, 0x80);
	uint8_t FIFOnewBytes[amountOfBytes] = {0};
	writeRegister(FIFODataReg, FIFOnewBytes, amountOfBytes);
}

void MFRC522::clearInternalBuffer() {
	clearFIFOBuffer(25);
	writeRegister(CommandReg, Mem);
}

uint8_t MFRC522::checkForErrors() {
	// Checking all the possible errors in the error register
	switch(readRegister(ErrorReg)) {
	case(1 << 0):
		return ProtocolErr;
	case(1 << 1):
		return ParityErr;
	case(1 << 2):
		return CRCErr;
	case(1 << 3):
		return CollErr;
	case(1 << 4):
		return BufferOvfl;
	case(1 << 6):
		return TempErr;
	case(1 << 7):
		return WrErr;
	default:
		return OkStatus;
	}
}

// RETURNS A ENUM CONNECTION_STATUS
uint8_t MFRC522::communicate(COMMAND command, uint8_t transmitData[],
                             int transmitLength, uint8_t receivedData[],
                             int & receivedLength) {

	uint8_t irqEn;
	uint8_t completedIrqReg;
	// Setting command stop variables
	if(command == Transceive) {
		irqEn= 0x77;
		completedIrqReg = 0x30;
	}

	writeRegister(ComIEnReg, irqEn|0x80);    // Interrupt request
	clearMaskInRegister(ComIrqReg, 0x80);    // Clear all interrupt requests bits.
	setMaskInRegister(FIFOLevelReg, 0x80);   // FlushBuffer=1, FIFO initialization.

	writeRegister(CommandReg, Idle);  // No action, cancel the current command.
	// Write to FIFO
	for(int i = 0; i < transmitLength; i++) {
		writeRegister(FIFODataReg, transmitData[i]);
	}

	// Execute the command.
	writeRegister(CommandReg, command);

	if(command == Transceive) {
		setMaskInRegister(BitFramingReg, 0x80);  // transmission of data starts
	}

	int msTillTimedOut = 25;
	uint8_t currentInterruptRR = readRegister(ComIrqReg);
	for(int i = 0; !(currentInterruptRR & completedIrqReg); i++) {
		currentInterruptRR = readRegister(ComIrqReg);

		// Timeout in time-out bit is active or after 25 milliseconds
		if(currentInterruptRR & 0x01 || (i > msTillTimedOut)) {
			return TimeOutStatus;
		}
		hwlib::wait_ms(1);
	}

	// Error checking
	uint8_t errorCode = checkForErrors();
	if(errorCode) {
		return errorCode;
	}

	// checks if there is enough room to store all the FIFO data
	if(receivedLength < readRegister(FIFOLevelReg)) {
		return NoRoom;
	}
	receivedLength = readRegister(FIFOLevelReg);

	// Reading the recieved data from FIFO.
	for(int i = 0; i < receivedLength; i++) {
		receivedData[i] = readRegister(FIFODataReg);
	}

	writeRegister(CommandReg, Idle);
	return OkStatus;
}

bool MFRC522::isCardInRange() {
	// Request REQA 26h(7 bit)
	// Wake-up WUPA 52h(7 bit)
	// So the framing is set to 7/111b/0x07
	writeRegister(BitFramingReg, 0x07); // amount of last bits 111b

	const uint8_t sendDataLength = 1;
	uint8_t sendData[sendDataLength] = {0x26};

	int receivedLength = 2;
	uint8_t receivedData[receivedLength] = {0};

	uint8_t status = communicate(Transceive, sendData, sendDataLength, receivedData, receivedLength);
	if((status != OkStatus)) {
		return false;
	}
	return true;

}

// You can call this command after each other. IsCardInRange() requires another rfid command to execute before executing again.
bool MFRC522::isCardInRangeCheck() {
	if(isCardInRange()) {
		resetAntennas();
		return true;
	}
	return false;
}


// returns status, param will become unique identifier.
// CASCADE LEVEL 1 used only
// https://www.nxp.com/docs/en/application-note/AN10927.pdf
uint8_t MFRC522::getCardUID(uint8_t UID[5]) {
	uint8_t serNum[2] = {CL1Command, 0x20};		//Put collision check data in the array

	// Only wake-up and request need 7 bit framing
	writeRegister(BitFramingReg, 0x00);			//Change the amount of bits transmitted from the last byte

	int length = 5;
	uint8_t status = communicate(Transceive, serNum, 2, UID, length);

	if(status != OkStatus) {
		return status;
	}

	if(length != 5 || checkUID4BCC(UID)) {
		return BCCErr;
	}
	return OkStatus;
}

bool MFRC522::getCardUIDSimple(uint8_t UID[5]) {
	if(isCardInRange()) {
		if(getCardUID(UID) == OkStatus) {
			return true;
		}
	}
	return false;

}

void MFRC522::waitForCardUID(uint8_t UID[5]) {
	while(true) {
		if(isCardInRange()) {
			if(getCardUID(UID) == OkStatus) {
				return;
			}
		}
	}
}

// TEST FUNCTIONS
uint8_t MFRC522::getVersion() {
	return readRegister(VersionReg) & 0x0F;
}

bool MFRC522::selfTest() {
	// check if firmware version is valid to execute this test
	uint8_t firmwareVersion = getVersion();
	if(firmwareVersion != 1 && firmwareVersion != 2) {
		return false;
	}

	// 1. Perform a soft reset
	softReset();
	// 2. Clear the internal buffer by writing 25 bytes of 00h
	clearInternalBuffer();
	// 3. Enable the self test by writing 09h to the AutoTestReg
	writeRegister(AutoTestReg, (1 << 3 | 1));
	// 4. Write 00h to the FIFO buffer
	writeRegister(FIFODataReg, 0x00);
	// 5. Start the self test with the CalcCRC command
	writeRegister(CommandReg, CalcCRC);
	// 6. The self test is initiated (WAIT TILL THE FIFO IS FILLED)
	while(readRegister(FIFOLevelReg) < FIFOAmountOfBytes) {}

	writeRegister(AutoTestReg, 0x00);

	uint8_t selfTestResult[FIFOAmountOfBytes] = {0};
	readRegister(FIFODataReg, selfTestResult, FIFOAmountOfBytes);

	const uint8_t* FIFOBytesCheckSpecificVersion = firmwareVersion == 1 ? selfTestFIFOBufferV1 : selfTestFIFOBufferV2;
	if(FIFOBytesCheckSpecificVersion == nullptr) {
		return false;
	}

	for(unsigned int i = 0; i < FIFOAmountOfBytes; i++) {
		if(selfTestResult[i] != FIFOBytesCheckSpecificVersion[i]) {
			return false;
		}
	}

	return true;
}
