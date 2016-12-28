#ifndef __CIRCLEMATH_CPP__
#define __CIRCLEMATH_CPP__

#include "CircleMath.h"

//#define DEG2RAD(x) (x*M_PI/180.0)
//#define RAD2DEG(x) (x/M_PI*180.0)

double rad2deg (double radVal)
{
	return (radVal * 180 / __PI);
}

double deg2rad (double degVal)
{
	return (degVal * __PI / 180);
}

#endif

