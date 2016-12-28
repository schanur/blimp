#ifndef __UART_H__
#define __UART_H__

//#include <stdlib.h>
//#include <avr/io.h>
//#include <stdint.h>

#include "../defines.h"

#include "../makros.h"
#include "uart_buffer.c"


void initUart (struct uartBuffer *strBufferToInit);

int8_t uartPutChar (struct uartBuffer *strBufferToPut, 
		char uiCharToSend);

int8_t uartPutCharArray (struct uartBuffer *strBufferToPutA, 
		char *uipCharArrayToSend, 
		uint8_t uiLength);

int8_t uartPutString (struct uartBuffer *strBufferToPutS, 
		char *uipStringToSend);

int8_t uartGetChar (struct uartBuffer *strBufferToGetC, 
		char *uiReceivedChar);


#endif
