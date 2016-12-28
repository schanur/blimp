#ifndef __DATA_EXCHANGE_CPP__
#define __DATA_EXCHANGE_CPP__

#include "DataExchange.h"



template<class IPCData> DataExchange <IPCData>:: DataExchange (int32_t iMagicKey, uint8_t uiMode)
{
	iKey = iMagicKey;
	allocateSharedMemory (uiMode);
	attachSharedMemory ();
	//pthread_mutex_init(&DataExchange::mutex1, NULL);
}

template<class IPCData> DataExchange <IPCData> :: ~DataExchange()
{
	detachSharedMemory ();
	deleteSharedMemory ();
}

template<class IPCData> void DataExchange <IPCData> :: allocateSharedMemory (uint8_t uiMode)
{
	if (uiMode == __DATA_EXCHANGE_MODE_CREATE) {
		iSharedMemID = shmget (iKey, sizeof (IPCControl) + sizeof (IPCData), IPC_CREAT | SHM_R | SHM_W);
		
		bIsCreator = true;
	} else if (uiMode == __DATA_EXCHANGE_MODE_OPEN) {
		iSharedMemID = shmget (iKey, 0, SHM_R | SHM_W);
		bIsCreator = false;
	} else {
		throw exception ();
	}
	if (iSharedMemID == -1) {
		cerr << "error: shmget IPC_CREAT" << endl;
    		throw exception ();
	}
}

template<class IPCData> void DataExchange <IPCData> :: attachSharedMemory ()
{
	vpDataAddress = shmat (iSharedMemID, NULL, 0);
	cpSharedControl = (IPCControl*) vpDataAddress;
	cpSharedData = (IPCData*) ((int8_t *) vpDataAddress + sizeof (IPCControl));
}

template<class IPCData> void DataExchange <IPCData> :: detachSharedMemory ()
{
	if (shmdt (vpDataAddress) != 0) {
		cerr << "error: shmdt" << endl;
		throw exception ();
    	}
}

template<class IPCData> void DataExchange <IPCData> :: deleteSharedMemory ()
{
	if ((shmctl (iSharedMemID, IPC_RMID, NULL)) == -1) {
		cerr << "error: shmctl IPC_RMID" << endl;
		throw exception ();
    	}
}

template<class IPCData> void DataExchange <IPCData> :: initSharedMemoryData ()
{
	pthread_mutex_init (&cpSharedControl->dataLock, NULL);
	lock ();
	cpSharedControl->uiRefCount = 0;
	cpSharedControl->uiLockCount = 0;
	unlock ();
	
}

template<class IPCData> void DataExchange <IPCData> :: lock ()
{
	pthread_mutex_lock (&cpSharedControl->dataLock);
	cpSharedControl->uiLockCount++;
}

template<class IPCData> void DataExchange <IPCData> :: unlock ()
{
	pthread_mutex_unlock (&cpSharedControl->dataLock);
}

template<class IPCData> IPCData* DataExchange <IPCData> :: getSharedDataAddress ()
{
	return (cpSharedData);
}
/*
template<class IPCData> void DataExchange <IPCData> :: write ()
{
	lockSharedData ();
	// *(int *) vpDataAddress = iToWrite;
	cerr << "Speicheraddresse : " << vpDataAddress << endl;
	unlockSharedData ();
}

template<class IPCData> void* DataExchange <IPCData> :: read ()
{
	lockSharedData ();
	cerr << "Speicheraddresse : " << vpDataAddress << endl;
	if (vpDataAddress == NULL) {
		cerr << "und Null ist der scheiss auch noch!!1" << endl;
	}
	unlockSharedData ();
	//return (*(int *) vpDataAddress);
	return (0);
}
*/


#endif
