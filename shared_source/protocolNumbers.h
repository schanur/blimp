#ifndef __PROTOCOL_NUMBERS_H__
#define __PROTOCOL_NUMBERS_H__




/* FIXME: sind doppelt! */
#define __ERROR 1
#define __SUCCESS 0
#define __INCOMPLETE 1
#define __COMPLETE 0

#define __UART_PROTOCOL_ECHO				10

#define __UART_PROTOCOL_MESSAGE				12

#define __UART_PROTOCOL_ATMEGA_STATE_RAM_USAGE		20
#define __UART_PROTOCOL_ATMEGA_STATE_BUFFER_USAGE_RX	22
#define __UART_PROTOCOL_ATMEGA_STATE_BUFFER_USAGE_TX	24
/*#define __PROTOCOL_ATMEGA_STATE_			26
  #define __PROTOCOL_ATMEGA_STATE_RAM			28*/

#define __UART_PROTOCOL_ENGINE_BOTH					38
#define __UART_PROTOCOL_ENGINE_RIGHT				40
#define __UART_PROTOCOL_ENGINE_LEFT					42
#define __UART_PROTOCOL_STEPPER_ENGINE				44	
#define __UART_PROTOCOL_STEPPER_VERTICAL			46
#define __UART_PROTOCOL_STEPPER_HORIZONTAL			48
#define __UART_PROTOCOL_SENSOR_COMPASS_8_BIT_RES	50
#define __UART_PROTOCOL_SENSOR_COMPASS_16_BIT_RES	52
#define __UART_PROTOCOL_SENSOR_ULTRASONIC_START		60
#define __UART_PROTOCOL_SENSOR_ULTRASONIC_READ		61

#define __UART_PROTOCOL_COMMAND_LED_1				120
#define __UART_PROTOCOL_COMMAND_LED_2			121
#define __UART_PROTOCOL_COMMAND_LED_3			122
#define __UART_PROTOCOL_COMMAND_LED_4			123

/*#define __PROTOCOL_COMMAND_MOTOR*/


/*###############################################################*/
#define __UART_PROTOCOL_RESET_STATE_1_CHAR		0x35
#define __UART_PROTOCOL_RESET_STATE_2_CHAR		0x36

#define __UART_PROTOCOL_RESET_STATE_1_LENGTH		9
#define __UART_PROTOCOL_RESET_STATE_2_LENGTH		18
/*###############################################################*/

#define __PROTOCOL_STATE_COMMAND_INCOMLETE		1
#define __PROTOCOL_STATE_COMMAND_COMPLETE		2
#define __PROTOCOL_STATE_COMMAND_INVALID		3
#define __PROTOCOL_STATE_COMMAND_VALID			4
#define __PROTOCOL_STATE_CONNECTION_RESET		5

#endif
