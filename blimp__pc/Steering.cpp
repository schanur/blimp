#ifndef __STEERING_CPP__
#define __STEERING_CPP__

#include "Steering.h"

using namespace std;

Position :: Position ()
{
	dLatitude = 0;
	dLongitude = 0;
	dAltitude = 0;

}

Position :: Position (double &Latitude, double &Longitude, double &Altitude)
{
	dLatitude = Latitude;
	dLongitude = Longitude;
	dAltitude = Altitude;
}


//######################################################################


bool Steering :: DoSteering ()
{
	if (GetPositionData ()) {
		CalculateDirection ();
    SetEngines ();
    SetStepper ();
		return (true);
	} 
	return (false);
}
	
bool Steering :: SetDestination (Position cDest)
{
	cDestPosition = cDest;
  return (true);
}	
	
void Steering :: CalculateDirection ()
{
// hier die Richtung berechnen
	//dDirection = errechnen
}
	
void Steering :: SetEngines ()
{	
  if (cCurrPosition != cDestPosition) {
    if (abs(dCurrDirection - dDirection) == 0) {
	 // Richtung stimmt
    return ();
    } else if (abs(dCurrDirection - dDirection) < 180) {
    // rechter Motor schub
    } else {
    //linker Motor schub
   }
   return ();
  }
	///TODO hier Motoren setzen
	//iEngineLeftCurr
	//iEngineRightCurr
}
	
void Steering :: SetStepper ()
{
   if (cCurrPosition.dAltidute != cDestPosition.dAltidute) {
    if (cCurrPosition.dAltidute < cDestPosition.dAltidute) {
    // weiter rauf
    } else {
    //weiter runter
    }
   }
	///TODO hier Motoren setzen
	//iEngineLeftCurr
	//iEngineRightCurr
}

bool Steering :: GetPositionData ()
{
	cLastPosition = cCurrPosition;
	/// TODO: Position auslesen
	//cCurrPosition = FUNKTIONSAUFRUF
	//dCurrDirection = vom Kompass
	//dDirection = errechnen
	return (true);
}

#endif 
