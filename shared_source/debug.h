#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "platform_specifics_macros.h"

#include "protocolNumbers.h"

#ifndef __cplusplus

#include <avr/io.h>
#include <avr/interrupt.h>

#include "../blimp__atmega_mc/defines.h"
#include "../blimp__atmega_mc/makros.h"
//#include "../blimp__atmega_mc/io/uart.c"
#include "uart_protocol_handler.h"
#else
#include <iostream>
#include <cstdlib>
#endif

#define __DEBUG_TRANSACTION_OFF		0
#define __DEBUG_TRANSACTION_START	1
#define __DEBUG_TRANSACTION_END		2

/// Forward declaration
uint8_t uartProtocolSendRequest (const char*, const uint8_t, const uint8_t);

void printDebugMsg (const char *ipDebugMsg);
void debugMsgTransactionStart ();
void debugMsgTransactionEnd ();
void panic ();

volatile uint8_t uiInDebugTransaction;

#endif
