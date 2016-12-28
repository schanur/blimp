#ifndef __UART_BUFFER_H__
#define __UART_BUFFER_H__

#include "ring_buffer.c"

struct uartBuffer {
	struct ringBuffer receive;
	struct ringBuffer send;
};

int8_t initUartBuffer (struct uartBuffer *strpUartBuffer, uint8_t uiReceiveBufferSize, uint8_t uiSendBufferSize);
void destroyUartBuffer (struct uartBuffer *strpUartBuffer);

/// Interrupt-Handler der aufgerufen wird,
/// wenn ein neues Zeichen auf dem RS232-Bus
/// empfangen wurde. Das empfange Zeichen
/// wird auf den Receive Buffer geschrieben.
/// Wenn der Receive Buffer voll ist,
/// findet eine Fehlerbehandlung statt.
//void intHandlerCharReceivedOnRS232 ();

/// Interrupt-Handler der aufgerufen wird,
/// wenn ein Zeichen auf dem RS232-Bus
/// gesendet wurde. Die Funktion prueft ob
/// weitere Zeichen auf dem Buffer stehen,
/// die gesendet werden koennen. Wenn ja,
/// dann wir ein weiteres Zeichen gesendet
//void intHandlerCharSendOnRS232 ();

#endif
