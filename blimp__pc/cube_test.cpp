//#include <stdio.h>
//#include <stdlib.h>

//#include <stdlib>
//#include <stdio>
//#include <string>
//#include <iostream>

#include <sys/types.h>

#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "Cube.cpp"
//#include "Dynamic3DMap.cpp"
#include "ObstacleMap.cpp"
#include "PathFinder.cpp"

using namespace std;

int main()
{
	ifstream ifRandom;
	ifRandom.open("/dev/urandom", ios_base::in);
 
	if (!ifRandom) {
		exit (1);      
	}
	int32_t i, j, k, l, m, n;

	//Dynamic3DMap<Cube, 8, 8, 8> cCubeMap;
	Cube cCube;
	//Cube cCubeGet;
	//cCube.uiValue = 0;
	CubePosition cCubePos;
	ObstacleMap cCubeMap;
	char c = 0;
	cout << "creating obstacle map... " << endl;
	for (i = 0; i < 65; i++) {
		for (j = 0; j < 65; j++) {
			for (k = 0; k < 65; k++) {
				for (l = 0; l < 8; l++) {
					for (m =0; m < 8; m++) {
						
						for (n = 0; n < 8; n++) {
							ifRandom.get (c);		
							if (c > 80) {
								cCube.uiValue = 1;
								//cout << 1;
							} else {
								cCube.uiValue = 0;
								//cout << 0;
							}
							cCubePos.iXPos = i * 8 + l + 1;
							cCubePos.iYPos = j * 8 + m + 1;
							cCubePos.iZPos = k * 8 + n + 1;
							cCubeMap.set (cCubePos, cCube);
						}
						(void) rand ();
					}
				}
			}
		}
		if (i % 5 == 0) {
			cout << ((double) (i + 1) / 65.) * 100. <<  "%" << endl;
		}
	}
	cout << "done" << endl;
	
	l = 0;
	/*for (k = 5; k < 19000; k += 500) {		
		cCube.uiValue = 1;
		for (i = 30 - l; i < 60  + l; i++) {
			for (j = 30 - l; j < 60 + l; j++) {
				cCubeMap.set (CubePosition (i, j, k), cCube);
			}
		}
		//cCube.uiValue = 0;
		//cCubeMap.set (CubePosition (40 + (rand () % 20), 40 + (rand () % 20), k), cCube);
		l++;
	}*/

	
	/*cCube.uiValue = 1;
	for (i = 20; i < 80; i++) {
		for (j =20; j < 80; j++) {
			cCubePos.iXPos = i;
			cCubePos.iYPos = j;
			cCubePos.iZPos = 50;
			cCubeMap.set (cCubePos, cCube);
		}
	}*/

	/*cCube.uiValue = 0;
	for (i = 0; i < 10; i++) {
		for (j =0; j < 10; j++) {
			for (k = 0; k < 10; k++) {
				cCubePos.iXPos = start.iXPos + i - 5;
				cCubePos.iYPos = start.iYPos + j - 5;
				cCubePos.iZPos = start.iZPos + k - 5;
				cCubeMap.set (cCubePos, cCube);
				cCubePos.iXPos = end.iXPos + i - 5;
				cCubePos.iYPos = end.iYPos + j - 5;
				cCubePos.iZPos = end.iZPos + k - 5;
				cCubeMap.set (cCubePos, cCube);
			}
		}
	}*/

	for (;;) {
		{
		CubePosition start((rand () % 490) + 5, (rand () % 490) + 5, (rand () % 490));
		CubePosition end((rand () % 490) + 5, (rand () % 490) + 5, (rand () % 490));
		cout << endl << "-----------------------------------" << endl;
		cout << endl << "start pos:" << endl;
		start.printPos ();
		cout << "end pos:" << endl;
		end.printPos ();
		CubePath cPath;
		PathFinder baum (&cCubeMap);
		(void) baum.searchPath (cPath, start, end);
		}
	}
	//sleep (5);
	/*CubePath::iterator iPathIt;
	int32_t l = 0;
	for (iPathIt = cPath.begin (); iPathIt != cPath.end (); iPathIt++) {
		cout << "Iteration Step: " << l << endl;
		iPathIt->printPos ();
		cout << endl;
		l++;
	}*/

	return(0);
}
