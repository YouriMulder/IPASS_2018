#ifndef RFID_HPP
#define RFID_HPP

#include "hwlib.hpp"

/// @brief
///	A pure virtual class for a rfid chip like the MFRC522.
/// @details
/// This class is a pure virtual class.
/// This means that you can access methods of the derived class when using reference or pointers.
/// This makes the code easier to expand.
/// @warning
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
class rfid {
public:
	/// @brief Initialize the rfid chip for.
	/// @details
	/// This will reset the chip and initilize all the register.
	virtual void initialize() = 0;
protected:
	/// @brief Wait till the is started correctly after for example a soft reset.
	virtual void waitTillStarted() = 0;
public:
	/// @brief Hard reset the rfid chip probably with a hwlib::pin_out (wouter@voti.nl) 2017.
	/// @warning Note if the chip requires a external pin to reset the whole chip.
	/// The pin must me connected correctly.
	virtual void hardReset() = 0;

	/// @brief Soft reset the rfid chip.
	virtual void softReset() = 0;

	/// @brief Reset the Tx and Rx antennas
	/// @details This function is mostly used to
	/// stop communicating with a card without using the halt command.
	virtual void resetAntennas() = 0;
public:
	/// @brief Check if there is a card within the radio frequency field.
	/// @return A bool which will be 1 if a card is detected and 0 when not.
	/// @details
	/// This function checks whether there is a card within the radio frequency field.
	/// The function uses the rfid request command to achieve this.
	/// @warning
	/// After requesting the rfid card expects the user to send another command.
	/// When you you only want to check if a card is in the radio frequency field you should use
	/// isCardInRangeCheck
	virtual bool isCardInRange() = 0;

	/// @brief Check if there is a card within the radio frequency field.
	/// @return A bool which will be 1 if a card is detected and 0 when not.
	/// @details
	/// This function checks whether there is a card within the radio frequency field.
	/// The function uses the rfid request command to achieve this.
	/// After sending the request command both antennas are reset (#resetAntennas)
	/// to stop communicating with the card.
	/// @warning
	/// Use #isCardInRange when you want to send some commands after you send a request to the card.
	virtual bool isCardInRangeCheck() = 0;

	/// @brief Get the UID/NUID of 4 bytes UID card with the BCC byte.
	/// @param UID[5] The array you want the UID to get stored into.
	/// @return An uint8_t containing a possible error or succes code. (These codes are in the derived class)
	/// @details
	/// The UID of a card is a unique identifier.
	/// This UID can be used to know which card you're communicating with.
	/// The UID is used when more than one card is in the radio frequency field,
	/// also known as collision detection.<br>
	/// The last byte of UID[5] will be the bcc. This can be used to check if the UID is valid.
	/// @warning Note that the UID might not be as unique as you might expect.
	/// Some cards have a feature to rewrite the UID block.
	/// @warning Note that the UID[5] array will be overridden.
	virtual uint8_t getCardUID(uint8_t UID[5]) = 0;

	/// @brief A wrapper around #getCardUID to make it simpler
	/// @param UID[5] The array you want the UID to get stored into.
	/// @return A bool which will be 1 when everything went fine and 0 when there was an error.
	/// @details
	/// When the function returns a zero you should try @getCardUID
	/// instead because that function returns a more accurate return status.
	/// @warning Note that the UID might not be as unique as you might expect.
	/// Some cards have a feature to rewrite the UID block.
	/// @warning Note that the UID[5] array will be overridden.
	virtual bool getCardUIDSimple(uint8_t UID[5]) = 0;

	/// @brief This function waits till there is a card in range and gives the UID back.
	/// @warning This function blocks everything!
	/// And will continue when there is a card detected with valid UID.
	virtual void waitForCardUID(uint8_t UID[5]) = 0;

public:
	/// @brief check whether two UIDs are equal
	/// @param UID1[5] the first UID you want to check.
	/// @param UID2[5] the seconds UID you want to check.
	/// @param UIDSize the size of the arrays. NOTE THAT FOR NOW THEY HAVE TO BE 5.
	/// @return A bool containing a 1 when they're the same and a zero when the're not.
	/// @details
	/// This method will check if every value of the same index in the arrays are equal.
	/// The BCC is also checked for equality.
	virtual bool isUIDEqual(uint8_t UID1[5], uint8_t UID2[5], unsigned int UIDSize) {
		for(unsigned int i = 0; i < UIDSize; i++) {
			if(UID1[i] != UID2[i]) {
				return false;
			}
		}
		return true;
	}

	/// @brief This will check if the UID is valid using BCC
	/// @param UID[5] the array where the UID including the BCC is store.
	/// @details
	/// The UID[5] will NOT be changed using this function.
	/// This check was found on the following site:
	/// <a href="http://www.proxmark.org/forum/viewtopic.php?id=2274">BCC check</a>
	virtual bool checkUID4BCC(const uint8_t UID[5]) {
		uint8_t BCC = 0;
		const uint8_t UIDSize = 4;
		for(int i = 0; i < UIDSize; i++) {
			BCC ^= UID[i];
		}
		return (BCC ==UID[UIDSize + 1]);
	}

public:
	/// @brief
	/// Get the version of the rfid chip to perform for instance a #selfTest.
	/// @return An uint8_t containing the version value 1 or 2
	virtual uint8_t getVersion() = 0;

	/// @brief
	/// Let the rfid chip perform a self test.
	/// @return
	/// A bool containing a 1 when passed and 0 when failed the self test.
	/// @details
	/// The rfid chip performs a self test.
	/// The self testing sequence can be found in the datasheet
	/// <a href="https://www.nxp.com/docs/en/data-sheet/MFRC522.pdf">MFRC522 datasheet page 85</a>
	/// @warning Only version 1 and 2 are supported at the moment!
	/// Some clones might have another version. It might work fine when not passing the test.
	virtual bool selfTest() = 0;

};

#endif // RFID_HPP
