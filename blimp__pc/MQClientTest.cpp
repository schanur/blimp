#include "MessageQueueClient.cpp"
#include "MessageSerialisation.cpp"
#include "MessageDeSerialisation.cpp"
#include "../shared_source/protocolPackets.h"
#include "../shared_source/protocolNumbers.h"
#include "iostream"
#include "string"

using namespace std;


int main (void) {

	MessageQueueClient  mqc;
	mqc.StartMessageQueueClient(123L);
/*
	int iWert;
	cout << " Wert eingeben: ";
	cin >> iWert;
	cout << endl << "int: " << iWert << endl;
	packetSetStepperHorizontal stepper;
	stepper.iAngle = iWert;
	MessageSerialisation serial(stepper);
	struct sSerialisedMsg cMsg = serial.getText();
	//cerr << "Engine Right size: " << sizeof(struct packetSetEngineRight) << endl;
	//cerr << "Packet header size: " << sizeof(struct packetHeader) << endl;
	//cerr << "das kommt von MsgSerialisation: " << cMsg.text << "--" << endl;
	mqc.SendMessage (serial.getText());
*/	
	
	
	
	{
		packetSensorUltrasonicStart ultrasonicStart;
		MessageSerialisation serial (ultrasonicStart);
		struct sSerialisedMsg cMsg = serial.getText();
		mqc.SendMessage (serial.getText());
		
		mqc.ReceiveMessage (cMsg);
	}
	cerr << "a";
//	sleep(1);
	cerr << "b" << endl;
	{
		packetSensorUltrasonicRead ultrasonicRead;
		
		MessageSerialisation serial (ultrasonicRead);
		struct sSerialisedMsg cMsg = serial.getText();
		mqc.SendMessage (cMsg);
		mqc.ReceiveMessage (cMsg);
		MessageDeSerialisation deSerialize(cMsg);
		deSerialize.getStruct (&ultrasonicRead);
		
		cerr << "Ultraschall: " << (uint16_t) ultrasonicRead.uiDistance << endl;
	}
	
	/*
	//mqc.StartMessageQueueClient(123L);
	{
		packetSetStepperEngine stepper3;
		stepper3.iAngle = 10000;
		MessageSerialisation serial(stepper3);
		struct sSerialisedMsg cMsg = serial.getText();
		mqc.SendMessage (serial.getText());
	}
*/
	mqc.EndMessageQueueClient ();


return 0;
}
