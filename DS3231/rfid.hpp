#ifndef RFID_HPP
#define RFID_HPP

class rfid {
public:
	virtual void initialize() = 0;
protected:
	virtual void waitTillStarted() = 0;
public:
	virtual void hardReset() = 0;
	virtual void softReset() = 0;
public:
	virtual bool isCardInRange() = 0;
	virtual bool getCardUID(uint8_t UID[]) = 0;

public:
	// TEST FUNCTIONS
	virtual uint8_t getVersion() = 0;
	virtual bool selfTest() = 0;

};

#endif // RFID_HPP
