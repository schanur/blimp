/* Autor: Bjoern Griebenow
 *
 */

#ifndef __COORDINATE_SYSTEM_TRANSLATION_H__
#define __COORDINATE_SYSTEM_TRANSLATION_H__

#include "math.h"
#include "Coordinate.cpp"

CartesianCoordinate spherical2Cartesician (const SphericalCoordinate& cSphericalCoord);

SphericianCoordinate cartesician2Spherical (const CartesianCoordinate& cCartesianCoord);


#endif
