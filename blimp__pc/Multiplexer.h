#ifndef __MULTIPLEXER_H__
#define __MULTIPLEXER_H__

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
//#include <fstream>
//#include <fcntl.h>
#include <stdint.h>

#include "defines.h"
#include "SerialConnection.cpp"

using namespace std;






class Multiplexer
{
	
	private: uint8_t uiCachePosition;
	private: uint8_t uiInDataMode;
	private: uint8_t uiProtocolDevNumber;
	private: SerialConnection *serConnection;

	public: Multiplexer (string sDeviceToOpen);
	public: ~Multiplexer ();
	
	private: void addChar (const char cChar);
	private: void addString ();

	public: void send (uint8_t uiDevNumber, char *ipDataToSend, uint16_t uiMessageLength);
    	public: uint8_t receive ();

    //public: 

};

#endif
