/* Autor: Bjoern Griebenow
 *
 */

#ifndef __DISTANCE_H__
#define __DISTANCE_H__

#include <string>
#include <math.h>

#include <gps.h>


#include "CircleMath.h"
#include "Coordinate.h"
#include "Exceptions.h"

#ifndef __EARTH_RADIUS
#define __EARTH_RADIUS 6371000.
#endif


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
