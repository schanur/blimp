#ifndef __BYTE_ORDER_H__
#define __BYTE_ORDER_H__

#include "platform_specifics_macros.h"
#include <inttypes.h>


void reverseBytes (char *cpStr, const uint8_t uiLength);

void toNetworkByteOrder (char *cpStr, const uint8_t uiLength);
void toPlatformByteOrder (char *cpStr, const uint8_t uiLength);

#endif
