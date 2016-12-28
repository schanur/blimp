#ifndef __I2C_C__
#define __I2C_C__
#include "i2c.h"

/*************************************************************************
 Liest vom I2C Bus 
INPUT: 	device = welches Gerät 
	byte = welches Byte des Gerätes
RETURN: Gelesenes Zeichen
*************************************************************************/  

uint8_t readFromI2C (uint8_t device, uint8_t byte)
{
	///FIXME prüfen ob stop das gerät die werte überschreiben lässt bie 16
	/// Bit werten (Beide Probleme)
	uint8_t ret_val;//= i2c_start (device + I2C_READ);
    	//if (ret_val) 	{
	//	while (uartPutString ("Fehler beim Lesen vom Gerät\n") == __ERROR) {}
		//panic ();
	//} else {
		(void) i2c_start (device + I2C_WRITE);
		i2c_write(byte);
		(void) i2c_rep_start(device + I2C_READ);
	    	//ret_val = i2c_read(1);
		ret_val = i2c_readNak();
		i2c_stop ();
	//}
	return (ret_val);
}

/*************************************************************************
 Schreibt ein Zeichen auf den I2C Bus
INPUT: 	device = welches Gerät 
	byte = welches Byte des Gerätes
	cchar = zu schreibendes zeichen
*************************************************************************/  
void writeToI2C (uint8_t device, uint8_t byte, unsigned char cchar)
{
	i2c_start_wait(device+I2C_WRITE);     // set device address and write mode
	i2c_write(byte);                        // write address = 5
	i2c_write(cchar);                        // write value 0x75 to EEPROM
	i2c_stop();                             // set stop conditon = release bus



/*	uint8_t ret_val = i2c_start (device + I2C_READ);
    	if (ret_val) 	{
		uartPutString ("Fehler beim Lesen vom Gerät\n");
		panic ();
	} else {
		(void) i2c_start (device + I2C_WRITE);
		i2c_write(byte);
		(void) i2c_rep_start(device + I2C_WRITE);
	    	i2c_write(cchar);
		i2c_stop ();
	}
*/
}

#endif
