#ifndef __PORTS_H__
#define __PORTS_H__

#include <stdint.h>
#include <avr/io.h>

#define __PORT_A 	0
#define __PORT_B 	1
#define __PORT_C 	2
#define __PORT_D 	3

#define __OUTPUT 	1
#define __INPUT 	0

#define __ON 		1
#define __OFF		0
#define __SWITCH	2


/*void port_direction (uint8_t port_no, uint8_t data_direction);*/
void set_port_direction (uint8_t port_no, uint8_t bit_pos, uint8_t io_value);
void port_init ();

void setPort (uint8_t port_no, uint8_t bit_pos, uint8_t io_value);

#endif
