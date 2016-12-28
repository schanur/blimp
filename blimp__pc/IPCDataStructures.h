#ifndef __IPC_DATA_STRUCTURES_H__
#define __IPC_DATA_STRUCTURES_H__

//#include <iostream>
#include <stdlib.h>
#include <stdio.h>
//#include <string>
//#include <fstream>
//#include <fcntl.h>

#include "defines.h"
#include "IPCDataStructures.cpp"

using namespace std;


typedef MCStatus volatile class
{
	public:
	uint16_t compass;
	uint16_t laserDistance;
	uint16_t ultrasonicDistance;

	uint16_t motorSpeedLeft; mslc 
	uint16_t motorSpeedRight;
	uint16_t batterieLevel;
};

//#####################################################################

typedef MCSet volatile class
{
	public:
	uint16_t motorSpeedLeft; mslc
	uint16_t motorSpeedRight;
	
};

#endif
