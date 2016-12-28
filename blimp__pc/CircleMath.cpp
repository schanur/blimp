#ifndef __CIRCLEMATH_CPP__
#define __CIRCLEMATH_CPP__

double rad2deg (double radVal)
{
	return (radVal * 180 / __PI);
}

double deg2rad (double degVal)
{
	return (degVal * __PI / 180);
}

#endif

