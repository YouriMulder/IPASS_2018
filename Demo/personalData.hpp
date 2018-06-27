// -----------------------------------------------------------
// (C) Copyright Youri Mulder 2018.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// -----------------------------------------------------------

#ifndef PERSONALDATA
#define PERSONALDATA

#include <stdint.h>

struct personalData {
	char name[255];
	uint8_t accessLevel;
	uint8_t	UID[5];
};

#endif // PERSONALDATA
