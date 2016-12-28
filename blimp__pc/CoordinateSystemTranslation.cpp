/* Autor: Bjoern Griebenow
 *
 */

#ifndef __COORDINATE_SYSTEM_TRANSLATION_CPP__
#define __COORDINATE_SYSTEM_TRANSLATION_CPP__

#include "CoordinateSystemTranslation.h"

CartesianCoordinate spherical2Cartesician (const SphericalCoordinate& cSphericalCoord)
{
	double dZenithCosRadius = cos (cSphericalCoord.dZenith) * cSphericalCoord.dRadialDistance;
	CartesianCoordinate cCartesianCoord (
		dZenithCosRadius * cos (cSphericalCoord.dAzimuth),
		dZenithCosRadius * sin (cSphericalCoord.dAzimuth),
		cSphericalCoord.dRadialDistance * sin (cSphericalCoord.dZenith);
	return (cCartesianCoord);
}

SphericalCoordinate cartesian2Spherical (const CartesianCoordinate& cCartesianCoord)
{
	SphericalCoordinate cSphericalCoord;
	
	

	return (cSphericalCoord);
}

#endif
