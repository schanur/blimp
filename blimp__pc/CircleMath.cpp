#ifndef __CIRCLEMATH_CPP__
#define __CIRCLEMATH_CPP__

double rad2deg (double radVal)
{
    return (radVal * __PI / 180);
}

double deg2rad (double degVal)
{
    return (degVal * 180 / __PI);
}

#endif

