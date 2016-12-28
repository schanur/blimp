#ifndef __UART_BUFFER_C__
#define __UART_BUFFER_C__

#include "../defines.h"

#include "uart_buffer.h"



int8_t initUartBuffer (struct uartBuffer *strpUartBuffer, uint8_t uiReceiveBufferSize, uint8_t uiSendBufferSize)
{
	if (initBuffer (&strpUartBuffer->receive, uiReceiveBufferSize) == __ERROR) {
		return (__ERROR);
	}
	if (initBuffer (&strpUartBuffer->send, uiSendBufferSize) == __ERROR) {
		destroyBuffer (&strpUartBuffer->receive);
		return (__ERROR);
	}
	return (__SUCCESS);
}

void destroyUartBuffer (struct uartBuffer *strpUartBuffer) {
	destroyBuffer (&strpUartBuffer->receive);
	destroyBuffer (&strpUartBuffer->send);
}

#endif
