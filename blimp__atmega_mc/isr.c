#ifndef __ISR_C__
#define __ISR_C__

#include "isr.h"

void registerAllInterrupts()
{
/* Timer 2 starten */
	TCCR2B = ( 1 << CS00 ) | (1 << CS01) | (1 << CS02);
	TCNT2 = 1;
	TIMSK2 |= ( 1 << TOIE2 );
/* UART starten */
	UCSR0B |= (1 << RXCIE0);

	/*////uint8_t i;*/
	/*for (i = 0; i < 4; i++) {
		uiStepperWatch[i] = 0xff;
	}
	uiStepperWatch[__STEPPER_SENSOR_HORIZONTAL] = 0;
	uiStepperWatch[__STEPPER_SENSOR_VERTICAL] = 1;*/
}

#ifdef __UART_H__
ISR (USART_RX_vect)  /* USART_RXC */
{
	if (!(UCSR0A & (1 << RXC0))) {
		/*//g.uiOccuredErrorCode = __ERROR_UNKNOWN;*/
		return;
	}
	const char cReceivedChar = UDR0;

	if (writeToBuffer (&strPCLink.receive, cReceivedChar) == __ERROR) {
		/*//g.uiOccuredErrorCode = __ERROR_RECEIVE_BUFFER_OVERFLOW;*/
	}
	if (protocol.uiUARTWatchdog < 100) {
		protocol.uiUARTWatchdog = 0;
	}
	
}

ISR (USART_UDRE_vect)
{
	if (charsInBuffer (&strUARTLink.send) > 0) {
		char uiCharToSend;
		readFromBuffer (&strUARTLink.send, &uiCharToSend);
		UDR0 = uiCharToSend;
		if (charsInBuffer (&strUARTLink.send) == 0) {
			UCSR0B &= ~(1 << UDRIE0);
		}
	} else {
		UCSR0B &= ~(1 << UDRIE0);
	}
}
#endif


/* Timer 2 */
ISR (TIMER2_OVF_vect)
{
/* TODO wenn PC Code fertig reparieren */
	/*uint8_t i;*/
	/*for (i = 0; i < 4; i++) {
		if (uiStepperWatch[i] != 0xff) {
			if (uiStepperWatch[i] != 0) {
				uiStepperWatch[i]--;
			} else {
				uiStepperWatch[i] = caStepper[i].uiSpeed;
				doStepperStep (&caStepper[i]);
			}
			
		}
	}*/

	#ifdef __UART_H__
	protocol.uiUARTWatchdog++;
	if (protocol.uiUARTWatchdog >= 50) {
		/*doStepperStep (&caStepper[__STEPPER_ENGINE]);*/
		setPort (__PORT_B, 1, __SWITCH);
		protocol.uiUARTWatchdog = 0;
	}
	#endif
/*//	if (protocol.uiUARTWatchdog >= 50) {
	//if (protocol.uiUARTWatchdog >= 2000) {
  		//PORTD = PORTD ^ 0xff;
		//PORTB = PORTB ^ (1 << PB1);
		//setPort (__PORT_B, 1, __SWITCH);
		/// FIXME: gehoert hier auch nicht hin
		
		//PORTC = PORTC ^ 0xff;
		//PORTD = PORTD ^ (1 << PD2);
//		protocol.uiUARTWatchdog = 0; ///FIXME: zur Reparatur raus
	//	if (protocol.strUARTProtocol.uiProtocolConnectionState ==  __PROTOCOL_STATE_CONNECTION_RESET) {

//	}	
	//protocol.uiUARTWatchdog = 0;
	//} ///FIXME: wie der rein bei Reperatur*/
/*else if (protocol.uiUARTWatchdog >= 1000) {
		protocol.strUARTProtocol.uiProtocolConnectionState =  __PROTOCOL_STATE_CONNECTION_RESET;
	}*/
	/*PORTB = PORTB ^ (1 << PB3);*/
}

#endif
