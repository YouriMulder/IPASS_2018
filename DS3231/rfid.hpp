#ifndef RFID_HPP
#define RFID_HPP

#include "hwlib.hpp"

class rfid {
public:
	virtual void initialize() = 0;
protected:
	virtual void waitTillStarted() = 0;
public:
	virtual void hardReset() = 0;
	virtual void softReset() = 0;
	virtual void resetAntennas() = 0;
public:
	virtual bool isCardInRange() = 0;
	virtual bool isCardInRangeCheck() = 0;
	virtual uint8_t getCardUID(uint8_t UID[5]) = 0;
	virtual bool getCardUIDSimple(uint8_t UID[5]) = 0;
	virtual void waitForCardUID(uint8_t UID[5]) = 0;

public:
	virtual bool isUIDEqual(uint8_t UID1[5], uint8_t UID2[5], unsigned int UIDSize) {
		for(unsigned int i = 0; i < UIDSize; i++) {
			if(UID1[i] != UID2[i]) {
				return false;
			}
		}
		return true;
	}

	// http://www.proxmark.org/forum/viewtopic.php?id=2274
	virtual bool checkUID4BCC(uint8_t UID[5]) {
		uint8_t BCC = 0;
		const uint8_t UIDSize = 4;
		for(int i = 0; i < UIDSize; i++) {
			BCC ^= UID[i];
		}
		return (BCC ==UID[UIDSize + 1]);
	}

public:
	// TEST FUNCTIONS
	virtual uint8_t getVersion() = 0;
	virtual bool selfTest() = 0;

};

#endif // RFID_HPP
