#ifndef __PORTS_C__
#define __PORTS_C__

#include "ports.h"
//#include "io.h"

/*void port_direction (uint8_t port_no, uint8_t data_direction)
{
	if (port_no == __PORT_B__) {
		DDRB |= data_direction;
	} else if (port_no == __PORT_C__) {
		DDRC |= data_direction; 
	} else if (port_no == __PORT_D__) {
		DDRD |= data_direction;
	} else {
		panic ();
	}
} */

void set_port_direction (uint8_t port_no, uint8_t bit_pos, uint8_t io_value)
{
	
	if (io_value == __INPUT)
	{
		uint8_t bitmask = (1 << (7 - bit_pos)) ^ 0xff;
		if (port_no == __PORT_B) {
			DDRB &= bitmask;
		} else if (port_no == __PORT_C) {
			DDRC &= bitmask; 
		} else if (port_no == __PORT_D) {
			DDRD &= bitmask;
		} else {
			/*panic ();*/
		}
	} else if (io_value == __OUTPUT)
	{
		/*uint8_t bitmask = 1 << (7 - bit_pos);*/
		if (port_no == __PORT_B) {
			DDRB |= (1 << PB2);
		} else if (port_no == __PORT_C) {
			DDRC |= (1 << PC3 | 1 << PC2);
		} else if (port_no == __PORT_D) {
			DDRD |=  (1 << PD3);
		} else {
			/*panic ();*/
		}
	} else 
	{
		/*panic ();*/
	}
}

void port_init ()
{
/*//	DDRB |=  (1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB3 | 1 << PB4 | 1 << PB5 );
//	DDRC |=  (1 << PC0 | 1 << PC1 | 1 << PC2 | 1 << PC3);
//	DDRD |=  (1 << PD3 | 1 << PD2 | 1 << PD4 | 1 << PD5 | 1 << PD6 | 1 << PD7 );*/

	DDRB |=  (1 << PB0 | 1 << PB1 | 1 << PB3 | 1 << PB5 );
	DDRC |=  (1 << PC0 | 1 << PC1 | 1 << PC2 | 1 << PC3);
	DDRD |=  (1 << PD3 | 1 << PD2 | 1 << PD6 | 1 << PD7 );
/*	// TEST LED 
//	set_port_direction (__PORT_D__, 2, __OUTPUT__);
//	port_direction (__PORT_D__, (1 << 5));
	//Ports für Motoren
//	set_port_direction (__PORT_D__, 3, __OUTPUT__);
//	set_port_direction (__PORT_D__, 6, __OUTPUT__);
//	set_port_direction (__PORT_D__, 7, __OUTPUT__);
	
//	set_port_direction (__PORT_B__, 0, __OUTPUT__); // will nicht
//	set_port_direction (__PORT_B__, 3, __OUTPUT__);
//	set_port_direction (__PORT_B__, 5, __OUTPUT__); // will nicht

//	set_port_direction (__PORT_C__, 3, __OUTPUT__);
//	set_port_direction (__PORT_C__, 2, __OUTPUT__);*/

	
}

void setPort (uint8_t port_no, uint8_t bit_pos, uint8_t io_value)
{
	switch (port_no) {
		/*case (__PORT_A): {
			switch (io_value) {
				case (__ON): {
					PORTA = PORTA | (1 << bit_pos);
					break;
				}
				case (__OFF): {
					PORTA = PORTA & (~(1 << bit_pos));
					break;
				}
				case (__SWITCH): {
					PORTA = PORTA ^ (1 << bit_pos);
					break;
				}
				default: {
					panic ();
					break;
				}
			}
			break;
		}*/
		case (__PORT_B): {
			switch (io_value) {
				case (__ON): {
					PORTB = PORTB | (1 << bit_pos);
					break;
				}
				case (__OFF): {
					PORTB = PORTB & (~(1 << bit_pos));
					break;
				}
				case (__SWITCH): {
					PORTB = PORTB ^ (1 << bit_pos);
					break;
				}
				default: {
					/*panic ();*/
					break;
				}
			}
			break;
		}
		case (__PORT_C): {
			switch (io_value) {
				case (__ON): {
					PORTC = PORTC | (1 << bit_pos);
					break;
				}
				case (__OFF): {
					PORTC = PORTC & (~(1 << bit_pos));
					break;
				}
				case (__SWITCH): {
					PORTC = PORTC ^ (1 << bit_pos);
					break;
				}
				default: {
					/*panic ();*/
					break;
				}
			}
			break;
		}
		case (__PORT_D): {
			switch (io_value) {
				case (__ON): {
					PORTD = PORTD | (1 << bit_pos);
					break;
				}
				case (__OFF): {
					PORTD = PORTD & (~(1 << bit_pos));
					break;
				}
				case (__SWITCH): {
					PORTD = PORTD ^ (1 << bit_pos);
					break;
				}
				default: {
					/*panic ();*/
					break;
				}
			}
			break;
		}
		default: {
			/*panic ();*/
		}
	}
}

#endif
