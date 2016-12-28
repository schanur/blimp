#ifndef __DEFINES_H__
#define __DEFINES_H__

#define _cplusplus
//#ifdef __DEBUG
//	#error: __DEBUG already defined.
//#elif
	//#define __DEBUG
	#include <assert.h>
//#endif

/// Numerische Konstanten
#define __PI 3.141592653589793
#define __EARTH_RADIUS 6371000.
//		meassured by gpsdrive.de: __6383254.445

/// SerialConnection
//#define __SERCON_DEFAULT_LINE_TERMINATOR '\n'
//#define __SERCON_MODE_BINARY 0
//#define __SERCON_MODE_ASCII 1
#define __SERCON_MAX_QUEUE_SIZE 32
#define __SERCON_QUEUE_TIMEOUT_SIZE 256

/// Multiplexer
#define __MULTIPLEXER_MAX_WORD_LENGTH 8
#define __MULTIPLEXER_RECEIVE_BUFFER_SIZE 32
#define __MULTIPLEXER_SEND_BUFFER_SIZE 32

/// Geraete Namen
#define __DEV_CPU_INFO "/proc/cpuinfo"
#define __DEV_MC "/dev/ttyS0"
#define __DEV_MC_RECEIVE_BUF "/tmp/uartReceiveBuf"
#define __DEV_MC_SEND_BUF "/tmp/uartSendBuf"
//#define __DEV_MC "/home/ze/code/current/blimp__pc/testfifo"
#define __DEV_GPS "/dev/ttyS1"

/// Protokollzeichen
#define __RS232_CR 0

/// DataExchange Modi
#define __DATA_EXCHANGE_MODE_CREATE 0
#define __DATA_EXCHANGE_MODE_OPEN 1

/// DataExchange Magic Keys
#define __DATA_EXCHANGE_KEY_STATUS 33
#define __DATA_EXCHANGE_KEY_SET 43
#endif
