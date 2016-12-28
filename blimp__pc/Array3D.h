/* Autor: Bjoern Griebenow
 *
 *
 * Die Klasse Array3D ist eine Klasse die eine feste
 * Anzahl von Elementen gleichen Typsin einem 
 * dreidimensionalen Array speichert. Die Struktur 
 * kennt die Anzahl von Elementen die tatsächlich 
 * beschrieben wurden.
 *
 * Die Klasse wird vor allem für die Realisierung der
 * dreidimensionalen Baumstruktur verwendet.
 */


#ifndef __ARRAY_3D_H__
#define __ARRAY_3D_H__

#include <bitset>
#include <stdexcept>

#include "CubePosition.cpp"

template <int XDim, int YDim, int ZDim>
int calcBitPosition (const CubePosition &cCubePos);

template <class ObjectType, int XDim, int YDim, int ZDim>
class Array3D
{
	public:
		Array3D ();
		bool get (const CubePosition &cCubePos, ObjectType &cFromArray);
		void set (const CubePosition &cCubePos, const ObjectType &cToArray);
		void erase (const CubePosition &cCubePos);
		bool isSet (const CubePosition &cCubePos);
		uint32_t count ();
	private:
		std::bitset<XDim * YDim * ZDim> cBitArray;
		ObjectType cObjArray[XDim][YDim][ZDim];
};

template <int XDim, int YDim, int ZDim>
class Array3D<bool, XDim, YDim, ZDim>
{
	public:
		Array3D ();
		bool get (const CubePosition &cCubePos, bool &cFromMap);
		void set (const CubePosition &cCubePos, const bool &cToMap);
		void erase (const CubePosition &cCubePos);
		bool isSet (const CubePosition &cCubePos);
		uint32_t count ();
	private:
		std::bitset<XDim * YDim * ZDim> cBitArray;
		std::bitset<XDim * YDim * ZDim> cObjArray;
};

// : public BitArray3D<XDim, YDim, ZDim>
#endif
