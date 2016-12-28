#ifndef __MESSAGEQUEUECLIENT_H__
#define __MESSAGEQUEUECLIENT_H__

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>

#include "platform_specifics_blimp_pc.h"
#include "msq_header.h"
#include "MessageSerialisation.cpp"
#include "SerialisedMessage.h"


using namespace std;

int ende;

class MessageQueueClient {
	
	private:
	int server_id, client_id;
	int res;
	client2server c2s;
	server2client s2c;
	int ConnectToMessageQueue (key_t key, int flag);
	struct msqid_ds msq;
	public:
	MessageQueueClient();
	~MessageQueueClient();
	int StartMessageQueueClient (key_t msqkey);
	int SendMessage (sSerialisedMsg cMsgToSend);
	//int SendMessage (char *sToSend, int ilenght);
	int ReceiveMessage (sSerialisedMsg &sToRec);
	void EndMessageQueueClient ();


};

#endif
