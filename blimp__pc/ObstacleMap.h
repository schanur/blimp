#ifndef __OBSTACLE_MAP_H__
#define __OBSTACLE_MAP_H__

#include "Cube.cpp"
#include "Dynamic3DMap.cpp"

#define __OBSTACLE_MAP__XDIM 32
#define __OBSTACLE_MAP__YDIM 32
#define __OBSTACLE_MAP__ZDIM 32

typedef class Dynamic3DMap<Cube, 
		__OBSTACLE_MAP__XDIM, 
		__OBSTACLE_MAP__YDIM, 
		__OBSTACLE_MAP__ZDIM> ObstacleMap;


#endif
