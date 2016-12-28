/* Autor: Bjoern Griebenow
 *
 */

#ifndef __COORDINATE_H__
#define __COORDINATE_H__

//#include <stdio>
#include <iostream>
#include <string>

//#include "defines.h"
#include "Exceptions.h"
#include "CircleMath.h"
#include "Vector.h"


#ifndef __PI
#define __PI 3.141592653589793
#endif

#define __ALTITUDE_DEFAULT 100.
#define __ALTITUDE_MIN -100.
#define __ALTITUDE_MAX 1000.


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
    
    public: bool valid ();
    public: double decimal ();
    
	public: Coordinate ();    
	public: Coordinate (double dInitDecimal);
};

class Latitude : public Coordinate
{
	public: Latitude ();
	public: Latitude (double dInitDecimalLatitude);

};

class Longitude : public Coordinate
{
    public: Longitude ();
	public: Longitude (double dInitDecimalLongitude);
};

class Altitude
{
	private: bool bValid;
	private: double dAltitude;

		void initValues (double dInitAltitude);

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
    public: GeoCoordinate (const Latitude &cInitLatitude, const Longitude &cInitLongitude, const Altitude &cInitAltitude);

    //public: Coordinate (Latitude cInitLatitude, Longitude cInitLongitude, float fAltitude);
    //public: Coordinate (double dInitDecimalLatitude, double dInitDecimalLongitude, float fInitAltitude);
};

#endif
