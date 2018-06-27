// -----------------------------------------------------------
// (C) Copyright Youri Mulder 2018.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// -----------------------------------------------------------

#ifndef bitParser_HPP
#define bitParser_HPP

#include "hwlib.hpp"

/** @addtogroup bitParser
 *  @{
 */
namespace bitParser {
/// @addtogroup bitParser
/// @{

/// @brief Mask for a whole byte.
const int nBitsinByte = 8;
/// @brief Mask for half of a byte.
const int nBitsinHalfAByte = 4;
/// @brief Mask for the 4 left bits of a byte.
const uint8_t leftHalfByteMask = 0x78;
/// @brief Mask for the 4 right bits of a byte.
const uint8_t rightHalfgByteMask = 0xF;

/// @brief Print a byte to the console.
/// @details
/// The byte is printed with the LSB first (left).
/// @warning
/// The byte is printed with the LSB first (left).
void printByte(uint8_t byte);

/// @brief Print a two bytes to the console.
/// @details
/// The bytes are printed with the LSB first (left).
/// @warning
/// The byte are printed with the LSB first (left).
void printBytes(uint16_t bytes);

/// @brief Turn a BCD-coded value into a decimal value.
/// @param BCD the BCD-coded value you want to turn into a decimal value.
/// @return An uint8_t containing the decimal value of the BCD-coded value.
/// @see DECToBCD for doing the opposite.
uint8_t BCDToDEC(uint8_t BCD);

/// @brief Turn a decimal value into a BCD-coded value.
/// @param DEC the decimal value you want to turn into a BCD-coded value.
/// @return An uint8_t containing BCD-coded value of the decimal value.
/// @see BCDtoDEC for doing the opposite.
uint8_t DECToBCD(uint8_t DEC);

/// @brief Turn a uint8_t into a signed integer.
/// @param byte the uint8_t you want to turn into a signed integer.
/// @return An signed int containing the signed value of the uint8_t.
int uint8_tToInt(uint8_t byte);
/// @}
}
/// @}

#endif // bitParser_HPP
