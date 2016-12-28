#ifndef __MESSAGEQUEUESERVER_H__
#define __MESSAGEQUEUESERVER_H__


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <map>
#include <sys/time.h>

/// dieser Block wird von uart_protocol_handler benoetigt
#define UART_RECEIVE_NONBLOCK ser->getChar (&uiCharFromBuffer)
#define UART_SEND_NONBLOCK ser->putChar (&uiReceivedChar)
#include "SerialConnection.cpp"
SerialConnection *ser;


//#include "Debug.cpp"
#include "msq_header.h"
#include "platform_specifics_blimp_pc.h"
#include "../shared_source/protocolNumbers.h"
#include "../shared_source/protocolPackets.h"
#include "../shared_source/uart_protocol_handler.c"
#include "SerialisedMessage.cpp"
#include "StringDump.cpp"

///FIXME
#include <execinfo.h>

using namespace std;


int endMQServer;



class MessageQueueServer
{
	private:
	StringDump *strD;
	map<uint8_t, int> mClientRequestTable;
	map<uint8_t, int> :: iterator iteratorCRTable;
	int server_id;
	uint8_t uiRecSeqNo;
	uint8_t uiSendSeqNo;
	struct msqid_ds msq;	
	int SetupMessageQueue( key_t key, int flag );
	void SendToClient( const char *str, int p );
	void PutInMap(int lastpid, uint8_t uiSeqNo);
	void FindMatchingClient(uint8_t uiSeqNoToFind);
	void SendSerial(int lastpid,char *cToSend);
	int ReceiveSerial();

	
	public:
	MessageQueueServer ();
	~MessageQueueServer ();
	int RunMessageQueueServer (key_t msqkey);
};




#endif
