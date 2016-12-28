#ifndef __MESSAGEDESERIALISATION_CPP__
#define __MESSAGEDESERIALISATION_CPP__

#include "MessageDeSerialisation.h"


MessageDeSerialisation :: MessageDeSerialisation(sSerialisedMsg msg)
{
	message = msg;
}
/*
void MessageDeSerialisation :: getStruct (packetHeader *pStrToDeSerialize)
{

}
*/
void MessageDeSerialisation :: getStruct (packetSetEngineBoth *pStrToDeSerialize)
{
	char *strptr = (char*) pStrToDeSerialize;
	strptr[0] = message.text[__PAYLOAD_START_POS + 1];
	strptr[1] = message.text[__PAYLOAD_START_POS];
	strptr[2] = message.text[__PAYLOAD_START_POS + 3];
	strptr[3] = message.text[__PAYLOAD_START_POS + 2];
}

void MessageDeSerialisation :: getStruct (packetSetEngineRight *pStrToDeSerialize)
{
	char *strptr = (char*) pStrToDeSerialize;
	strptr[0] = message.text[__PAYLOAD_START_POS + 1];
	strptr[1] = message.text[__PAYLOAD_START_POS];
}

void MessageDeSerialisation :: getStruct (packetSetEngineLeft *pStrToDeSerialize)
{
	char *strptr = (char*) pStrToDeSerialize;
	strptr[0] = message.text[__PAYLOAD_START_POS + 1];
	strptr[1] = message.text[__PAYLOAD_START_POS];
}

void MessageDeSerialisation :: getStruct (packetSetStepperEngine *pStrToDeSerialize)
{
	char *strptr = (char*) pStrToDeSerialize;
	strptr[0] = message.text[__PAYLOAD_START_POS + 1];
	strptr[1] = message.text[__PAYLOAD_START_POS];
}

void MessageDeSerialisation :: getStruct (packetSetStepperVertical *pStrToDeSerialize)
{
	char *strptr = (char*) pStrToDeSerialize;
	strptr[0] = message.text[__PAYLOAD_START_POS + 1];
	strptr[1] = message.text[__PAYLOAD_START_POS];
}

void MessageDeSerialisation :: getStruct (packetSetStepperHorizontal *pStrToDeSerialize)
{
	char *strptr = (char*) pStrToDeSerialize;
	strptr[0] = message.text[__PAYLOAD_START_POS + 1];
	strptr[1] = message.text[__PAYLOAD_START_POS];
}

void MessageDeSerialisation :: getStruct (packetSensorCompass8Bit *pStrToDeSerialize)
{
	pStrToDeSerialize->uiDirection = message.text[__PAYLOAD_START_POS];
}

void MessageDeSerialisation :: getStruct (packetSensorCompass16Bit *pStrToDeSerialize)
{
	char *strptr = (char*) pStrToDeSerialize;
	strptr[0] = message.text[__PAYLOAD_START_POS + 1];
	strptr[1] = message.text[__PAYLOAD_START_POS];
}

void MessageDeSerialisation :: getStruct (packetSensorUltrasonicStart *pStrToDeSerialize)
{
	
}

void MessageDeSerialisation :: getStruct (packetSensorUltrasonicRead *pStrToDeSerialize)
{
	char *strptr = (char*) pStrToDeSerialize;
	strptr[0] = message.text[__PAYLOAD_START_POS + 1];
	strptr[1] = message.text[__PAYLOAD_START_POS];
	//uartPutBinX (strptr, 2);
}

void MessageDeSerialisation :: getStruct (packetLed *pStrToDeSerialize)
{
	pStrToDeSerialize->uiLedNo = message.text[__PAYLOAD_START_POS];
	pStrToDeSerialize->uiLedValue = message.text[__PAYLOAD_START_POS + 1];
}	
	
#endif
	
