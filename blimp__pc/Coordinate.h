/* Autor: Bjoern Griebenow
 *
 */

#ifndef __COORDINATE_H__
#define __COORDINATE_H__

//#include <stdio>
#include <iostream>
#include <string>

#include "defines.h"
#include "Exceptions.cpp"
#include "CircleMath.cpp"
#include "Vector.cpp"

using namespace std;



typedef Vector CartesianCoordinate;

class SphericalCoordinate
{
	public: 
		SphericalCoordinate ();
		SphericalCoordinate (const double dInitZenith, 
			const double dInitAzimuth,
			const double dInitRadialDistance);
		
		double dZenith;
		double dAzimuth;
		double dRadialDistance;

	private: 
		void initValues (const double dInitZenith, 
			const double dInitAzimuth,
			const double dInitRadialDistance);
	
};

//######################################################################

/*class DegreesMinutes
{
    private: uint16_t uiDegrees;
    private: double dMinutes;
    
    public: uint16_t degrees ();
    public: double minutes ();
    
    public: double toDecimal ();
    
    public: DegreesMinutesSeconds (DegreesMinutesSeconds &cInitDMS);
    public: DegreesMinutesSeconds (uint16_t uiInitDegrees, uint16_t uiInitMinutes, double dInitSeconds);
    public: DegreesMinutesSeconds (double dInitDecimal);
    public: ~DegreesMinutesSeconds ();
};*/

//######################################################################

class DegreesMinutesSeconds
{
    private: uint16_t uiDegrees;
    private: uint16_t uiMinutes;
    private: double dSeconds;
    
    public: uint16_t degrees ();
    public: uint16_t minutes ();
    public: double seconds ();
    
    public: double toDecimal ();
    
    public: DegreesMinutesSeconds (DegreesMinutesSeconds &cInitDMS);
    public: DegreesMinutesSeconds (uint16_t uiInitDegrees, uint16_t uiInitMinutes, double dInitSeconds);
    public: DegreesMinutesSeconds (double dInitDecimal);
    public: ~DegreesMinutesSeconds ();
};

class Coordinate
{
    protected: double dDecimal;
	protected: bool bValid;
	//protected: bool bValid;
    //public: class Degrees
    //public: class DegreesMinutesSeconds *dms;
    
    public: bool valid ();
    public: double decimal ();
    
    //public: HalfCoordinate (const HalfCoordinate &cInitHalfCoordinate);
	public: Coordinate ();    
	public: Coordinate (double dInitDecimal);
    //public: HalfCoordinate (uint16_t uiInitDegrees, uint16_t uiInitMinutes, double dInitSeconds);
    //public: ~Coordinate ();
};

class Latitude : public Coordinate
{
    //public: Latitude (const Latitude &cInitLatitide);
	public: Latitude ();
	public: Latitude (double dInitDecimalLatitude);
    //public: Latitude (uint16_t uiDegreesToSet, uint16_t uiMinutesToSet, double dSecondsToSet);
    //public: ~Latitude ();
};

class Longitude : public Coordinate
{
    //public: Longitude (const Longitude &cInitLongitude);
    	public: Longitude ();
	public: Longitude (double dInitDecimalLongitude);
    //public: Longitude (uint16_t uiDegreesToSet, uint16_t uiMinutesToSet, double dSecondsToSet);
    //public: ~Longitude ();
};

class Altitude
{
	private: bool bValid;
	private: double dAltitude;

	public: bool valid ();
	public: double decimal ();
	public: double feet ();

	public: Altitude ();
	public: Altitude (double dInitAltitide);
};

class GeoCoordinate
{
    public: class Latitude latitude;
    public: class Longitude longitude;
    public: class Altitude altitude;

	public: bool valid ();

	public: GeoCoordinate ();
	//public: Coordinate (const Coordinate &cInitCoordinate);
    public: GeoCoordinate (const Latitude &cInitLatitude, const Longitude &cInitLongitude, const Altitude &cInitAltitude);

    //public: Coordinate (Latitude cInitLatitude, Longitude cInitLongitude, float fAltitude);
    //public: Coordinate (double dInitDecimalLatitude, double dInitDecimalLongitude, float fInitAltitude);
    //public: ~Coordinate ();
};

#endif
