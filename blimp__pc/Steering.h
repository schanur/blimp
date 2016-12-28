#ifndef __STEERING_H__
#define __STEERING_H__

#include "sys/types.h"

using namespace std;

class Position
{
	public: Position ();
	public: Position (double &Latitude, double &Longitude, double &Altitude);

	public:
	double dLatitude;
	double dLongitude;
	double dAltitude;
};

//######################################################################

class Steering
{
	private: Position cLastPosition;
	private: Position cCurrPosition;
	private: Position cDestPosition;
	private: double dDirection;
	private: double dCurrDirection;
	private: int16_t iEngineLeftCurr;
	private: int16_t iEngineRightCurr;
	
	
	//Gesamter Steuerungsprozess
	public: bool DoSteering ();
	
	//Setzt ein neues Ziel
	public: bool SetDestination (Position cDest);
	
	
	//Berechnet die Richtung zum Zielpunkt
	private: void CalculateDirection ();
	
	// Setzt Motoren - Geschwindigkeit und Richtung
	private: void SetEngines ();	
	private: void SetStepper ();		
	// Holt Daten ueber Psoition, Ausrichtung und Hoehe
	private: bool GetPositionData ();		
};

#endif 
