#ifndef __PRINT_DTYPES_C__
#define __PRINT_DTYPES_C__

#ifndef _cplusplus
//#include "../blimp__atmega_mc/io/uart.c"
#include <stdlib.h>
#else
#include <stdlib.h>
#endif

//#include "debug.c"


void U32IntToString (char *buf, uint32_t number)
{
	uint8_t uiBufPos = 11;
	char caBuffer[12];
	uint8_t i;
	caBuffer[11] = 0x00;
	do {
		caBuffer[--uiBufPos] = (number % 10) + 48;
		number /= 10;
	} while (number != 0);
	for (i = 0; i < (11 - uiBufPos); i++) {
		*(buf++) = caBuffer[uiBufPos++];
	}
}

void S32IntToSting (char *buf, int32_t number)
{
	if (number < 0) {
		
		*(buf++) = '-';	
		if (number == -2147483647) {
			{
				uint8_t i;
				char tmpStr[] = "2147483647";
				for (i = 0; i < 10; i++) {
					*buf = tmpStr[i];
				}
			}
		} else {
			number = -number;	
		}
	}
	U32IntToString (buf, number);
}

void Bin8ToString (char *buf, const char noToPrint) {
	uint8_t i, j;
	char caBinPacket[5];
	caBinPacket[4] = 0;

	for (i = 0; i < 2; i++) {
		for (j = 0; j < 4; j++) {
			if (noToPrint & (1 << (7 - (i * 4 + j)))) {
				buf[j] = '1';
			} else {
				buf[j] = '0';
			}
		}
	}
}

void BinVarToString (char *buf, const char *noToPrint, const uint8_t uiLength)
{
	uint8_t i;
	for (i = 0; i < uiLength; i++) {
		Bin8ToString (buf, *(noToPrint + i));
		buf += 8;
	}
}

#endif
