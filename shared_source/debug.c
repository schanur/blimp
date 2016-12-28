#ifndef __DEBUG_C__
#define __DEBUG_C__

#include "debug.h"

//void uartProtocolSendRequest (const char*, uint8_t, uint8_t);

void printDebugIdent ()
{
	#ifndef __cplusplus
	uartProtocolSendRequest (&strPCLink, "atme", 4, __UART_PROTOCOL_MESSAGE);
	uartProtocolSendRequest (&strPCLink, "ga_m", 4, __UART_PROTOCOL_MESSAGE);
	uartProtocolSendRequest (&strPCLink, "c: ", 3, __UART_PROTOCOL_MESSAGE);
	#else
	std::cerr << __PLATFORM_NAME << ":  ";
	#endif
}

void printDebugMsg (const char *ipDebugMsg)
{
	if (uiInDebugTransaction == 0) {
		printDebugIdent ();
	}
	#ifndef __cplusplus
	
	uint8_t i, uiPacketLength, uiMessageLength = 0;
	//return;
	/// FIXME: 32 irgendwo anders her nehmen
	for (i = 0; i < 63; i++) {
		if (*(ipDebugMsg + i) == 0) {
			uiMessageLength = i;
			break;
		}
	}
	if (uiMessageLength != 0) {
		for (i = 0; i <= uiMessageLength / __MAX_PAYLOAD_SIZE; i++) {
			/// Prüfe auf letztes Paket
			if (i == uiMessageLength / __MAX_PAYLOAD_SIZE) {
				uiPacketLength = uiMessageLength % __MAX_PAYLOAD_SIZE;
			} else {
				uiPacketLength = __MAX_PAYLOAD_SIZE;
			}
			//uiPacketLength--;
			uartProtocolSendRequest (&strPCLink, ipDebugMsg + i * __MAX_PAYLOAD_SIZE, uiPacketLength, __UART_PROTOCOL_MESSAGE);
		}
		if (uiInDebugTransaction == 0) {
			uartProtocolSendRequest (&strPCLink, "\n", 1, __UART_PROTOCOL_MESSAGE);
		}
	} else {
		printDebugMsg ("\nprintDebugMsg (): no termination\n");
	}
	#else
	std::cerr << ipDebugMsg;
	if (uiInDebugTransaction == 0) {
		std::cerr << std::endl; 
	}
	std::cerr << std::flush;
	#endif
}

#define __DEBUG_TRANSACTION_OFF		0
#define __DEBUG_TRANSACTION_START	1
#define __DEBUG_TRANSACTION_RUNNING	2

void debugMsgTransactionStart ()
{
	__ENTER_CRITICAL_SECTION;
	uint8_t uiTransactionDepth = uiInDebugTransaction;
	__LEAVE_CRITICAL_SECTION;
	if (uiTransactionDepth == 0) {
		printDebugIdent ();
	}
	uiInDebugTransaction++;
	
}
void debugMsgTransactionEnd ()
{
	__ENTER_CRITICAL_SECTION;
	//uiInDebugTransaction = DEBUG_TRANSACTION_OFF;
	if (uiInDebugTransaction == 1) {
		uartProtocolSendRequest (&strPCLink, "\n", 1, __UART_PROTOCOL_MESSAGE);
	}
	uiInDebugTransaction--;
	__LEAVE_CRITICAL_SECTION;
}

void panic ()
{
	printDebugMsg ("\nPANIC!\n");
	#ifndef __cplusplus
	while (1);
	#else
	exit (1);
	#endif
}

#endif

