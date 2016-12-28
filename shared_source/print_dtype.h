#ifndef __PRINT_DTYPES_H__
#define __PRINT_DTYPES_H__

//#ifndef _cplusplus
//#include "../blimp__atmega_mc/io/uart.c"
//#include <stdlib.h>
//#else
//#include <stdlib.h>
//#endif

#include "platform_specifics_macros.h"

#include <inttypes.h>

void U32IntToString (char *buf, uint32_t number);
void S32IntToSting (char *buf, int32_t number);
void Bin8ToString (char *buf, const char noToPrint);
void BinVarToString (char *buf, const char *noToPrint, const uint8_t uiLength);

#endif