#ifndef __MESSAGESERIALISATION_CPP__
#define __MESSAGESERIALISATION_CPP__

#include "MessageSerialisation.h"

/*
MessageSerialisation :: MessageSerialisation(struct packetHeader)
{

}
*/
MessageSerialisation :: MessageSerialisation(packetSetEngineBoth toConvert)
{
	char *serptr = (char*) &toConvert;
	message.text[__PAYLOAD_START_POS] = *(serptr + 1);
	message.text[__PAYLOAD_START_POS + 1] = *(serptr + 0);
	message.text[__PAYLOAD_START_POS + 2] = *(serptr + 3);
	message.text[__PAYLOAD_START_POS + 3] = *(serptr + 2);
	
	message.text[__PACKET_TYPE_POS] = __UART_PROTOCOL_ENGINE_BOTH;
	message.text[__PACKET_LENGTH_POS] = 4;
}

MessageSerialisation :: MessageSerialisation(packetSetEngineRight toConvert)
{
	char *serptr = (char*) &toConvert;
	message.text[__PAYLOAD_START_POS] = *(serptr + 1);
	message.text[__PAYLOAD_START_POS + 1] = *(serptr + 0);

	message.text[__PACKET_TYPE_POS] = __UART_PROTOCOL_ENGINE_RIGHT;
	message.text[__PACKET_LENGTH_POS] = 2;

}

MessageSerialisation :: MessageSerialisation(packetSetEngineLeft toConvert)
{
	char *serptr = (char*) &toConvert;
	message.text[__PAYLOAD_START_POS] = *(serptr + 1);
	message.text[__PAYLOAD_START_POS + 1] = *(serptr + 0);

	message.text[__PACKET_TYPE_POS] = __UART_PROTOCOL_ENGINE_BOTH;
	message.text[__PACKET_LENGTH_POS] = 2;
}

MessageSerialisation :: MessageSerialisation(packetSetStepperEngine toConvert)
{
	char *serptr = (char*) &toConvert;
	message.text[__PAYLOAD_START_POS] = *(serptr + 1);
	message.text[__PAYLOAD_START_POS + 1] = *(serptr + 0);

	message.text[__PACKET_TYPE_POS] = __UART_PROTOCOL_STEPPER_ENGINE;
	message.text[__PACKET_LENGTH_POS] = 2;
}

MessageSerialisation :: MessageSerialisation(packetSetStepperVertical toConvert)
{
	char *serptr = (char*) &toConvert;
	message.text[__PAYLOAD_START_POS] = *(serptr + 1);
	message.text[__PAYLOAD_START_POS + 1] = *(serptr + 0);

	message.text[__PACKET_TYPE_POS] = __UART_PROTOCOL_STEPPER_VERTICAL;
	message.text[__PACKET_LENGTH_POS] = 2;
}

MessageSerialisation :: MessageSerialisation(packetSetStepperHorizontal toConvert)
{
	char *serptr = (char*) &toConvert;
	message.text[__PAYLOAD_START_POS] = *(serptr + 1);
	message.text[__PAYLOAD_START_POS + 1] = *(serptr + 0);

	message.text[__PACKET_TYPE_POS] = __UART_PROTOCOL_STEPPER_HORIZONTAL;
	message.text[__PACKET_LENGTH_POS] = 2;
}

MessageSerialisation :: MessageSerialisation(packetSensorCompass8Bit toConvert)
{
	message.text[__PAYLOAD_START_POS] = toConvert.uiDirection;

	message.text[__PACKET_TYPE_POS] = __UART_PROTOCOL_SENSOR_COMPASS_8_BIT_RES;
	message.text[__PACKET_LENGTH_POS] = 1;
}

MessageSerialisation :: MessageSerialisation(packetSensorCompass16Bit toConvert)
{
	char *serptr = (char*) &toConvert;
	message.text[__PAYLOAD_START_POS] = *(serptr + 1);
	message.text[__PAYLOAD_START_POS + 1] = *(serptr + 0);

	message.text[__PACKET_TYPE_POS] = __UART_PROTOCOL_SENSOR_COMPASS_16_BIT_RES;
	message.text[__PACKET_LENGTH_POS] = 2;
}

MessageSerialisation :: MessageSerialisation(packetSensorUltrasonicStart toConvert)
{
	message.text[__PACKET_TYPE_POS] = __UART_PROTOCOL_SENSOR_ULTRASONIC_START;
	message.text[__PACKET_LENGTH_POS] = 0;
}

MessageSerialisation :: MessageSerialisation(packetSensorUltrasonicRead toConvert)
{
	char *serptr = (char*) &toConvert;
	message.text[__PAYLOAD_START_POS] = *(serptr + 1);
	message.text[__PAYLOAD_START_POS + 1] = *(serptr + 0);

	message.text[__PACKET_TYPE_POS] = __UART_PROTOCOL_SENSOR_ULTRASONIC_READ;
	message.text[__PACKET_LENGTH_POS] = 2;
}


MessageSerialisation :: MessageSerialisation(packetLed toConvert)
{
	
	message.text[__PAYLOAD_START_POS] = toConvert.uiLedNo;
	message.text[__PAYLOAD_START_POS + 1] = toConvert.uiLedValue;

	message.text[__PACKET_TYPE_POS] = __UART_PROTOCOL_COMMAND_LED_1;
	message.text[__PACKET_LENGTH_POS] = 2;
}

sSerialisedMsg MessageSerialisation ::  getText()
{
	return (message);
}


#endif
