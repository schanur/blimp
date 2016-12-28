#ifndef __PLATFORM_SPECIFICS_H__
	#define __PLATFORM_SPECIFICS_H__ 1
#endif

#if __PLATFORM_SPECIFICS_H__ == 1
	#ifndef __PLATFORM_SPECIFICS_BLIMP_PC_H__
		#define __PLATFORM_SPECIFICS_BLIMP_PC_H__
		//#include "../shared_source/platform_specifics_macros.h"
		#ifdef __PLATFORM_SPECIFICS_ATMEGA_MC_H__
			#error: more than one platform_specifics.h included.
		#endif

		//class SerialConnection;
		//#include "SerialConnection.cpp"
		//SerialConnection *ser;
		//#include "io/uart.c"

		#define __PLATFORM_NAME "blimp pc"
		#define __ENDIANESS LITTLE

		/// Protokoll Return Codes
		#define __ERROR 1
		#define __SUCCESS 0

		#define __INCOMPLETE 1
		#define __COMPLETE 0

		/// UART Sequenznummerbereiche
		#define __UART_SEQENCE_NO_BEGIN		0
		#define __UART_SEQENCE_NO_END		31

		/// Makros fuer das Protokoll
		//#define UART_RECEIVE_NONBLOCK ser->getChar
		//#define UART_SEND_NONBLOCK ser->putChar
		//#define UART_RECEIVE_NONBLOCK(x) uartGetChar(x)
		//#define UART_SEND_NONBLOCK(x) uartPutChar(x)

		#define __ENTER_CRITICAL_SECTION //
		#define __LEAVE_CRITICAL_SECTION //

		#ifndef __cplusplus
			#error wrong compiler
		#endif
	#endif
#endif
