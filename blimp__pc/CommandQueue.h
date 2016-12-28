#ifndef __COMMAND_QUEUE_H__
#define __COMMAND_QUEUE_H__

#include <iostream>
#include <map>
#include <string>
#include <sys/types.h>


using namespace std;
//typedef class map<int, string> cQueueElement;

class CommandQueue
{
//######################################################################
	private: uint8_t uiRecSeqenceNo;
	private: uint8_t uiSeqenceNo;
	private: uint8_t uiNextSeqNoToSend;
	private: map<uint8_t, string> mCommandSend;
	private: map<uint8_t, string> mCommandReceive;
	private: map<uint8_t, string>::iterator iter;

	

	public: CommandQueue ();

//######################################################################	
	// SEND QUEUE
	// Neues Kommando in SendeQueue einfügen
	// Rueckgabe: Sequenznummer (0 bei Fehler)
	public: int PutNewCommandToSend (string sCommandToSend);
	
	// Naechstes zu sendendes Kommando abrufen
	public: bool GetNextCommandToSend (string &sResponse);
	
	// Anzahl der noch zu sendenden Kommandos
	public: int CommandsNotSend ();

	// Kommando mit der Sequenznummer (uiRecSeqNo) aus der SendQueue löschen
	private: bool DeleteCommandSendQueue (uint8_t uiRecSeqNo);

//######################################################################
	//RECEIVE QUEUE
	// Neues empfangenes Kommando hinzufuegen
	public: bool PutNewReceivedCommand (string sReceivedCommand);
	
	// naechtes empfangenes Kommando abrufen
	public: bool GetNextReceivedCommand (string &sResponse);
	
	// empfangenes Kommando mit der QUEUE-Nummer (iCommandNo) abrufen
	public: bool GetReceivedCommandSequenceNo (uint32_t iCommandNo, uint8_t &iResponse);
	
	// empfanenes Kommando mit der SEQUENZ-Nummer (uiRecSeqNo) abrufen
	public: bool GetResponse (uint8_t uiRecSeqNo, string &sResponse);
	
	// Anzahl der Kommandos in der Receive Queue
	public: int CommandsReceived ();
	
};


#endif

