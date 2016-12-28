/* Autor: Bjoern Griebenow
 *
 */

#ifndef __COORDINATE_SYSTEM_TRANSLATION_H__
#define __COORDINATE_SYSTEM_TRANSLATION_H__

#include <cmath>
#include "Coordinate.h"

CartesianCoordinate spherical2Cartesician (const SphericalCoordinate& cSphericalCoord);

SphericalCoordinate cartesician2Spherical (const CartesianCoordinate& cCartesianCoord);


#endif
