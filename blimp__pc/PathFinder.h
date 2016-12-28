/* Autor: Bjoern Griebenow
 *
 * Algorithmus für das Finden
 * möglichst kurzer Wege auf
 * einer dreidimensionalen Rasterkarte.
 * Der Algorithmus arbeitet nicht optimal.
 * Das heisst er findet nicht zwangsläufig
 * den kürzesten Weg. Dafuer ist er sehr
 * sparsam mit dem Umgang von Speicher.
 * Der Algorithmus verwendet eine Heuristik,
 * um zu entscheiden, welche Richtungen
 * bei der Wegsuche zu einer kurzen
 * Route führen.
 * 
 */

#ifndef __PATH_FINDER_H__
#define __PATH_FINDER_H__

#include <list>


#include "signum.h"
#include "ObstacleMap.cpp"

#define __PATH_FINDER__MAX_RECURSION_DEPTH	4000000
//#define __PATH_FINDER__ALL_PATHS_CHECKED	0xfc
#define __DBL_MAX 				3333333.

using namespace std;


typedef class list<CubePosition> CubePath;

int8_t signum (int32_t a, int32_t b);

class PathFinder
{
	public:
		PathFinder (ObstacleMap *cpObstacleMap);
		
		bool searchPath (CubePath &cPath, const CubePosition &cStartPos, const CubePosition &cEndPos);
	private:
		typedef class Dynamic3DMap<bool, 8, 8, 8> DynamicBitMap;

		bool nextCubeStep (const uint32_t uiRecursionStepsLeft, const CubePosition &cPathPos);
		void calcDirectionPriorities (uint8_t *uiaPrioArray, const CubePosition &cPathPos);
		CubePosition nextPathPos (const uint8_t uiDirection, const CubePosition &cPathPos);
		void calcShortPath ();

		ObstacleMap *cpObstacleModel;
		DynamicBitMap *cpUsedCubesModel;
		CubePath *cpPath, *cpLongPath;
		CubePosition cTargetPos;	
};

#endif
