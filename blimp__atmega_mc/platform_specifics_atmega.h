#ifndef __PLATFORM_SPECIFICS_H__
	#define __PLATFORM_SPECIFICS_H__ 2
#endif

#if __PLATFORM_SPECIFICS_H__ == 2
	#ifndef __PLATFORM_SPECIFICS_ATMEGA_MC_H__
		#define __PLATFORM_SPECIFICS_ATMEGA_MC_H__ 
		//#include "../shared_source/platform_specifics_macros.h"

		#ifdef __PLATFORM_SPECIFICS_BLIMP_PC_H__
			#error: more than one platform_specifics.h included.
		#endif

		#include <stdint.h>


		#define __PLATFORM_NAME "atmega mc"
		#define __ENDIANESS LITTLE

		/// Makros fuer das Protokoll

		//extern struct uartBuffer strBufferToPut;

		//int8_t uartGetChar(struct uartBuffer *strBufferToGet, 
		//char *uiReceivedChar);
		//int8_t uartPutChar(struct uartBuffer *strBufferToPut, 
		//char uiCharToSend);


		//#define UART_RECEIVE_NONBLOCK(x) uartGetChar(strUARTLink, (x))

		/// UART Sequenznummerbereiche
		#define __UART_SEQENCE_NO_BEGIN		32
		#define __UART_SEQENCE_NO_END		63

		#ifdef __cplusplus
			#error wrong compiler
		#endif
	#endif
#endif
