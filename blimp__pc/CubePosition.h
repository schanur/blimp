/* Autor: Bjoern Griebenow
 *
 * CubePosition ist eine Klasse die hauptsaechlich
 * fuer den Zugriff auf die dynamische Rasterdatenstruktur
 * verwendet wird.
 * Es koennen positive und negative ganze Zahlen verwendet werden.
 * 
 */

#ifndef __CUBE_POSITION_H__
#define __CUBE_POSITION_H__

#include <sys/types.h>
#include <cmath>

#include "signum.h"

#define __INT32_MAX 2147483647

using namespace std;

class CubePosition
{
	public:
		CubePosition ();
		CubePosition (const int32_t iInitXPos, 
				const int32_t iInitYPos,
				const int32_t iInitZPos);
		CubePosition difference (const CubePosition &cCubePositionToDiff) const;
		double distance (const CubePosition &cCubePos) const;
		uint32_t manhattanDistance (const CubePosition cCubePos) const;
		void printPos () const;

		bool operator== (const class CubePosition &cCubePositionToCompare) const;
		CubePosition operator- (const class CubePosition &cCubePositionToSubstract) const;
		CubePosition operator+ (const class CubePosition &cCubePositionToAdd) const;

		int32_t iXPos;
		int32_t iYPos;
		int32_t iZPos;
		//~CubePosition ();
};

#endif
