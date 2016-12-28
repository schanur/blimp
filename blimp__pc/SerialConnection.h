#ifndef __SERIAL_CONNECTION_H__
#define __SERIAL_CONNECTION_H__

//#define _POSIX_C_SOURCE 199309
//#include <sys/time.h>


#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

#include <sys/stat.h>

#include <iostream>
//#include <string>
#include <fstream>
#include <queue>

#include "defines.h"
#include "Exceptions.cpp"

//FIXME:
#define __ERROR 1
#define __SUCCESS 0

#define __SER_READ 1
#define __SER_WRITE (1 << 1)

#define __SER_THREAD_COMMAND__END_THREAD 		5
#define __SER_THREAD_COMMAND__SEND_QUEUE_FILLED 	6


using namespace std;

class SerialConnectionThreadData
{
	private: pthread_mutex_t dataLock;
	
	public: queue<char> cQueue;


	public: SerialConnectionThreadData ();

	public: void lock ();
	public: void unlock ();
};

class SerialConnectionData
{
	public: uint32_t uiBaudrate;
	public: uint32_t uiOptions;
	public: string sDeviceName;
	public: SerialConnectionThreadData *receive;
	public: SerialConnectionThreadData *send;
	public: int fdThreadControlRead;
	public: SerialConnectionData ();
	public: ~SerialConnectionData ();
};

void readCharFromSerialConn (int fdRead, SerialConnectionData *cSerConData);
void writeCharToSerialConn (int fdWrite, SerialConnectionData *cSerConData);
void *serialConnDevRWThread (void *ptr);

class SerialConnection
{
	private: SerialConnectionData *cSerConData;
	private: pthread_t serRWThread;
	private: int fdThreadControlWrite;
	public: SerialConnection (string sDeviceToOpen, uint32_t uiBaudrate, uint32_t uiOptions);
	public: ~SerialConnection ();
	

	private: void initConnection (uint32_t uiOptions);

	/// FIXME: etwas unschoenes interface...
	public: int8_t getChar (char *uiReceivedChar);
	public: int8_t putChar (const char iCharToSend);
};


#endif
