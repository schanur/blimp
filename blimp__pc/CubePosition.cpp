/* Autor: Bjoern Griebenow
 *
 */

#ifndef __CUBE_POSITION_CPP__
#define __CUBE_POSITION_CPP__

#include "CubePosition.h"


CubePosition :: CubePosition ()
{
	iXPos = 0;
	iYPos = 0;
	iZPos = 0;
}

CubePosition :: CubePosition (const int32_t iInitXPos, 
		const int32_t iInitYPos,
		const int32_t iInitZPos)
{
	iXPos = iInitXPos;
	iYPos = iInitYPos;
	iZPos = iInitZPos;
}

CubePosition CubePosition :: difference (const CubePosition &cCubePositionToDiff) const
{
	CubePosition cDiff;
	int64_t iXDiff;
	int64_t iYDiff;
	int64_t iZDiff;
	iXDiff = (int64_t) cCubePositionToDiff.iXPos - iXPos;
	iYDiff = (int64_t) cCubePositionToDiff.iYPos - iYPos;
	iZDiff = (int64_t) cCubePositionToDiff.iZPos - iZPos;
	if (abs (iXDiff) > __INT32_MAX) {
		cerr << "CubePosition :: differnce: xDiff value to high." << endl;
		iXDiff = signum (iXDiff) * __INT32_MAX;
	}
	if (abs (iYDiff) > __INT32_MAX) {
		cerr << "CubePosition :: differnce: yDiff value to high." << endl;
		iYDiff = signum (iYDiff) * __INT32_MAX;
	}
	if (abs (iZDiff) > __INT32_MAX) {
		cerr << "CubePosition :: differnce: zDiff value to high." << endl;
		iZDiff = signum (iZDiff) * __INT32_MAX;
	}
	cDiff.iXPos = (int32_t) iXDiff;
	cDiff.iYPos = (int32_t) iYDiff;
	cDiff.iZPos = (int32_t) iZDiff;
	return (cDiff);
}

double CubePosition :: distance (const CubePosition &cCubePos) const
{
	CubePosition cDiff = difference (cCubePos);
	return (
			sqrt(
			((double) cDiff.iXPos * cDiff.iXPos)
			+ ((double) cDiff.iYPos * cDiff.iYPos)
			+ ((double) cDiff.iZPos * cDiff.iZPos))
	);
}

uint32_t CubePosition :: manhattanDistance (const CubePosition cCubePos) const
{
	CubePosition cDiff = difference (cCubePos);
	return (abs (cDiff.iXPos) + abs (cDiff.iYPos) + abs (cDiff.iZPos));
}

void CubePosition :: printPos () const
{
	cerr << "  X: " << iXPos;// << endl;
	cerr << "  Y: " << iYPos;// << endl;
	cerr << "  Z: " << iZPos << endl;
}

bool CubePosition :: operator== (const class CubePosition &cCubePositionToCompare) const
{
	if (iXPos == cCubePositionToCompare.iXPos &&
			iYPos == cCubePositionToCompare.iYPos &&
			iZPos == cCubePositionToCompare.iZPos) {
		return (true);
	}
	return (false);
}

CubePosition CubePosition :: operator- (const class CubePosition &cCubePositionToSubstract) const
{
	CubePosition cResult;
	cResult.iXPos = iXPos - cCubePositionToSubstract.iXPos;
	cResult.iYPos = iYPos - cCubePositionToSubstract.iYPos;
	cResult.iZPos = iZPos - cCubePositionToSubstract.iZPos;
	return (cResult);
}

CubePosition CubePosition :: operator+ (const class CubePosition &cCubePositionToAdd) const
{
	CubePosition cResult;
	cResult.iXPos = iXPos + cCubePositionToAdd.iXPos;
	cResult.iYPos = iYPos + cCubePositionToAdd.iYPos;
	cResult.iZPos = iZPos + cCubePositionToAdd.iZPos;
	return (cResult);
}

#endif
