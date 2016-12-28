#ifndef __COMMAND_QUEUE_CPP__
#define __COMMAND_QUEUE_CPP__

#include "CommandQueue.h"

using namespace std;

CommandQueue :: CommandQueue ()
{
	uiSeqenceNo = 0;
	uiNextSeqNoToSend = 0;
}

int CommandQueue :: PutNewCommandToSend (string sCommandToSend)
{
	if (sCommandToSend.length() > 4) {
		sCommandToSend[1] = uiSeqenceNo;
		iter = mCommandSend.end ();
		mCommandSend.insert(make_pair (uiSeqenceNo, sCommandToSend));
		uiSeqenceNo = (uiSeqenceNo + 1) % 127; 
		if (mCommandSend.size () == 126) {
			cerr << "SEND Queue bei 126" << endl;
			throw exception ();
		}
	} else {
		cerr << "String nicht lang genug !!!!111 elf" << endl;
		throw exception ();
	}
	return (uiSeqenceNo);
}

bool CommandQueue :: PutNewReceivedCommand (string sReceivedCommand)
{
	if (sReceivedCommand.length() > 4) {
		uiRecSeqenceNo = 0;
		iter = mCommandSend.end ();
		uiRecSeqenceNo = sReceivedCommand[1];
		mCommandReceive.insert(make_pair (uiRecSeqenceNo, sReceivedCommand));
		if (mCommandSend.size () == 126) {
			cerr << "RECEIVE Queue bei 126" << endl;
			throw exception ();
		}
		if (DeleteCommandSendQueue (uiRecSeqenceNo)) {
			return (true);
		}
	} else {
		cerr << "String nicht lang genug !!!!111 elf" << endl;
		throw exception ();
	}
	return (false);
}

bool CommandQueue :: GetNextCommandToSend (string &sResponse)
{
	if (!mCommandSend.empty ()) {
		iter = mCommandSend.find (uiNextSeqNoToSend);
		sResponse = iter->second;
		uiNextSeqNoToSend = (uiNextSeqNoToSend + 1) % 127;
		mCommandReceive.erase (iter);
		return (true);
	} 
	return (false);
}

bool CommandQueue :: GetNextReceivedCommand (string &sResponse)
{
	if (!(mCommandReceive.empty())) {
		iter = mCommandReceive.end ();
		iter--;
		sResponse = iter->second;
		mCommandReceive.erase (iter);
		return (true);
	}
	return (false);
}

bool CommandQueue :: GetReceivedCommandSequenceNo (uint32_t iCommandNo, uint8_t &iResponse)
{
	uint32_t i;
	iter = mCommandReceive.begin ();
  	for (i = 0; i == iCommandNo; i++) {
		if (iter == mCommandReceive.end ()) {
    			return (false);
		}
		iter++;
	}
	iResponse = iter->first;
	mCommandReceive.erase (iter);
	return (true);
}

bool CommandQueue :: GetResponse (uint8_t uiRecSeqNo, string &sResponse)
{
	iter = mCommandReceive.find (uiRecSeqNo);
	if (iter != mCommandReceive.end ()) {
		sResponse = iter->second;
		mCommandReceive.erase (iter);
		return (true);
	} else {
		return (false);
	}
}

int CommandQueue :: CommandsReceived ()
{
	return (mCommandReceive.size ());
}

int CommandQueue :: CommandsNotSend ()
{
	return (mCommandSend.size ());
}

bool CommandQueue :: DeleteCommandSendQueue (uint8_t uiRecSeqNo)
{
	iter = mCommandSend.find (uiRecSeqNo);
	if (iter != mCommandReceive.end ()) {
		mCommandReceive.erase (iter);
		return (true);
	} else {
		return (false);
	}
}

#endif

