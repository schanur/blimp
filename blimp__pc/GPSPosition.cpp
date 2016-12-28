#ifndef __GPS_POSITION_CPP__
#define __GPS_POSITION_CPP__

#include "GPSPosition.h"

uint16_t DegreesMinutesSeconds :: degrees () { return (uiDegrees); }
uint16_t DegreesMinutesSeconds :: minutes () { return (uiMinutes); }
double DegreesMinutesSeconds :: seconds () { return (dSeconds); }

DegreesMinutesSeconds :: DegreesMinutesSeconds (DegreesMinutesSeconds &cInitDMS)
{
    uiDegrees = cInitDMS.degrees ();
    uiMinutes = cInitDMS.minutes ();
    dSeconds = cInitDMS.seconds ();
}

DegreesMinutesSeconds :: DegreesMinutesSeconds (uint16_t uiInitDegrees, uint16_t uiInitMinutes, double dInitSeconds)
{
    uiDegrees = uiInitDegrees;
    uiMinutes = uiInitMinutes;
    dSeconds = dInitSeconds;
}

DegreesMinutesSeconds :: ~DegreesMinutesSeconds ()
{

}

Latitude :: Latitude (Latitude &cInitLatitude)
{
    dms = new DegreesMinutesSeconds (cInitLatitude.dms->degrees (), 
	    cInitLatitude.dms->minutes (), 
	    cInitLatitude.dms->seconds ());
}

Latitude :: Latitude (uint16_t uiInitDegrees, uint16_t uiInitMinutes, double dInitSeconds)
{
    dms = new DegreesMinutesSeconds (uiInitDegrees, uiInitMinutes, dInitSeconds);
}


Latitude :: ~Latitude ()
{

}

Longitude :: Longitude (Longitude &cInitLongitude)
{

}

Longitude :: Longitude (uint16_t uiInitDegrees, uint16_t uiInitMinutes, double dInitSeconds)
{
    dms = new DegreesMinutesSeconds (uiInitDegrees,uiInitMinutes,dInitSeconds);
}


Longitude :: ~Longitude ()
{

}

void GPSPosition :: initVars ()
{
    
}

GPSPosition :: GPSPosition (GPSPosition &cInitGPSPos)
{
    latitude = new Latitude (cInitGPSPos.latitude->dms->degrees (), 
	    cInitGPSPos.latitude->dms->minutes (), 
	    cInitGPSPos.latitude->dms->seconds ());
}

GPSPosition :: GPSPosition (Latitude &cInitLatitude, Longitude &cInitLongitude, float fAltitude)
{
    latitude = new Latitude (cInitLatitude.dms->degrees (), 
	    cInitLatitude.dms->minutes (), 
	    cInitLatitude.dms->seconds ());
    longitude = new Longitude (cInitLongitude.dms->degrees (), 
	cInitLongitude.dms->minutes (), 
	cInitLongitude.dms->seconds ());
}


GPSPosition :: GPSPosition (double dInitLatitude, double dInitLongitude, float fAltitude)
{

}

#endif
