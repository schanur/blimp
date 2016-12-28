#ifndef __BYTE_ORDER_C__
#define __BYTE_ORDER_C__

#include "byte_order.h"

void reverseBytes (char *cpStr, const uint8_t uiLength)
{
	uint8_t i;
	char cSwap;
	for (i = 0; i < uiLength / 2; i++) {
		cSwap = *(cpStr + i);
		*(cpStr + i) = *(cpStr + (uiLength - 1 - i));
		*(cpStr + (uiLength - 1 - i)) = cSwap;
	}	
}

void toNetworkByteOrder (char *cpStr, const uint8_t uiLength)
{
#if __ENDIANESS == LITTLE
	reverseBytes (cpStr, uiLength);
#elif __ENDIANESS == BIG
	/* Die Byte Order muss nicht
	 * geaendert werden, da die
	 * Netzwerkbyteorder ebenfalls
	 * Big Endian ist.
	 */
#endif
}

void toPlatformByteOrder (char *cpStr, const uint8_t uiLength)
{
/*#if __ENDIANESS == LITTLE*/
	reverseBytes (cpStr, uiLength);
/*#elif __ENDIANESS == BIG*/
	/* Die Byte Order muss nicht
	 * geaendert werden, da die
	 * Netzwerkbyteorder ebenfalls
	 * Big Endian ist.
	 */
/*#else
#error no endianess defined
#endif*/
}

#endif
