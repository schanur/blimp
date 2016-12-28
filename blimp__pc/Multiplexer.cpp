#ifndef __MULTIPLEXER_CPP__
#define __MULTIPLEXER_CPP__

#include "Multiplexer.h"


Multiplexer :: Multiplexer (string sDeviceToOpen) 
{
	serConnection = new SerialConnection (sDeviceToOpen);
}

Multiplexer :: ~Multiplexer ()
{
	delete serConnection;
}

void Multiplexer :: addChar (const char cChar)
{
	char foo = cChar;
	foo++;
}

void Multiplexer :: send (uint8_t uiDevNumber, char *cpDataToSend, uint16_t uiMessageLength)
{
	if (uiMessageLength > __MULTIPLEXER_MAX_WORD_LENGTH) {
		cerr << "error: Multiplexer :: sendData (uint8_t, uint8_t[], uint8_t):"
				<< endl << "  message too long." << endl;
	}

	serConnection->sendChar(uiDevNumber);
	//serConnection.sendChar
	uint8_t uiMessagePosition = 0;
	while (uiMessagePosition < uiMessageLength) {
		serConnection->sendChar(cpDataToSend[uiMessagePosition++]);
	}
}

uint8_t Multiplexer :: receive () {
	throw exception ();
	return (0);
}




#endif
