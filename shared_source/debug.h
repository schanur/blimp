#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "platform_specifics_macros.h"

#include "protocolNumbers.h"

#if __PLATFORM == 2
	#include <avr/io.h>
	#include <avr/interrupt.h>

	#include "../blimp__atmega_mc/defines.h"
	#include "../blimp__atmega_mc/makros.h"
	#include "../blimp__atmega_mc/io/uart.h"
	#include "uart_protocol_handler.h"

	extern struct strUartProtocol strPCDataLink;

#elif __PLATFORM == 1
	#include <iostream>
	#include <cstdlib>
#endif


#define __DEBUG_TRANSACTION_OFF		0
#define __DEBUG_TRANSACTION_START	1
#define __DEBUG_TRANSACTION_END		2

/* Forward declaration */
/*uint8_t uartProtocolSendRequest (struct strUartProtocol *strProtocolLink,
		const char *uipResponse,
		const uint8_t uiPayloadLength,
		const uint8_t uiPacketTypeNo);*/

void printDebugIdent ();
void printDebugMsg (const char *ipDebugMsg);

#if __PLATFORM == 2
void debugMsgTransactionStart ();
void debugMsgTransactionEnd ();
volatile uint8_t uiInDebugTransaction;
#endif

void panic ();

#endif
