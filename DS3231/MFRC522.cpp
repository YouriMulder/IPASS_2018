#include "MFRC522.hpp"

#include "bitParser.hpp"

MFRC522::MFRC522(spiBus& SPIBus,
                 hwlib::pin_out& slaveSelect,
                 hwlib::pin_out& reset, bool init):
	SPIBus(SPIBus), slaveSelect(slaveSelect), reset(reset) {
	if(init) {
		initialize();
		setAntennas(1);
	}
}

void MFRC522::initialize() {
	hardReset();

	writeRegister(TModeReg, 0x8D);      // Tauto=1; f(Timer) = 6.78MHz/TPreScaler
	writeRegister(TxModeReg, 0); 		// Set speed to 106 kBd to be able to use some extra functionality
	writeRegister(TxModeReg, 0);		// Set speed to 106 kBd to be able to use some extra functionality

	writeRegister(TPrescalerReg, 0x3E); // TModeReg[3..0] + TPrescalerReg
	writeRegister(TReloadReg1, 0x03);	// 25ms timeout
	writeRegister(TReloadReg2, 0xE8);	// 25ms timeout

	writeRegister(TxASKReg, 0x40);      // 100%ASK
	writeRegister(ModeReg, 0x3D);       // CRC initial value 0x6363
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

uint8_t MFRC522::readRegister(REG registerAddress) {
	return SPIBus.getByteFromRegister((uint8_t)registerAddress, slaveSelect);
}

void MFRC522::readRegister(REG registerAddress, uint8_t read[],
                           uint8_t amountOfBytes) {
	SPIBus.getBytesFromRegister((uint8_t)registerAddress, read, amountOfBytes, slaveSelect);
}

void MFRC522::writeRegister(REG registerAddress, uint8_t newByte) {
	SPIBus.setByteInRegister((uint8_t)registerAddress, newByte, slaveSelect);
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

void MFRC522::calculateCRC(uint8_t *data, int len, uint8_t *result) {
	int i;
	uint8_t n;

	clearMaskInRegister(DivIrqReg, 0x04);   // CRCIrq = 0
	setMaskInRegister(FIFOLevelReg, 0x80);  // Clear the FIFO pointer

	//Writing data to the FIFO.
	for(i = 0; i < len; i++) {
		writeRegister(FIFODataReg, data[i]);
	}
	writeRegister(CommandReg, CalcCRC);

	// Wait for the CRC calculation to complete.
	i = 0xFF;
	do {
		n = readRegister(DivIrqReg);
		i--;
	} while((i != 0) && !(n & 0x04));   //CRCIrq = 1

	// Read the result from the CRC calculation.
	result[0] = readRegister(CRCResult1Reg);
	result[1] = readRegister(CRCResult2Reg);
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
uint8_t MFRC522::communicate(COMMANDS command, uint8_t transmitData[],
                             int transmitLength, uint8_t receivedData[],
                             int & receivedLength) {
	//setAntennas(1);
	uint8_t irqEn = 0x77;

	uint8_t completedIrqReg = 0x30;

	writeRegister(ComIEnReg, irqEn|0x80);    // interrupt request
	clearMaskInRegister(ComIrqReg, 0x80);             // Clear all interrupt requests bits.
	setMaskInRegister(FIFOLevelReg, 0x80);             // FlushBuffer=1, FIFO initialization.

	writeRegister(CommandReg, Idle);  // No action, cancel the current command.
	// Write to FIFO
	for(int i = 0; i < transmitLength; i++) {
		writeRegister(FIFODataReg, transmitData[i]);
	}

	// Execute the command.
	writeRegister(CommandReg, Transceive);

	if(/* cmd == MFRC522_TRANSCEIVE */ true) {
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

	// setting backLen
	receivedLength = readRegister(FIFOLevelReg);

	// Reading the recieved data from FIFO.
	for(int i = 0; i < receivedLength; i++) {
		receivedData[i] = readRegister(FIFODataReg);
	}

	//setAntennas(0);
	writeRegister(CommandReg, Idle);
	return OkStatus;
}

bool MFRC522::isCardInRange() {
	writeRegister(BitFramingReg, 0x07); //

	const uint8_t sendDataLength = 1;
	uint8_t sendData[sendDataLength] = {0x26};

	int receivedLength = 0;
	uint8_t receivedData[2] = {0};

	uint8_t status = communicate(Transceive, sendData, sendDataLength, receivedData, receivedLength);

	if((status != MI_OK)) {
		return false;
	}
	return true;

}


// returns status, param will become unique identifier.
bool MFRC522::getCardUID(uint8_t UID[]) {
	uint8_t serNum[2] = {0x93, 0x20};//Put collision check data in the array
	writeRegister(BitFramingReg, 0x00);//Change the amount of bits transmitted from the last byte

	int length;
	uint8_t status = communicate(Transceive, serNum, 2, UID, length);
	auto serNumCheck = 0;
	if(status == 0) {
		if((length) == 5) { //Change from amount of bits to amount of bytes and then check
			int i = 0;
			while(i<4) {
				serNumCheck = serNumCheck ^ UID[i];
				i++;
			}
			if(serNumCheck != UID[i]) {
				status = ParityErr;
			}
		} else {
			status = ParityErr;
		}
	}

	return status; //return the status
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
