#ifndef __MESSAGEDESERIALISATION_H__
#define __MESSAGEDESERIALISATION_H__

//#include "../shared_source/print_dtype.c"

#include "../shared_source/protocolPackets.h"
#include "../shared_source/protocolNumbers.h"
#include "SerialisedMessage.h"

using namespace std;



class MessageDeSerialisation {

	private:
	sSerialisedMsg message;

	public:
	MessageDeSerialisation(sSerialisedMsg msg);
	//void getStruct (packetHeader *pStrToDeSerialize);
	void getStruct (packetSetEngineBoth *pStrToDeSerialize);
	void getStruct (packetSetEngineRight *pStrToDeSerialize);
	void getStruct (packetSetEngineLeft *pStrToDeSerialize);
	void getStruct (packetSetStepperEngine *pStrToDeSerialize);
	void getStruct (packetSetStepperVertical *pStrToDeSerialize);
	void getStruct (packetSetStepperHorizontal *pStrToDeSerialize);
	void getStruct (packetSensorCompass8Bit *pStrToDeSerialize);
	void getStruct (packetSensorCompass16Bit *pStrToDeSerialize);
	void getStruct (packetSensorUltrasonicStart *pStrToDeSerialize);
	void getStruct (packetSensorUltrasonicRead *pStrToDeSerialize);
	void getStruct (packetLed *pStrToDeSerialize);

};

#endif
