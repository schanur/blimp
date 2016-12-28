#ifndef __RING_BUFFER_C__
#define __RING_BUFFER_C__

#include "ring_buffer.h"


void incBufferPointer (struct ringBuffer const *strpRingBuffer, volatile char **capBufferPointer)
{
	if ((int8_t) ((*capBufferPointer) - strpRingBuffer->capBuffer)
			== strpRingBuffer->uiBufferSize) {
		(*capBufferPointer) = (volatile char*) strpRingBuffer->capBuffer;
	} else {
		(*capBufferPointer)++;
	}
	return;
}

int8_t initBuffer (struct ringBuffer *strpRingBuffer, const uint8_t uiBufferSize)
{
	if (uiBufferSize < 2) {
		return (__ERROR);
	}
	strpRingBuffer->uiBufferSize = uiBufferSize;
	strpRingBuffer->capBuffer = (volatile char*) malloc (strpRingBuffer->uiBufferSize);
	if (strpRingBuffer->capBuffer == NULL) {
		return (__ERROR);
	}
	strpRingBuffer->capReadPos = strpRingBuffer->capBuffer;
	strpRingBuffer->capWritePos = strpRingBuffer->capBuffer;
	return (__SUCCESS);
}

void destroyBuffer (struct ringBuffer const *strpRingBuffer)
{
	free ((void *) strpRingBuffer->capBuffer);
}

uint8_t freeBufferSize (const struct ringBuffer const *strpRingBuffer)
{
	__ENTER_CRITICAL_SECTION;
	uint8_t uiFreeBufferSize;
	if (strpRingBuffer->capWritePos >= strpRingBuffer->capReadPos) {
		uiFreeBufferSize = strpRingBuffer->uiBufferSize
				- (uint8_t) (strpRingBuffer->capWritePos
				- strpRingBuffer->capReadPos);
	} else {
		uiFreeBufferSize = ((uint8_t) (strpRingBuffer->capReadPos - strpRingBuffer->capWritePos)) - 1;
	}
	__LEAVE_CRITICAL_SECTION;
	return (uiFreeBufferSize);
}

uint8_t charsInBuffer (const struct ringBuffer const *strpRingBuffer)
{
	return (strpRingBuffer->uiBufferSize - freeBufferSize (strpRingBuffer));
}

int8_t readFromBuffer (struct ringBuffer *strpRingBuffer, char* cpReadChar)
{
	__ENTER_CRITICAL_SECTION;
	if (charsInBuffer (strpRingBuffer) == 0) {
		/// Fehler: kein weiteres Zeichen im Buffer
		__LEAVE_CRITICAL_SECTION;
		return (__ERROR);
	}
	*cpReadChar = *strpRingBuffer->capReadPos;
	incBufferPointer (strpRingBuffer, &(strpRingBuffer->capReadPos));
	__LEAVE_CRITICAL_SECTION;
	return (__SUCCESS);
}

int8_t writeToBuffer (struct ringBuffer *strpRingBuffer, const char cWriteChar)
{
	__ENTER_CRITICAL_SECTION;
	if (freeBufferSize (strpRingBuffer) == 0) {
		/// Fehler: Der Empfangsbuffer ist übergelaufen.
		__LEAVE_CRITICAL_SECTION;
		return (__ERROR);
	}
	*strpRingBuffer->capWritePos = cWriteChar;
	incBufferPointer (strpRingBuffer, &(strpRingBuffer->capWritePos));
	__LEAVE_CRITICAL_SECTION;
	return (__SUCCESS);
}

#endif
