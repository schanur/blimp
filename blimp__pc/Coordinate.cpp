/* Autor: Bjoern Griebenow
 *
 */

#ifndef __COORDINATE_CPP__
#define __COORDINATE_CPP__

#include "Coordinate.h"




//######################################################################

void SphericalCoordinate :: initValues (const double dInitZenith, 
			const double dInitAzimuth,
			const double dInitRadialDistance)
{
	dZenith = dInitZenith;
	dAzimuth = dInitAzimuth;
	dRadialDistance = dInitRadialDistance;
}

SphericalCoordinate :: SphericalCoordinate ()
{
	initValues (0., 0., 0.);
}

SphericalCoordinate :: SphericalCoordinate (const double dInitZenith, 
			const double dInitAzimuth,
			const double dInitRadialDistance)
{
	initValues (dInitZenith, dInitAzimuth, dInitRadialDistance);
}

//######################################################################

uint16_t DegreesMinutesSeconds :: degrees () { return (uiDegrees); }
uint16_t DegreesMinutesSeconds :: minutes () { return (uiMinutes); }
double DegreesMinutesSeconds :: seconds () { return (dSeconds); }

double DegreesMinutesSeconds :: toDecimal ()
{
    return ((double) uiDegrees
	    + ((double) uiMinutes / 60)
	    + ((double) dSeconds / 3600));
}

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

DegreesMinutesSeconds :: DegreesMinutesSeconds (double dInitDecimal)
{
    uiDegrees = (int) dInitDecimal;
    double dModDeg = dInitDecimal - (double) uiDegrees;
    uiMinutes = (int) (dModDeg * 60.);
    double dModMin = dModDeg - (double) uiMinutes / 60;
    dSeconds = dModMin * 3600;
}

DegreesMinutesSeconds :: ~DegreesMinutesSeconds ()
{
    //cerr << "  destructor: ~DegreesMinutesSeconds" << endl;
}

//######################################################################

bool Coordinate :: valid () { return (bValid); }

double Coordinate :: decimal ()
{
    return (dDecimal);
}

Coordinate :: Coordinate ()
{
	bValid = false;
}

Coordinate :: Coordinate (double dInitDecimal)
{
	bValid = true;
    dDecimal = dInitDecimal;
    //dms = new DegreesMinutesSeconds (dDecimal);
}

//######################################################################


Latitude :: Latitude ()
	: Coordinate ()
{
	bValid = false;
}

Latitude :: Latitude (double dInitDecimalLatitude)
    : Coordinate (dInitDecimalLatitude)
{
    if (dInitDecimalLatitude < -90.) {
	if (dInitDecimalLatitude < -90.05) {
		bValid = false;	    
		//throw GeneralException ();
	} else {
	    cerr << "warning: Latitude has value: " << dInitDecimalLatitude << endl;
	    dDecimal = -90.;
	}
    } else if (dInitDecimalLatitude > 90.) {
	if (dInitDecimalLatitude > 90.05) {
		bValid = false;
		//throw GeneralException ();
	} else {
	    cerr << "warning: Latitude has value: " << dInitDecimalLatitude << endl;
	    dDecimal = 90.;
	}
    }
    dDecimal = dInitDecimalLatitude;
}


//######################################################################

Longitude :: Longitude ()
	: Coordinate ()
{
	bValid = false;
}

Longitude :: Longitude (double dInitDecimalLongitude)
    : Coordinate (dInitDecimalLongitude)
{
    if (dInitDecimalLongitude < -180.) {
	if (dInitDecimalLongitude < -180.05) {
		bValid = false;
		throw GeneralException ();
	} else {
	    cerr << "warning: Longitude has value: " << dInitDecimalLongitude << endl;
	    dDecimal = -180.;
	}
    } else if (dInitDecimalLongitude > 180.) {
	if (dInitDecimalLongitude > 180.05) {
		bValid = false;	    
		throw GeneralException ();
	} else {
	    dDecimal = 180.;
	    cerr << "warning: Longitude has value: " << dInitDecimalLongitude << endl;
	}
    }
	bValid = true;
    dDecimal = dInitDecimalLongitude;
};
//######################################################################

Altitude :: Altitude () { initValues (__ALTITUDE_DEFAULT); }
Altitude :: Altitude (double dInitAltitude) { initValues (dInitAltitude); }

void Altitude :: initValues (double dInitAltitude)
{
	bValid = false;
	dAltitude = dInitAltitude;
	if (dAltitude < __ALTITUDE_MIN) {
		throw string ("yellow submarine");
	} else if (dAltitude > __ALTITUDE_MAX) {
		throw string ("baehm");
	} else {
		bValid = true;
	}
}

bool Altitude :: valid () { return bValid; }
double Altitude :: decimal () { return dAltitude; }
double Altitude :: feet () { throw string ("Altitude :: feed (): unsuported"); }

//######################################################################

bool GeoCoordinate :: valid ()
{
	if (latitude.valid () == true) {
		if (longitude.valid () == true) {
			return (true);
		}
	}
	return (false);
}

GeoCoordinate :: GeoCoordinate (const Latitude &cInitLatitude, const Longitude &cInitLongitude, const Altitude &cInitAltitude)
{
    latitude = cInitLatitude;
    longitude = cInitLongitude;
    altitude = cInitAltitude;
}

#endif
