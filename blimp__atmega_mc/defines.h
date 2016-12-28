#ifndef __DEFINES_H__
#define __DEFINES_H__



#define F_CPU 20000000UL
//#define F_CPU 16000000UL
#define UBRR_BAUD ((F_CPU)/(16*(BAUD))-1)
#define BAUDRATE 9600

/// Protokoll Return Codes
/// FIXME error = 1???
#define __ERROR 1
#define __SUCCESS 0

#define __INCOMPLETE 1
#define __COMPLETE 0

/// UART Buffer
#define __UART_RECEIVE_BUFFER_SIZE 		32
#define __UART_SEND_BUFFER_SIZE 		32

/// Error Codes
#define __ERROR_UNKNOWN				1					
#define __ERROR_RECEIVE_BUFFER_OVERFLOW 	10
#define __ERROR_UART_PUT_STRING 		14
#define __ERROR_PROTOCOL_UNKNOWN_REQUEST 	30

/// Schrittmotoren
// Für die Position der Antriebsmotoren
#define _ENGINE_ 1
// Sensoren Vertikal
#define _VERTICAL_ 2
// Sensoren Horizotal
#define _HORIZONTAL_ 3

#endif
