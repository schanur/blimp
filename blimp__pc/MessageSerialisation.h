#ifndef __MESSAGESERIALISATION_H__
#define __MESSAGESERIALISATION_H__

#include "platform_specifics_blimp_pc.h"

//#include "../shared_source/protocolPackets.h"
//#include "../shared_source/protocolNumbers.h"
#include "../shared_source/uart_protocol_handler.h"
#include "SerialisedMessage.h"



using namespace std;

class MessageSerialisation {

	private:
	sSerialisedMsg message;


	public:
	//MessageSerialisation(struct packetHeader);
	MessageSerialisation(packetSetEngineBoth toConvert);
	MessageSerialisation(packetSetEngineRight toConvert);
	MessageSerialisation(packetSetEngineLeft toConvert);
	MessageSerialisation(packetSetStepperEngine toConvert);
	MessageSerialisation(packetSetStepperVertical toConvert);
	MessageSerialisation(packetSetStepperHorizontal toConvert);
	MessageSerialisation(packetSensorCompass8Bit toConvert);
	MessageSerialisation(packetSensorCompass16Bit toConvert);
	MessageSerialisation(packetSensorUltrasonicStart toConvert);
	MessageSerialisation(packetSensorUltrasonicRead toConvert);
	MessageSerialisation(packetLed toConvert);

	sSerialisedMsg getText();

};

#endif
