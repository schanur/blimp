/* Autor: Bjoern Griebenow
 *
 */

#ifndef __DISTANCE_H__
#define __DISTANCE_H__

#include <string>
#include <math.h>

#include <gps.h>

#include "defines.h"
#include "CircleMath.cpp"
#include "Coordinate.cpp"
#include "Exceptions.cpp"

using namespace std;

class Distance
{
    public: GeoCoordinate *cStartPoint, *cEndPoint;
    private: bool bStartCoordsValid, bEndCoordsValid;
    private: bool bDirectionValid, bDistanceValid;
    private: bool bSame;
    
    private: double dSphericAngle;
    private: double dDirection;
    private: double dDistance;
    
    private: 
		void calcSphericAngle ();
		double distanceOnSphere ();
    public: 
		double direction ();
    	double distance ();

    //public: bool reached ();

    public: void setStartPoint (const GeoCoordinate &cNewStartPoint);
    public: void setEndPoint (const GeoCoordinate &cNewEndPoint);

    public: Distance ();
    public: Distance (const GeoCoordinate &cInitStartPoint, const GeoCoordinate &cInitEndPoint);
    public: ~Distance ();
};

#endif
