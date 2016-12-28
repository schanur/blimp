#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

#include <stdlib.h>
#include <avr/interrupt.h>

#include "../defines.h"
#include "../makros.h"

//#include "../platform_specifics_atmega.h"

struct ringBuffer {
	volatile uint8_t	uiBufferSize;
	//volatile char		caBuffer[32];
	volatile char		*capBuffer;
	volatile char		*capReadPos;
	volatile char		*capWritePos;
};

void incBufferPointer (struct ringBuffer const *strpRingBuffer, volatile char **capBufferPointer);

int8_t initBuffer (struct ringBuffer *strpRingBuffer, const uint8_t uiBufferSize);
void destroyBuffer (struct ringBuffer const *strpRingBuffer);
uint8_t freeBufferSize (const struct ringBuffer const *strpRingBuffer);
uint8_t charsInBuffer (const struct ringBuffer const *strpRingBuffer);
int8_t readFromBuffer (struct ringBuffer *strpRingBuffer, char* cpReadChar);
int8_t writeToBuffer (struct ringBuffer *strpRingBuffer, const char cWriteChar);

#endif
