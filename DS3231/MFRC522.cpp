#include "MFRC522.hpp"

#include "bitParser.hpp"

MFRC522::MFRC522(spiBus& SPIBus,
                 hwlib::pin_out& slaveSelect,
                 hwlib::pin_out& reset):
	SPIBus(SPIBus), slaveSelect(slaveSelect), reset(reset) {
	hardReset();

	// Reset baud rates
	writeRegister(TxModeReg, 0x00);
	writeRegister(RxModeReg, 0x00);
	// Reset ModWidthReg
	writeRegister(ModWidthReg, 0x26);

	// When communicating with a PICC we need a timeout if something goes wrong.
	// f_timer = 13.56 MHz / (2*TPreScaler+1) where TPreScaler = [TPrescaler_Hi:TPrescaler_Lo].
	// TPrescaler_Hi are the four low bits in TModeReg. TPrescaler_Lo is TPrescalerReg.
	writeRegister(TModeReg, 0x80);			// TAuto=1; timer starts automatically at the end of the transmission in all communication modes at all speeds
	writeRegister(TPrescalerReg, 0xA9);		// TPreScaler = TModeReg[3..0]:TPrescalerReg, ie 0x0A9 = 169 => f_timer=40kHz, ie a timer period of 25μs.
	writeRegister(TReloadReg1, 0x03);		// Reload timer with 0x3E8 = 1000, ie 25ms before timeout.
	writeRegister(TReloadReg2, 0xE8);

	writeRegister(TxASKReg, 0x40);			// Default 0x00. Force a 100 % ASK modulation independent of the ModGsPReg register setting
	writeRegister(ModeReg, 0x3D);

	setAntennas(1);
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
  for (i = 0; i < len; i++) {
    writeRegister(FIFODataReg, data[i]);
  }
  writeRegister(CommandReg, CalcCRC);

  // Wait for the CRC calculation to complete.
  i = 0xFF;
  do {
    n = readRegister(DivIrqReg);
    i--;
  } while ((i != 0) && !(n & 0x04));  //CRCIrq = 1

  // Read the result from the CRC calculation.
  result[0] = readRegister(CRCResult1Reg);
  result[1] = readRegister(CRCResult2Reg);
}

uint8_t MFRC522::transceive(uint8_t *sendData, int sendLen, uint8_t *backData, int *backLen) {
	//int status = MI_ERR;
	uint8_t irqEn = 0x77;
	//uint8_t waitIRq = 0x30;
	//uint8_t lastBits, n;
	//int i;
	
	
	writeRegister(ComIEnReg, irqEn | 1 << 7);
	clearMaskInRegister(ComIrqReg, 1 << 7);	// Clear interupts
	writeRegister(FIFOLevelReg, 1 << 7);					// reset the FIFO pointer
	writeRegister(CommandReg, Idle); 	// Stop any previous command		
	
	for(int i = 0; i < sendLen; i++) {
		writeRegister(FIFODataReg, sendData[i]);
	}
	
	writeRegister(CommandReg, Transceive);
	writeRegister(BitFramingReg, 1 << 7);
	
	for(unsigned int i = 0; i < 25; i++) {
		uint8_t interrupt = readRegister(ComIrqReg);
//		hwlib::cout << "IRQ ";
//		bitParser::printByte(readRegister(ComIrqReg));
//		hwlib::cout << "Error ";
//		bitParser::printByte(readRegister(ErrorReg));
//		hwlib::cout << "Status ";
//		bitParser::printByte(readRegister(Status1Reg));
		//bitParser::printByte(readRegister(TCounterValReg1));
		//bitParser::printByte(readRegister(TCounterValReg2));

		
		if(interrupt & 0x30) {
			break;
		}
		
		if(interrupt & 0x01 || i > 1999) {
			return STATUS_TIMEOUT;
		}
		hwlib::wait_ms(1);
	}
	
	clearMaskInRegister(BitFramingReg, 1 << 7);
	
	uint8_t errorRegValue = readRegister(ErrorReg);
	if (errorRegValue & 0x13) {	 // BufferOvfl ParityErr ProtocolErr
		return STATUS_ERROR;
	}	
	
	hwlib::cout << (unsigned)readRegister(FIFOLevelReg) << "\n";
	if (errorRegValue & 0x08) { // CollErr
		return STATUS_COLLISION;
	}
	
	
	if(readRegister(FIFOLevelReg) > *backLen) {
		return STATUS_NO_ROOM;
	}
	
	*backLen = readRegister(FIFOLevelReg);
	readRegister(FIFODataReg, backData, *backLen);
	for(int i = 0; i < *backLen; i++) {
		hwlib::cout << (unsigned)backData[i] << "\n";
	}
	
	return 0;
}

bool MFRC522::isCardPresented() {
	return 1;
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
