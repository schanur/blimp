#ifndef __UART_PROTOCOL_HANDLER_H__
#define __UART_PROTOCOL_HANDLER_H__

#ifndef __PLATFORM_SPECIFICS_ATMEGA_MC_H__
#ifndef __PLATFORM_SPECIFICS_BLIMP_PC_H__
#error no __PLATFORM_SPECIFICS_[$PLATFORM_NAME]_H__ included
#endif
#endif

#ifndef UART_RECEIVE_NONBLOCK
#error protocol don't know how to receive bytes. UART_RECEIVE_NONBLOCK is not defined.
#endif

#ifndef UART_SEND_NONBLOCK
#error protocol don't know how to send bytes. UART_SEND_NONBLOCK is not defined.
#endif

//#include "../defines.h"
//#include "../blimp__atmega_mc/global_vars.c"

#include "protocolNumbers.h"
#include "protocolPackets.h"

#include "debug.h"

/* 
 * Protokollbeschreibung:
 * Byte 0:         Pakettyp-Nummer
 * Byte 1:         Paket Sequenznummer (fortlaufende Nummer (wird vom PC generiert))
 * Byte 2:         Datenpaketlaenge
 * Byte 3 bis n-1: Nutzdaten
 * letztes Byte:   Pruefsumme. Wird durch die Anwendung
 *                 von XOR ueber alle Datenbytes berechnet
 */

#define __PACKET_TYPE_POS	0
#define __SEQUENCE_NO_POS	1
#define __PACKET_LENGTH_POS 	2
#define __PAYLOAD_START_POS	3

#define __HEADER_SIZE		3
#define __MAX_PAYLOAD_SIZE	4
#define __CHECKSUM_SIZE		1

#define __UART_REMOTE_REQUEST		0
#define __UART_REMOTE_RESPONSE		1

/// //Forward declaration
/// function prototype
//int uartProtocolHandlePacket ();
//uint8_t uartProtocolHandlePacket ();

struct strCommandBuffer {
	char commandData[__HEADER_SIZE + __MAX_PAYLOAD_SIZE + __CHECKSUM_SIZE];
	uint8_t dataPos;
};

struct strProtocol {
	uint8_t	uiOccuredErrorCode;
	uint8_t uiConnectionState;
	uint8_t uiReceiveResetCharCount;
	uint8_t uiSendResetCharCount;
	uint16_t uiUARTWatchdog;
	uint8_t uiSequenceNoBegin;
	uint8_t uiSequenceNoEnd;
	uint8_t uiSequenceNoSendPos;
	uint8_t uiSequenceNoReceivePos;
	struct strCommandBuffer receive;
	struct strCommandBuffer send;
};

struct strProtocol protocol;

uint8_t uartProtocolInitProtocolHandler (const uint8_t uiSequenceNoBegin, const uint8_t uiSequenceNoEnd);
void uartProtocolIncSequenceNo (uint8_t *uiSequenceNoToInc, uint8_t uiSequenceBarrier);
uint8_t uartProtocolNewCommandReceived ();
uint8_t uartProtocolcalcXORChecksum (const char* const uipData, const uint8_t uiDataLength);
uint8_t uartProtocolNewCommandValid ();

uint8_t uartProtocolSendMessage (const char *uipResponse, const uint8_t uiPayloadLength, const uint8_t uiSeqenceNo, const uint8_t uiPacketTypeNo);
uint8_t uartProtocolSendResponse (const char *uipResponse, const uint8_t uiPayloadLength);
uint8_t uartProtocolSendRequest (const char *uipResponse, const uint8_t uiPayloadLength, const uint8_t uiPacketTypeNo);
uint8_t uartProtocolGetPacketType ();


void uartProtocolClearIncomingCommandBuffer ();

void uartProtocolUndoResetProgress ();
uint8_t uartProtocolConnectionReset ();

uint8_t uartProtocolDoHandlerStep ();

#endif

