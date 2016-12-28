#ifndef __PROTOCOL_PACKETS_H__
#define __PROTOCOL_PACKETS_H__

#include <stdint.h>

struct packetHeader
{
	uint8_t uiID;
	uint8_t uiSequenceNo;
	uint8_t uiLength;
};

struct packetSetEngineBoth
{
	int16_t iRight;
	int16_t iLeft;
};

struct packetSetEngineRight
{
	int16_t iSpeed;
};

struct packetSetEngineLeft
{
	int16_t iSpeed;
};

struct packetSetStepperEngine
{
	int16_t iAngle;
};

struct packetSetStepperVertical
{
	int16_t iAngle;
};

struct packetSetStepperHorizontal
{
	int16_t iAngle;
};

struct packetSensorCompass8Bit
{
	uint8_t uiDirection;
};

struct packetSensorCompass16Bit
{
	uint16_t uiDirection;
};

struct packetSensorUltrasonicStart
{
	uint8_t uiDummy;
};

struct packetSensorUltrasonicRead
{
	uint16_t uiDistance;
};


struct packetLed
{
	uint8_t uiLedNo;
	uint8_t uiLedValue;
};

#endif
