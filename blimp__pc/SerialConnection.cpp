#ifndef __SERIAL_CONNECTION_CPP__
#define __SERIAL_CONNECTION_CPP__

#include "SerialConnection.h"

using namespace std;
 
void readCharFromSerialConn (int fdRead, SerialConnectionData *cSerConData) {
	char ch, iRet;

	//cerr << "Zeichen Empfangen." << endl;
	iRet = read (fdRead, &ch, 1);
	if (iRet > 1) {
		cerr << ("error: \"read ()\"got more than one character.") << endl;
	} else if (iRet == 1) {
		//cerr << ch << endl;
	} 
	cSerConData->receive->lock ();
	/// FIXME: define
	if (cSerConData->receive->cQueue.size () >= 2048) {
		cerr << "warning: receiveQueue size: " << cSerConData->receive->cQueue.size () << endl;
	}
	cSerConData->receive->cQueue.push (ch);
	cSerConData->receive->unlock ();
	
		
}

void writeCharToSerialConn (int fdWrite, SerialConnectionData *cSerConData) {
	char ch, iRet;

	cSerConData->send->lock ();
	if (cSerConData->send->cQueue.size () > 0) {
		ch = cSerConData->send->cQueue.front();
		cSerConData->send->cQueue.pop();
		iRet = write (fdWrite, &ch, 1);			
	}
	cSerConData->send->unlock ();
}

void *serialConnDevRW (void *ptr)
{
	cerr << "serialConnDevRW (): start" << endl;
	SerialConnectionData *cSerConData = (SerialConnectionData*) ptr;

	int iRet, fdRead, fdWrite, fdControl = cSerConData->fdThreadControlRead;
	uint8_t uiFdError, uiCheckWriteFd;
	int fdSelectMax;
	fd_set cReadSet, cWriteSet;
	char ch;

	uint64_t tmpFd1Count = 0, tmpFd2Count = 0, tmpFd3Count = 0;

	fdRead = open (cSerConData->sDeviceName.c_str (), O_RDONLY);
	fdWrite = open (cSerConData->sDeviceName.c_str (), O_WRONLY);
	if (fdRead < fdWrite) {fdSelectMax = fdWrite;} else {fdSelectMax = fdRead;}
	if (fdControl > fdSelectMax) {fdSelectMax = fdControl;}
	fdSelectMax++;

	while (1) {
		uiCheckWriteFd = 0;
		FD_ZERO (&cReadSet);
		FD_ZERO (&cWriteSet);
		FD_SET (fdRead, &cReadSet);
		FD_SET (fdControl, &cReadSet);
		cSerConData->send->lock ();
		if (cSerConData->send->cQueue.size () > 0) {
			uiCheckWriteFd = 1;
		}
		cSerConData->send->unlock ();
			
		if (uiCheckWriteFd == 1) {
			FD_SET (fdWrite, &cWriteSet);
			select (fdSelectMax, &cReadSet, &cWriteSet, NULL, NULL);
		} else {
			select (fdSelectMax, &cReadSet, NULL, NULL, NULL);
		}
		
		uiFdError = 1;
		
		if (FD_ISSET (fdControl, &cReadSet)) {
			iRet = read (fdControl, &ch, 1);
			switch (ch) {
				case __SER_THREAD_COMMAND__SEND_QUEUE_FILLED: {
					writeCharToSerialConn (fdWrite, cSerConData);
					++tmpFd3Count;
					break;
				}
				case __SER_THREAD_COMMAND__END_THREAD: {
					/// Beende den Thread.
					cerr << "serialConnDevRW (): end" << endl;
					cerr << "fd1Count: " << tmpFd1Count << endl;
					cerr << "fd2Count: " << tmpFd2Count << endl;
					cerr << "fd3Count: " << tmpFd3Count << endl;
					pthread_exit ((void*) 1);
					break;
				}
				default: {
					cerr << "error: serialConnDevRW (): Thread got unknown command." << endl;
					break;
				}
			}
			uiFdError = 0;
		} 
		if (FD_ISSET (fdRead, &cReadSet)) {
			readCharFromSerialConn (fdRead, cSerConData);
			uiFdError = 0;
			++tmpFd1Count;
		}
		if (uiCheckWriteFd == 1) {
			if (FD_ISSET (fdWrite, &cWriteSet)) {
				writeCharToSerialConn (fdWrite, cSerConData);
				uiFdError = 0;
				++tmpFd2Count;
			}
		}

		if (uiFdError == 1) {
			cerr << "error: serialConnDevRW (): unexpected select response." << endl; 
		}
	}
}

//#####################################################################

SerialConnectionThreadData :: SerialConnectionThreadData ()
{
	pthread_mutex_init (&dataLock, NULL);
}

void SerialConnectionThreadData :: lock ()
{
	pthread_mutex_lock (&dataLock);
}

void SerialConnectionThreadData :: unlock ()
{
	pthread_mutex_unlock (&dataLock);
	
}

//#####################################################################

SerialConnectionData :: SerialConnectionData ()
{
	receive = new SerialConnectionThreadData ();
	send = new SerialConnectionThreadData ();
}

SerialConnectionData :: ~SerialConnectionData ()
{
	delete receive;
	delete send;
}

//#####################################################################

SerialConnection :: SerialConnection (string sDeviceToOpen, uint32_t uiBaudrate, uint32_t uiOptions)
{
	cSerConData = new SerialConnectionData ();
	cSerConData->sDeviceName = sDeviceToOpen;
	cSerConData->uiBaudrate = uiBaudrate;
	cSerConData->uiOptions = uiOptions;
	initConnection (uiOptions);
}

SerialConnection :: ~SerialConnection ()
{
	char iEndThread = __SER_THREAD_COMMAND__END_THREAD ;
	write (fdThreadControlWrite, &iEndThread, 1);
	
	void *vpThreadRetVal;
	pthread_join (serRWThread, &vpThreadRetVal);
	if (vpThreadRetVal == 0) {
		cerr << "Fehler in Modul Roetzpoetz" << endl;
	} else {
		cerr << "Thread hat sich beendet" << endl;
	}

	delete cSerConData;
}

void SerialConnection :: initConnection (uint32_t uiOptions)
{
	int iret1;//, iret2;
	int fdPipe[2];
	if (pipe (fdPipe) == -1) {
		cerr << "error: cannot create pipe" << endl;
		exit (1);
	}
	cSerConData->fdThreadControlRead = fdPipe[0];
	fdThreadControlWrite = fdPipe[1];
	iret1 = pthread_create(&serRWThread, NULL, serialConnDevRW, (void*) cSerConData);
}

int8_t SerialConnection :: getChar (char *iReceivedChar)
{
	struct timespec t1;
	t1.tv_sec = 0;
	t1.tv_nsec = 1;
	
	cSerConData->receive->lock ();
	if (cSerConData->receive->cQueue.empty () == false) {
		*iReceivedChar = cSerConData->receive->cQueue.front ();
		cSerConData->receive->cQueue.pop ();
		cSerConData->receive->unlock ();
		return (__SUCCESS);
	} else {
		cSerConData->receive->unlock ();
		return (__ERROR);
	}
}

int8_t SerialConnection :: putChar (const char iCharToSend)
{
	cSerConData->send->lock ();
	/// TODO: definen;
	if (cSerConData->send->cQueue.size () >= 32) {
		cSerConData->send->unlock ();
		return (__ERROR);
	} else {
		cSerConData->send->cQueue.push (iCharToSend);
		//cerr << "s" << iCharToSend;
		cSerConData->send->unlock ();
		char iEndThread = __SER_THREAD_COMMAND__SEND_QUEUE_FILLED;
		write (fdThreadControlWrite, &iEndThread, 1);
		return (__SUCCESS);		
	}
}

#endif
