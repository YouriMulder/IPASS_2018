#ifndef PERSONALDATA
#define PERSONALDATA

#include <stdint.h>

struct personalData {
	char name[255];
	uint8_t accessLevel;
	uint8_t	UID[5];
};

#endif // PERSONALDATA
