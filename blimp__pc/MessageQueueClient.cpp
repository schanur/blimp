#ifndef __MESSAGEQUEUECLIENT_CPP__
#define __MESSAGEQUEUECLIENT_CPP__

#include "MessageQueueClient.h"

/* Der Client will sich den beenden */
static void ShutdownClient (int signr) {
	ende = 0;
}

MessageQueueClient :: MessageQueueClient () {

	ende = 1;
}

MessageQueueClient :: ~MessageQueueClient () {
	msgctl(client_id, IPC_RMID, &msq);
}

int MessageQueueClient :: ConnectToMessageQueue (key_t key, int flag) {
	int res;
	res = msgget (key, flag);
	if (res < 1) {
		cerr << "Clientfehler beim Einrichten der Message Queues...ERROR: " << endl;
	/*	switch (errno) {
			case EACCES :{
				cerr << " EACCES" << endl;
				break;
			}
			case EEXIST :{
				cerr << " EEXIST" << endl;
				break;
			}
			case ENOENT :{
				cerr << " ENOENT" << endl;
				break;
			}
			case ENOSPC :{
				cerr << " ENOSPC" << endl;
				break;
			}
		}
		return -1;*/
	}
	return res;
}


int MessageQueueClient :: StartMessageQueueClient (key_t msqkey) {
	/// Signalhandler für STRG+C  einrichten
	signal (SIGINT, ShutdownClient);

	/// Eine Message Queues zum Server 
	server_id = ConnectToMessageQueue (msqkey, 0);
	if (server_id < 0) {
		return EXIT_FAILURE;
	}
	/// Eine Message Queues für den Client 
	client_id = ConnectToMessageQueue (IPC_PRIVATE, PERM | IPC_CREAT | IPC_EXCL);
	if (client_id < 0){
		return EXIT_FAILURE;
	}
	/// Eine Nachricht an den Server versenden
	c2s.prioritaet = client_id;
	sprintf (c2s.message, "%d", client_id);
	res = msgsnd (server_id, &c2s, MSG_LEN, 0);
	if (res == -1) {
		cerr << "Konnte keine Testnachricht versenden" << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


int MessageQueueClient :: SendMessage (sSerialisedMsg cMsgToSend) {
	memset((void*)c2s.message, 0, 15);
	memcpy (c2s.message, cMsgToSend.text, 8);
	c2s.prioritaet = client_id;
	cerr << "Client: " << client_id << " versende: " << c2s.message << endl;
	//printf("in decimal: %d %d %d %d %d \n",c2s.message[0],c2s.message[1],c2s.message[2],c2s.message[3],c2s.message[4]);
	res = msgsnd (server_id, &c2s, cMsgToSend.text[__PACKET_LENGTH_POS] + __HEADER_SIZE, 0);
	if (res == -1) {
		cerr << "Konnte Nachricht :" << c2s.message << " nicht versenden!" << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


int MessageQueueClient :: ReceiveMessage (sSerialisedMsg &sToRec) {
	/// empfangen von Nachrichten ohne zu blockieren
	//res = msgrcv (client_id, &s2c, MSG_LEN, 0, IPC_NOWAIT);
	/// empfangen von Nachrichten und blockieren
	msgrcv (client_id, &s2c, MSG_LEN, 0, 0);
	if (res != -1) {
		if (s2c.prioritaet == client_id) {
			cerr << "Packet empfangen" << endl;
			/// Das Gesamte Paket kopieren
			memcpy (sToRec.text, s2c.message, __HEADER_SIZE +
					 __MAX_PAYLOAD_SIZE + 
					__CHECKSUM_SIZE);
			//printf ("(%s) nachricht erhalten Queues-ID: %ld\n", s2c.message, s2c.prioritaet);
		} else {
			printf ("(%s) falsche: %ld\n", s2c.message, s2c.prioritaet);
		}
	}
	return (__SUCCESS);
}


void MessageQueueClient :: EndMessageQueueClient () {
   	/// STRG+C also das Signal SIGINT wurde ausgelöst
	c2s.prioritaet = 1;
	sprintf (c2s.message, "%d", client_id);
	res = msgsnd (server_id, &c2s, MSG_LEN, 0);
	if (res == -1) {
	cerr << "Konnte Nachricht nicht versenden " << endl;
	}
	ende = 0;
}


#endif
