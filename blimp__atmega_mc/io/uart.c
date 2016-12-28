#ifndef __UART_C__
#define __UART_C__

#include "uart.h"

void initUart(struct uartBuffer *strBufferToInit)
{
	//initUartBuffer (strBufferToInit, 48, 48);

	long aaubrr0 = (F_CPU/((unsigned long)16 * BAUDRATE)) - 1;
	UBRR0H = (aaubrr0>>8);
	UBRR0L = (aaubrr0 & 0xFF);
   
	/// UART Receiver und Transmitter anschalten
	/// Data mode 8N1, asynchron
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

	/// Flush Receive-Buffer (entfernen evtl. vorhandener ung�ltiger Werte)
	do {
		uint8_t dummy;
		(void) (dummy = UDR0);
	}
	while (UCSR0A & (1 << RXC0));

	/// Einschalten der Interrupts
	//UCSR0B |= (1 << RXCIE0);
	//UCSR0B |= (1 << TXCIE0);
	return;
}

int8_t uartPutChar (struct uartBuffer *strBufferToPut, 
		char uiCharToSend)
{
	if (writeToBuffer (&(strBufferToPut->send), uiCharToSend) == __SUCCESS) {
		UCSR0B |= (1 << UDRIE0);
		return (__SUCCESS);
	}
	return (__ERROR);
}

int8_t uartPutCharArray (struct uartBuffer *strBufferToPutA, 
		char *uipCharArrayToSend, 
		uint8_t uiLength)
{
	__ENTER_CRITICAL_SECTION;
	if (freeBufferSize (&(strBufferToPutA->send)) < uiLength) {
		__LEAVE_CRITICAL_SECTION;
		return (__ERROR);
	}
	uint8_t i;
	for (i = 0; i <= uiLength; i++) {
		while (uartPutChar (strBufferToPutA, *(uipCharArrayToSend + i)) == __ERROR) {
		}
	}
	__LEAVE_CRITICAL_SECTION;
	return (__SUCCESS);
}

int8_t uartPutString (struct uartBuffer *strBufferToPutS, 
		char *uipStringToSend)
{
	uint8_t i;
	uint8_t uiMaxStringLength = strBufferToPutS->send.uiBufferSize;
	for (i = 0; i <= uiMaxStringLength; i++) {
		if (*(uipStringToSend + i) == 0) {
			return (uartPutCharArray (strBufferToPutS, uipStringToSend, i));
		}
	}
	/// Der String ist groesser als der Buffer oder
	/// der String ist nicht mit 0 terminiert.
	return (__ERROR);
}

int8_t uartGetChar (struct uartBuffer *strBufferToGetC, 
		char *uiReceivedChar) 
{
	return (readFromBuffer (&(strBufferToGetC->receive), uiReceivedChar));
}

#endif
