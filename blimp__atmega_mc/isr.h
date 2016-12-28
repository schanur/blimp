#ifndef __ISR_H__
#define __ISR_H__

#include <avr/interrupt.h>

#include "defines.h"
#include <stdint.h>

//#include "global_vars.c"
//#include "platform_specifics_atmega.h"
//#include "io/ports.c"
//#include "io/uart_buffer.c"
//#include "../shared_source/uart_protocol_handler.c"

//#include "io/ring_buffer.c"
//#include "io/print_dtype.c"

#define __ISR_USE_UART
#define __ISR_USE_STEPPER

#ifdef __ISR_USE_UART
	#include "io/uart_buffer.h"
#endif
#ifdef __ISR_USE_STEPPER
	#include "devices/stepper_motor.h"
	extern struct stepper caStepper[4];
#endif

extern uint8_t uiGlobalError;

//uint8_t uiTimerDiv;

void registerAllInterrupts();

#ifdef __ISR_USE_UART
ISR (USART_RX_vect);
ISR (USART_UDRE_vect);
#endif

ISR (TIMER2_OVF_vect);

///FIXME: die anderen Funktionen auch anlegen

#endif
