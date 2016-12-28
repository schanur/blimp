/* Autor: Bjoern Griebenow
 *
 */

#ifndef __PATH_FINDER_CPP__
#define __PATH_FINDER_CPP__

#include "PathFinder.h"


//#####################################################################

PathFinder :: PathFinder (ObstacleMap *cpObstacleMap)
{
	cpObstacleModel = cpObstacleMap;
}
		
bool PathFinder :: searchPath (CubePath &cPath, const CubePosition &cStartPos, const CubePosition &cEndPos)
{
	cpUsedCubesModel = new DynamicBitMap ();
	cTargetPos = cEndPos;
	cpPath = &cPath;
	cpLongPath = new CubePath ();
	bool bPathFound = nextCubeStep (__PATH_FINDER__MAX_RECURSION_DEPTH, cStartPos);
	if (bPathFound) {
		cout << "route found" << endl;
		cout << "route length:            " << cpLongPath->size () << endl;
		calcShortPath ();
		if (cpPath->size () < cpLongPath->size ()) {
			cout << "route reduction successful" << endl;
			cout << "short route length:      " << cpPath->size () << endl;
		}
		
		CubePath::iterator iPathIt, iPathIt2;
		int32_t  uiPathErrors = 0;
		for (iPathIt = cpPath->begin (); iPathIt != cpPath->end (); iPathIt++) {
			iPathIt2 = iPathIt;
			iPathIt2++;
			if (iPathIt2 != cpPath->end ()) {
				if (iPathIt->manhattanDistance (*iPathIt2) != 1) {
					cout << "manhattanError" << endl;
					uiPathErrors++;
				}
			}
		}
	} else {
		cout << "no route found" << endl;
	}

	delete cpLongPath;
	delete cpUsedCubesModel;
	return (bPathFound);
}

bool PathFinder :: nextCubeStep (const uint32_t uiRecursionStepsLeft, const CubePosition &cPathPos)
{
	if (cPathPos == cTargetPos) {
		cpLongPath->push_front (cPathPos);
		return (true);
	}

	if (uiRecursionStepsLeft == 0) {
		return (false);
	}
	
	uint8_t i;
	if (cpUsedCubesModel->isSet (cPathPos)) {
		return (false);
	} else {
		cpUsedCubesModel->set (cPathPos, true);
	}

	{
		Cube cWayBlocked;
		if (! cpObstacleModel->get (cPathPos, cWayBlocked)) {
			return (false);
		}
		if (cWayBlocked.uiValue != 0) {
			return (false);
		}
	}

	uint8_t uiDirectionPriorities[6];
	calcDirectionPriorities (uiDirectionPriorities, cPathPos);

	for (i = 0; i < 6; i++) {
		if (nextCubeStep (uiRecursionStepsLeft - 1, nextPathPos (uiDirectionPriorities[i], cPathPos))) {
			cpLongPath->push_front (cPathPos);
			return (true);
		}
	}
	return (false);
}

void PathFinder :: calcDirectionPriorities (uint8_t *uiaPrioArray, const CubePosition &cPathPos)
{
	uint8_t i, j;
	double daDistances[6];
	bool baWrittenPrios[6];
	double dLowestDistance;
	uint8_t uiLowestDistancePos = 0;
	CubePosition cNextPathPos;
	for (i = 0; i < 6; i++) {
		cNextPathPos = nextPathPos (i, cPathPos);
		daDistances[i] = cNextPathPos.distance (cTargetPos);
		baWrittenPrios[i] = false;
	}
	for (i = 0; i < 6; i++) {
		dLowestDistance = __DBL_MAX;
		for (j = 0; j < 6; j++) {
			if (baWrittenPrios[j] == false) {
				if (daDistances[j] < dLowestDistance) {
					uiLowestDistancePos = j;
					dLowestDistance = daDistances[j];
				}
			}
		}
		baWrittenPrios[uiLowestDistancePos] = true;
		*(uiaPrioArray + i) = uiLowestDistancePos;
	}
}

CubePosition PathFinder :: nextPathPos (const uint8_t uiDirection, const CubePosition &cPathPos)
{
	CubePosition cNextCube = cPathPos;
	switch (uiDirection) {
		case 0: {
			cNextCube.iXPos++;
			break;
		}
		case 1: {
			cNextCube.iXPos--;
			break;
		}
		case 2: {
			cNextCube.iYPos++;
			break;
		}
		case 3: {
			cNextCube.iYPos--;
			break;
		}
		case 4: {
			cNextCube.iZPos++;
			break;
		}
		case 5: {
			cNextCube.iZPos--;
			break;
		}
		default: {
			cerr << "kann NIE passieren" << endl;
			break;
		}
	}
	return (cNextCube);
}

void PathFinder :: calcShortPath ()
{
	int32_t iPathLength = cpLongPath->size ();
	CubePosition *capPath = new CubePosition[iPathLength];
	int32_t *iapReducedDistance = new int32_t[iPathLength];
	DynamicBitMap cPathNeighbours;

	int32_t i = 0, j;
	int8_t uiPathNeighbours;
	int32_t iManhattanDistance;
	bool bPenalty;
	uint32_t uiSkip = 0;
	CubePath::iterator iPathIt;
	cout << "  list to map...         ";
	for (iPathIt = cpLongPath->begin (); iPathIt != cpLongPath->end (); iPathIt++) {
		capPath[i] = *iPathIt;
		iapReducedDistance[i] = 0;
		i++;
	}
	cout << "done" << endl << "  insert path to map...  ";
	
	for (i = 0; i < iPathLength; i++) {
		cPathNeighbours.set (capPath[i], true);
	}

	cout << "done" << endl << "  find neighbours...     ";
	for (i = 0; i < iPathLength; i++) {
		uiPathNeighbours = 0;
		for (j = 0; j < 6; j++) {
			if (cPathNeighbours.isSet (nextPathPos (j, capPath[i]))) {
				uiPathNeighbours++;
			}
		}
		if (uiPathNeighbours <= 2) {
			uiSkip++;
			iapReducedDistance[i] = 0;
		} else {
			j = 0;
			while (j < i) {
				iManhattanDistance = capPath[i].manhattanDistance (capPath[j]);
				if (iManhattanDistance == 1) {
					iapReducedDistance[i] = i - j - 1;
					break;
				}
				j += iManhattanDistance - 1;
			}

		}
	}
	cout << "done" << endl << "  reduce cubes...        ";

	i = iPathLength - 1;
	
	while (i >= 0) {
		cpPath->push_front (capPath[i]);
		bPenalty = false;
		if (iapReducedDistance[i] != 0) {
			for (j = i - iapReducedDistance[i] + 1; j < i; j++) {
				if (iapReducedDistance[j] > iapReducedDistance[i]) {
					bPenalty = true;
				}
			}
			if (bPenalty) {
				i--;
			} else {
				i -= iapReducedDistance[i] + 1;
			}
		} else {
			i--;
		}
	}
	cout << "done" << endl;

	delete[] capPath;
	delete[] iapReducedDistance;
}

#endif
