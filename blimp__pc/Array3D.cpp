#ifndef __ARRAY_3D_CPP__
#define __ARRAY_3D_CPP__

#include "Array3D.h"

template <int XDim, int YDim, int ZDim>
int calcBitPosition (const CubePosition &cCubePos)
{
	return (cCubePos.iXPos * YDim * ZDim
		+ cCubePos.iYPos * ZDim
		+ cCubePos.iZPos);
}

template <class ObjectType, int XDim, int YDim, int ZDim>
Array3D <ObjectType, XDim, YDim, ZDim> :: Array3D ()
{
	//cerr << "Array3D: object array mode" << endl;
}

template <int XDim, int YDim, int ZDim>
Array3D <bool, XDim, YDim, ZDim> :: Array3D ()
{
	//cerr << "Array3D: bitmap mode" << endl;
}

template <class ObjectType, int XDim, int YDim, int ZDim>
bool Array3D <ObjectType, XDim, YDim, ZDim> :: get (const CubePosition &cCubePos, ObjectType &cFromArray)
{
	if (cBitArray.test (calcBitPosition<XDim, YDim, ZDim> (cCubePos))) {
		cFromArray = cObjArray[cCubePos.iXPos]
				[cCubePos.iXPos]
				[cCubePos.iXPos];
		return (true);
	}
	return (false);
}

template <int XDim, int YDim, int ZDim>
bool Array3D <bool, XDim, YDim, ZDim> :: get (const CubePosition &cCubePos, bool &cFromArray)
{
	int iBitPos = calcBitPosition<XDim, YDim, ZDim> (cCubePos);
	if (cBitArray.test (iBitPos)) {
		cFromArray = cObjArray.test (iBitPos);
		return (true);
	}
	return (false);
}

template <class ObjectType, int XDim, int YDim, int ZDim>
void Array3D <ObjectType, XDim, YDim, ZDim> :: set (const CubePosition &cCubePos, const ObjectType &cToArray)
{
	cBitArray.set (calcBitPosition<XDim, YDim, ZDim> (cCubePos), 1);
	cObjArray[cCubePos.iXPos]
			[cCubePos.iXPos]
			[cCubePos.iXPos]
			= cToArray;
}

template <int XDim, int YDim, int ZDim>
void Array3D <bool, XDim, YDim, ZDim> :: set (const CubePosition &cCubePos, const bool &cToArray)
{
	int iBitPos = calcBitPosition<XDim, YDim, ZDim> (cCubePos);
	cBitArray.set (iBitPos, 1);
	if (cToArray) {
		cObjArray.set (iBitPos, 1);
	} else {
		cObjArray.set (iBitPos, 0);
	}
}

template <class ObjectType, int XDim, int YDim, int ZDim>
void Array3D <ObjectType, XDim, YDim, ZDim> :: erase (const CubePosition &cCubePos)
{
	cBitArray.set (calcBitPosition<XDim, YDim, ZDim> (cCubePos), 0);
}

template <class ObjectType, int XDim, int YDim, int ZDim>
bool Array3D <ObjectType, XDim, YDim, ZDim> :: isSet (const CubePosition &cCubePos)
{
	return (cBitArray.test (calcBitPosition<XDim, YDim, ZDim> (cCubePos)));
}

template <int XDim, int YDim, int ZDim>
bool Array3D <bool, XDim, YDim, ZDim> :: isSet (const CubePosition &cCubePos)
{
	return (cBitArray.test (calcBitPosition<XDim, YDim, ZDim> (cCubePos)));
}

/*template <int XDim, int YDim, int ZDim>
bool Array3D <bool, XDim, YDim, ZDim> :: isSet (const CubePosition &cCubePos)
{
	bool bPosIsSet = false;
	try {
		bPosIsSet = cBitArray.test (calcBitPosition<XDim, YDim, ZDim> (cCubePos));;
	} catch (std::out_of_range outOfRange) {
		cout << outOfRange.what () << endl;
		cout << "bitset size: " << cBitArray.size () << endl;
		cCubePos.printPos ();
		
	}
	return (bPosIsSet);
}*/

template <class ObjectType, int XDim, int YDim, int ZDim>
uint32_t Array3D <ObjectType, XDim, YDim, ZDim> :: count ()
{
	return (cBitArray.count ());
}

#endif
