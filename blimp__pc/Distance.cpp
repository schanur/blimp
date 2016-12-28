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
	    (sin (dCircStartLatitude) * sin (dCircEndLatitude))
	    + (cos (dCircStartLatitude) * cos (dCircEndLatitude)
	    * cos (dCircEndLongitude - dCircStartLongitude))))
	    * (360. / (2. * __PI));
    cerr << "sphericAngle: " << dSphericAngle << endl;
}

double Distance :: direction ()
{
    if (bDirectionValid) { return (dDirection); }
    if (!bStartCoordsValid | !bEndCoordsValid) { throw GeneralException (); }	
    if (!bDistanceValid) {
		calcSphericAngle ();
    }
    bDirectionValid = true;
    /*dDirection = acos ((sin (cEndPoint->latitude->decimal ())
	    - (sin (cStartPoint->latitude->decimal ())
	    * cos (dSphericAngle)))
	    / (cos (cEndPoint->latitude->decimal ())
	    * (sin (dSphericAngle))))
	    * (360. / (2. * __PI));*/
    
    cerr << "direction ()" << endl;
    cerr << cEndPoint->latitude.decimal () << endl;
    cerr << cStartPoint->latitude.decimal () << endl;
    //cerr << cEndPoint->latitude->decimal () << endl;
    //cerr << cEndPoint->latitude->decimal () << endl;
    dDirection = rad2deg (acos (
			sin (deg2rad(cStartPoint->latitude.decimal ()))
			* sin (deg2rad(cEndPoint->latitude.decimal ()))
			+ cos (deg2rad(cStartPoint->latitude.decimal ()))
			* cos (deg2rad(cEndPoint->latitude.decimal ()))
			* cos (deg2rad(cEndPoint->longitude.decimal ())
					- deg2rad(cStartPoint->longitude.decimal ()))));

	/*dDirection = (sin (deg2rad(cEndPoint->latitude.decimal ()))
	    - (sin (deg2rad(cStartPoint->latitude.decimal ()))
	    * cos (dSphericAngle)))
	    / (cos (deg2rad(cStartPoint->latitude.decimal ()))
	    * sin (dSphericAngle));*/

	/*dDirection = (sin (cEndPoint->latitude.decimal ())
	    - (sin (cStartPoint->latitude.decimal ())
	    * cos (dSphericAngle)))
	    / (cos (cStartPoint->latitude.decimal ())
	    * sin (dSphericAngle));*/
    //cerr << "direction vor acos:  "<< dDirection << endl;
    //dDirection = acos (dDirection) * (360. / (2 * __PI));
    //cerr << "direction nach acos: " << dDirection << endl;
     if (cStartPoint->longitude.decimal () > cEndPoint->longitude.decimal ()) {    
		dDirection = 360. - dDirection;
    }
    return (dDirection);

	//*****************************
     /*       kurswinkel = (System.Math.Sin(x_dezgrad_zweite) - System.Math.Sin(x_dezgrad_erste) * System.Math.Cos(winkel)) / (System.Math.Cos(x_dezgrad_erste) * System.Math.Sin(winkel));

            double degrees = (System.Math.Acos(kurswinkel) * (360 / (2 * System.Math.PI)));
            if (y_dezgrad_erste < y_dezgrad_zweite)
            {
                return (degrees);
            }
            else 
            {
                return (360 - degrees);
            }

*/
}

double Distance :: distance ()
{
    if (bDistanceValid) { return (dDistance); }
    if (!bStartCoordsValid | !bEndCoordsValid) { throw GeneralException (); }	
    
	/// Die externe Funktion "earth_distance" hat eione höhere
	/// Genauigkeit, da sie auf einen Rotationselypsoiden rechnet
	/// anstatt auf einer Kugel.
	/// Allerdings funktioniert diese nicht, wenn die beiden Punkte
	/// dicht bei einander oder dicht bei den Polen liegen.
	/// Fuer diese beiden Faelle wird auf eine Ersatzfunktion
	/// zurueck gegriffen.

	dDistance = earth_distance (cStartPoint->latitude.decimal (),
			cStartPoint->longitude.decimal (),
			cEndPoint->latitude.decimal (),
			cEndPoint->longitude.decimal ());

	//if (dDistance != NAN) {
	if (!isnan(dDistance)) {
		return (dDistance);
	}
	cerr << "double Distance :: distance (void): warning: NAN, using fallback algorithm." << endl;
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
