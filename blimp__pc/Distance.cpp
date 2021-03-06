/* Autor: Bjoern Griebenow
 *
 */

#ifndef __DISTANCE_CPP__
#define __DISTANCE_CPP__

#include "Distance.h"

void Distance :: calcSphericAngle ()
{
    double dCircStartLatitude = cStartPoint->latitude.decimal () * (2 * __PI) / 360;
    double dCircStartLongitude = cStartPoint->longitude.decimal () * (2 * __PI) / 360;
    double dCircEndLatitude = cEndPoint->latitude.decimal () * (2 * __PI) / 360;
    double dCircEndLongitude = cEndPoint->longitude.decimal () * (2 * __PI) / 360;
	
    dSphericAngle = (acos (
	    (sin (dCircStartLatitude) 
				* sin (dCircEndLatitude))
	    + (cos (dCircStartLatitude) 
				* cos (dCircEndLatitude)
	    		* cos (dCircEndLongitude - dCircStartLongitude))))
	    * (360. / (2. * __PI));
    std::cerr << "sphericAngle: " << dSphericAngle << std::endl;
}

double Distance :: direction ()
{
	std::cerr << "double Distance :: direction (void): start" << std::endl;
    if (bDirectionValid) { return (dDirection); }
    if (!bStartCoordsValid | !bEndCoordsValid) { throw GeneralException (); }	
    if (!bDistanceValid) {
		calcSphericAngle ();
    }
    bDirectionValid = true;
	
	/// Formel stammt aus dem Softwareprojekt
	/// gpsdrive (http://www.gpsdrive.de)
	double tx, ty;
	tx = (2 * __EARTH_RADIUS * __PI / 360) * cos (deg2rad (cStartPoint->latitude.decimal ()))
			* (cEndPoint->longitude.decimal () - cStartPoint->longitude.decimal ());
	ty = (2 * __EARTH_RADIUS * __PI / 360)
			* (cEndPoint->latitude.decimal () - cStartPoint->latitude.decimal ());
	dDirection = atan (tx / ty);
	if (ty < 0)
				dDirection += __PI;
			if (dDirection >= (2 * __PI))
				dDirection -= 2 * __PI;
			if (dDirection < 0)
				dDirection += 2 * __PI;

    return (rad2deg (dDirection));
}

double Distance :: distance ()
{
    if (bDistanceValid) { return (dDistance); }
    if (!bStartCoordsValid | !bEndCoordsValid) { throw GeneralException (); }	
    
	/// Die externe Funktion "earth_distance" hat eine höhere
	/// Genauigkeit, da sie auf einem Rotationselypsoiden rechnet
	/// anstatt auf einer Kugel.
	/// Allerdings funktioniert diese nicht, wenn die beiden Punkte
	/// dicht bei einander oder dicht bei den Polen liegen.
	/// Fuer diese beiden Faelle wird auf eine Ersatzfunktion
	/// zurueck gegriffen, welche auf einer Kugel rechnet.

	dDistance = earth_distance (cStartPoint->latitude.decimal (),
			cStartPoint->longitude.decimal (),
			cEndPoint->latitude.decimal (),
			cEndPoint->longitude.decimal ());

	//if (dDistance != NAN) {
	if (!isnan(dDistance)) {
		return (dDistance);
	}
	std::cerr << "double Distance :: distance (void): warning: NAN, using fallback algorithm." << std::endl;
	if (!bDirectionValid) {
		calcSphericAngle ();
    }
    bDistanceValid = true;
	dDistance = ((dSphericAngle * (2. * __PI) / 360.)) * __EARTH_RADIUS;
    return (dDistance);
}

void Distance :: setStartPoint (const GeoCoordinate &cNewStartPoint)
{
    delete cStartPoint;
    cStartPoint = new GeoCoordinate(cNewStartPoint);
    bStartCoordsValid = true;
    bDirectionValid = false;
    bDistanceValid = false;
}

void Distance :: setEndPoint (const GeoCoordinate &cNewEndPoint)
{
    delete cEndPoint;
    cEndPoint = new GeoCoordinate(cNewEndPoint);
    bEndCoordsValid = true;
    bDirectionValid = false;
    bDistanceValid = false;
}

Distance :: Distance ()
{
    cStartPoint = new GeoCoordinate (Latitude (0.), Longitude (0.), 0);
    cEndPoint = new GeoCoordinate (Latitude (0.), Longitude (0.), 0);
    bStartCoordsValid = bEndCoordsValid = bDirectionValid = bDistanceValid = false;
}

Distance :: Distance (const GeoCoordinate &cInitStartPoint , const GeoCoordinate &cInitEndPoint)
{
    cStartPoint = new GeoCoordinate (cInitStartPoint);
    cEndPoint = new GeoCoordinate (cInitEndPoint);
    bStartCoordsValid = bEndCoordsValid = true;
    bDirectionValid = bDistanceValid = false;
}

Distance :: ~Distance ()
{
    delete cStartPoint;
    delete cEndPoint;
}

#endif
