/* Autor: Bjoern Griebenow
 *
 */

#ifndef __VECTOR_CPP__
#define __VECTOR_CPP__

#include "Vector.h"

void Vector :: initValues (const double dInitXValue, 
		const double dInitYValue,
		const double dInitZValue)
{
	dX = dInitXValue;
	dY = dInitYValue;
	dZ = dInitZValue;
}

Vector :: Vector ()
{
	initValues (0., 0., 0.);
}

Vector :: Vector (const double dInitXValue, 
			const double dInitYValue,
			const double dInitZValue)
{
	initValues (dInitXValue, dInitYValue, dInitZValue);
}

#endif
