#include <stdlib.h>
#include <avr/io.h>
#include <stdint.h>
//#include <stdio.h>

#include "platform_specifics_atmega.h"




/// TODO: includes korrigieren... in allen dateien
#include "defines.h"
//#include "global_vars.c"

/// Hardware Interfaces
#include "io/ports.h"
//#include "io.c"

#include "io/uart.h"
//#include "io/uart_buffer.c"
//#include "io/twimaster.c"
#include "io/i2c.h"

//struct uartBuffer strUARTLink;

/// CPU Wait Funktionen
#include "timing.h"

/// Software Protokolle
#include "devices/stepper_motor.h"
//uint8_t uiStepperWatch[4];

#include "../shared_source/uart_protocol_handler.h"
#include "io/protocol_packet_handler.h"

/// Interrup Handling
#include "isr.h"

/// Debugging
#include "../shared_source/print_dtype.h"
#include "../shared_source/debug.h"

uint8_t uiGlobalError;
struct stepper caStepper[4];

int main (void)
{
	setPort (__PORT_C, 3, __ON);
	//struct stepper* blah = &caStepper[__STEPPER_SENSOR_HORIZONTAL];
	//blah->uiSpeed = 2;

	wait_ms(300);
	//initGlobalVars ();
	struct uartBuffer strPCLink;
	initUartBuffer (&strPCLink, 64, 64);
	initUart (&strPCLink);
	
	registerAllInterrupts();
	sei ();

	while (uartPutString (&strPCLink, "\n\ninit ports...\t\t ") == __ERROR) {wait_ms(1);}
	wait_ms(300);
	port_init ();
	while (uartPutString (&strPCLink, "done\ninit i2c bus...\t\t ") == __ERROR) {wait_ms(1);}
	i2c_init ();
	wait_ms(300);
	while (uartPutString (&strPCLink, "done\ntesting led...\t\t ") == __ERROR) {wait_ms(1);}
	setPort (__PORT_B, 1, __SWITCH);
	wait_ms(1000);
	setPort (__PORT_B, 1, __SWITCH);
	wait_ms(1000);
	setPort (__PORT_B, 1, __SWITCH);
	while (uartPutString (&strPCLink, "done\ninit protocol handler... ") == __ERROR) {wait_ms(1);}
	wait_ms(1000);
	//while (1) {}
	uartProtocolInitProtocolHandler (__UART_SEQENCE_NO_BEGIN, __UART_SEQENCE_NO_END);
	while (uartPutString (&strPCLink, "done\ninit steppers...\t\t") == __ERROR) {}
	wait_ms(1000);
	//initStepper (&caStepper[__STEPPER_SENSOR_HORIZONTAL], __STEPPER_SENSOR_HORIZONTAL, __UNIPOLAR_FULLSTEP);
	//initStepper (&caStepper[__STEPPER_SENSOR_VERTICAL], __STEPPER_SENSOR_VERTICAL, __UNIPOLAR_FULLSTEP);
	//initStepper (&caStepper[__STEPPER_ENGINE], __STEPPER_ENGINE, __UNIPOLAR_FULLSTEP);
	//setStepperSpeed (&engine, 100);
	////while (uartPutString (&strUARTLink, "done\n") == __ERROR) {}
//********************

	while (1) {

		/*if (uartProtocolDoHandlerStep () == __PROTOCOL_STATE_COMMAND_VALID) {
			if (uartProtocolHandlePacket () == __ERROR) {
				protocol.uiConnectionState = __PROTOCOL_STATE_CONNECTION_RESET;
			}
		}*/

	}
	return (0);
}

