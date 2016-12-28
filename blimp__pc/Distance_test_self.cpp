#include <iostream>

#include <sys/types.h>

#include "Distance.cpp"
#include "gps.h"

using namespace std;


int main (void)
{
	double lat1, lon1, lat2, lon2;
	cin >> lat1;
	cin >> lon1;
	cin >> lat2;
	cin >> lon2;

	Distance self(GeoCoordinate(
			Latitude(lat1), 
			Longitude(lon1), 
			Altitude(100.)), 
			GeoCoordinate(
			Latitude(lat2), 
			Longitude(lon2), 
			Altitude(100.)));
	cout << "distance self:  " << self.distance () << endl;
	cout << "distance gps.h: " << earth_distance (lat1, lon1, lat2, lon2) << endl;

}