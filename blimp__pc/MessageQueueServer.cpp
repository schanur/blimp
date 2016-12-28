#ifndef __MESSAGEQUEUESERVER_CPP__
#define __MESSAGEQUEUESERVER_CPP__

#include "MessageQueueServer.h"


using namespace std;

static void shutdownServer (int signr) {
	endMQServer = 0;
}


MessageQueueServer :: MessageQueueServer ()
{
	endMQServer = 1;
	signal (SIGINT, shutdownServer);
	strD = new StringDump ("MQServer");
}

MessageQueueServer :: ~MessageQueueServer ()
{
	msgctl(server_id, IPC_RMID, &msq);
	cerr << "Message Queue kaputt" << endl;
	delete strD;
	cerr << "strD kaputt" << endl;
	delete ser;
	cerr << "ser kaputt" << endl;
}


int MessageQueueServer :: SetupMessageQueue( key_t key, int flag )
{
	
	int res;
	res = msgget (key, flag);
	if( res < 0 ) {
		return -1;
	}
	return res;
}

void MessageQueueServer :: SendToClient( const char *str, int p )
{
   	int res;
   	server2client s2c;
   	s2c.prioritaet = p;
	sprintf(s2c.message,"%s",str);
	res = msgsnd(p, &s2c, MSG_LEN, 0);
}



void MessageQueueServer :: SendSerial(int lastpid, char *cToSend)
{
	//cerr << "sende request an mc" << endl;
	uartProtocolSendRequest (cToSend + __PAYLOAD_START_POS, cToSend[__PACKET_LENGTH_POS], cToSend[__PACKET_TYPE_POS]);
	PutInMap(lastpid, protocol.uiSequenceNoSendPos);
}

// wird nicht verwendet
int MessageQueueServer :: ReceiveSerial(){

	return EXIT_SUCCESS;
}

void MessageQueueServer :: PutInMap(int lastpid, uint8_t uiSeqNo)
{
	mClientRequestTable.insert(make_pair(uiSeqNo,lastpid));
	/// nur Warnung der Fall sollte eigentlich nicht eintreten 
	if (mClientRequestTable.size() > 64) {
		cerr << "Achtung Map größer als 64" << endl;
	}
}

void MessageQueueServer :: FindMatchingClient(uint8_t uiSeqNoToFind)
{
	//cerr << "Suche Client: " << (int) uiSeqNoToFind << endl;
	server2client s2c;
	iteratorCRTable = mClientRequestTable.find(uiSeqNoToFind);
	//cerr << "Iterator: " << iteratorCRTable->second << endl;
	if (iteratorCRTable != mClientRequestTable.end()){
		s2c.prioritaet = iteratorCRTable->second;
		sprintf (s2c.message, "%s", protocol.receive.commandData);
		SendToClient(s2c.message, iteratorCRTable->second);
		/// aus der Map löschen
		mClientRequestTable.erase(iteratorCRTable);
	} else {
		/// tritt nur ein wenn Fehler in Map oder bei MC-Antwort
		char msg[4];
		memcpy (msg, &protocol.receive.commandData + __PAYLOAD_START_POS,  protocol.receive.commandData[__PACKET_LENGTH_POS]);
		cerr << "Empfänger der Nachricht: " << msg << " nicht in Map" << endl;
	}
}

int MessageQueueServer :: RunMessageQueueServer (key_t msqkey)
{
	int res, msgno;
	client2server c2s;
	char puffer[MSG_LEN];
	int client_id, i = 0;
	/// Aufbau der Queue
	server_id = SetupMessageQueue( msqkey, PERM  | IPC_CREAT | IPC_EXCL );
	/// wenn Server nicht richtig beendet wurde die alte Queue löschen
	/// und eine neue anlegen
	if( server_id < 0 ) {
		server_id = SetupMessageQueue( msqkey, PERM  | IPC_CREAT);
		msgctl(server_id, IPC_RMID, &msq);
		server_id = SetupMessageQueue( msqkey, PERM  | IPC_CREAT | IPC_EXCL );
	}
	/// serielle Verbindung starten
	ser = new SerialConnection("/dev/ttyS1", 9600, __SER_READ | __SER_WRITE);
	/// Protokollhandler starten
	uartProtocolInitProtocolHandler(__UART_SEQENCE_NO_BEGIN, __UART_SEQENCE_NO_END);
	
	printf("Message Queue Server läuft ...\n");
	struct timespec cPlanedIdle, cRealIdle;
	cPlanedIdle.tv_sec = 0;
	cPlanedIdle.tv_nsec = 10000;
	while(endMQServer) {
		(void) nanosleep (&cPlanedIdle, &cRealIdle);
		/// Nachricht vom MC empfangen
		memset((void*)&c2s.message, 0, 15);
		res = msgrcv( server_id, &c2s, MSG_LEN, 0, IPC_NOWAIT);
		if( res < 0 ) {
			/// empfangene Nachricht des MC an den entsprechenden Client
			/// weiterreichen	
			if (uartProtocolDoHandlerStep () == __PROTOCOL_STATE_COMMAND_VALID) {
				uiRecSeqNo = protocol.receive.commandData[__SEQUENCE_NO_POS];
				
				/// prüfen ob es eine Antwort oder eine Anfrage des
				/// MC ist
				if ((protocol.receive.commandData[__PACKET_LENGTH_POS] < __HEADER_SIZE) || (protocol.receive.commandData[__PACKET_LENGTH_POS] > __HEADER_SIZE + __MAX_PAYLOAD_SIZE)) {
					cerr << "Paket laenge falsch" << endl;
					strD->dumpString (protocol.receive.commandData, __HEADER_SIZE);	
				}
				if (uartProtocolGetPacketType() == __UART_REMOTE_RESPONSE) {
					//cerr << "uiReqSeqNo: " << (int) uiRecSeqNo << endl;
					/// Antwort des MC an Client zustellen
					FindMatchingClient(uiRecSeqNo);
				} else {
					/// der MC hat eine Anfrage gestellt
					/// sind meistens Warnungen oder Mitteilungen
					char msg[4];
					memcpy (msg, &protocol.receive.commandData[0] + __PAYLOAD_START_POS,  protocol.receive.commandData[__PACKET_LENGTH_POS]- __HEADER_SIZE);
					for (i = 0; 
						i <= protocol.receive.commandData[__PACKET_LENGTH_POS] - __HEADER_SIZE - 1;
						i++) {
						cerr << protocol.receive.commandData[__PAYLOAD_START_POS + i];
					}
					uartProtocolSendResponse(msg, protocol.receive.commandData[__PACKET_LENGTH_POS]);
				}
			}
			continue;
		}
		/// Nachricht auswerten
		/// Clients an der MessageQueue an- und abmelden
		if( c2s.prioritaet == 1 ) {	
		/// Message Queues aus der Verwaltung entfernen
			sscanf(c2s.message,"%d",&client_id);
			mq_verwaltung_remove( client_id );
		}
		else {
			sscanf(c2s.message,"%d:%s",&client_id, puffer);
			/// client_id eventuell zur Liste hinzufügen 
			mq_verwaltung_add( client_id );	
		/// speichern des Clients und der ID und senden über
		/// serielle Schnittstelle
			client_id = c2s.prioritaet;
			msgno = atoi(c2s.message);
			if (client_id != msgno) {
				SendSerial(c2s.prioritaet, c2s.message);
			}
			res = -1;
		}
	}
	printf(" --- Server-Ende ---\n");
	return EXIT_SUCCESS;
}


#endif
