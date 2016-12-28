#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
//#include <curses.h>

#include "defines.h"

#include "Exceptions.cpp"
#include "strman.cpp"
#include "SerialConnection.cpp"
#include "Coordinate.cpp"
//#include "navigation/GPSPosition.cpp"
#include "Distance.cpp"

int main (int argc, char *argv[])
{
    cerr << endl << endl;    

    
    /*for (int i = 0;; i++) {
	Coordinate mem (Latitude (10.1), Longitude (10.3), 10);
	if (i % 10000 == 0) {
	    //cerr << i << endl;
	}
    }*/
    
    //for (int i = 0;; i++) {
	//Coordinate mem (10.1, 23.3, 10.);
	//Coordinate mem2 (Latitude (10.1), Longitude (10.3), 10);
	//if (i % 10000 == 0) {
	    //cerr << i << endl;
	//}
    //}
    //return (0);

    cerr << "90" << endl;
    Latitude (90);
    cerr << "90.01 ";
    Latitude lat_test = Latitude (90.01);
    cerr << lat_test.decimal () << endl;
    cerr << "91" << endl;
    //Latitude (91);
    
    Coordinate coord1 (Latitude (10.1), Longitude (10.3), 10);
    Coordinate coord2 (Latitude (10.2), Longitude (20.4), 10);
    
    
    cerr << "coord1" << endl;
    cerr << coord1.latitude->decimal () << endl;
    //cerr << coord1.latitude->dms->degrees () << endl;
    //cerr << coord1.latitude->dms->minutes () << endl;
    //cerr << coord1.latitude->dms->seconds () << endl;
    
    /*for (;;) {
    Distance dist (Coordinate (Latitude (89.9), Longitude (10.01), 10), 
		   Coordinate (Latitude (10.02), Longitude (10.03), 10));
    }*/
    
    //cerr << "object sizes:" << endl;
    //cerr << "  coordinate: " << sizeof (coord1) << endl;
    //cerr << "  distance:   " << sizeof (dist) << endl;
    //cerr << endl;
    
    //Distance dist (coord1, coord2);
    
    //Distance dist;
    //dist.setStartPoint (coord1);
    //dist.setEndPoint (coord2);
    
    cerr << "dist" << endl;
    //cerr << dist.cStartPoint->latitude->decimal () << endl;
    //cerr << dist.cStartPoint->latitude->dms->degrees () << endl;
    
    //cerr << dist.direction () << endl;
    //cerr << (uint64_t) dist.distance () << endl;
    
    
    
    SerialConnection *cGPSLink = new SerialConnection (__DEV_GPS, __SERCON_MODE_ASCII);
    //SerialConnection *cRnmcLink = new SerialConnection ("/dev/ttyS0");
    cerr << "moeoeepp" << endl;
    while (1) {
	while (!cGPSLink->newDataArrived ()) {
	    
	}
	cout << cGPSLink->getData () << endl;    
	/*if (!cRnmcLink->newData ()) {
	    cout << cRnmcLink->getLine () << endl;
	}*/
    }
    return (EXIT_SUCCESS);
}
