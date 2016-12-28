#ifndef __DATA_EXCHANGE_H__
#define __DATA_EXCHANGE_H__

#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
//#include <inttypes.h>
#include <stdint.h>
#include <pthread.h>

#include "defines.h"
#include "Exceptions.cpp"
#include "IPCDataStructures.cpp"


using namespace std;


class IPCControl
{
	public:
	pthread_mutex_t dataLock;
	uint16_t uiRefCount;
	uint16_t uiLockCount;
};

//#####################################################################

template <class IPCData>
class DataExchange
{
	private: int32_t iKey;
	private: int32_t iSharedMemID;
	private: void *vpDataAddress;
	private: IPCControl *cpSharedControl;
	private: IPCData *cpSharedData;
	private: bool bIsCreator;

	public: DataExchange (int32_t iMagicKey, uint8_t uiMode);
	public: ~DataExchange ();

	private: void allocateSharedMemory (uint8_t uiMode);
	private: void attachSharedMemory ();
	private: void detachSharedMemory ();
	private: void deleteSharedMemory ();
	private: void initSharedMemoryData ();

	public: IPCData* getSharedDataAddress();
	public: void lock ();
	public: void unlock ();

	//public: void write();
	//public: void* read();
};

#endif
