#ifndef __I2C_H__
#define __I2C_H__
#include <inttypes.h>
#include <compat/twi.h>

#include "twimaster.c"
#include "i2cmaster.h"

/*************************************************************************
 Liest vom I2C Bus 
INPUT: 	device = welches Gerät 
	byte = welches Byte des Gerätes
RETURN: Gelesenes Zeichen
*************************************************************************/  

uint8_t readFromI2C (uint8_t device, uint8_t byte);

/*************************************************************************
 Schreibt ein Zeichen auf den I2C Bus
INPUT: 	device = welches Gerät 
	byte = welches Byte des Gerätes
	cchar = zu schreibendes zeichen
*************************************************************************/  
void writeToI2C (uint8_t device, uint8_t byte, unsigned char cchar);

#endif
