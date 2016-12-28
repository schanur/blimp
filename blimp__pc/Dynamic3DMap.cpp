/* Autor: Bjoern Griebenow
 *
 * Die Klasse Dynamic3DMap implementiert
 * eine Dynamische Speicherstruktur
 * die fuer die Speicherung des Rastermodells
 * verwendet wird.
 *
 */

#ifndef __DYNAMIC_3D_MAP_CPP__
#define __DYNAMIC_3D_MAP_CPP__

#include "Dynamic3DMap.h"


//#####################################################################

template <class ObjectType, int XDim, int YDim, int ZDim>
Dynamic3DMap <ObjectType, XDim, YDim, ZDim> :: Dynamic3DMap ()
{
	cpXDimMap = new XDimMap ();
	cpMapCache = new MapCache ();

	uiXDimCount = 0;
	uiYDimCount = 0;
	uiZDimCount = 0;
}

template <class ObjectType, int XDim, int YDim, int ZDim>
Dynamic3DMap <ObjectType, XDim, YDim, ZDim> :: Dynamic3DMap (Dynamic3DMap &cInitDynamic3DMap)
{

}

template <class ObjectType, int XDim, int YDim, int ZDim>
Dynamic3DMap <ObjectType, XDim, YDim, ZDim> :: ~Dynamic3DMap ()
{
	class XDimMap::iterator iXDimIt;
	YDimMap *cpYDimMap;
	class YDimMap::iterator iYDimIt;
	ZDimMap *cpZDimMap;
	class ZDimMap::iterator iZDimIt;
	for (iXDimIt = cpXDimMap->begin (); iXDimIt != cpXDimMap->end (); iXDimIt++) {
		uiXDimCount--;
		cpYDimMap = iXDimIt->second;
		iYDimIt = cpYDimMap->begin ();
		for (iYDimIt = cpYDimMap->begin (); iYDimIt != cpYDimMap->end (); iYDimIt++) {
			uiYDimCount--;
			cpZDimMap = iYDimIt->second;
			iZDimIt = cpZDimMap->begin ();
			for (iZDimIt = cpZDimMap->begin (); iZDimIt != cpZDimMap->end (); iZDimIt++) {
				uiZDimCount--;
				delete (iZDimIt->second);
			}
			delete cpZDimMap;
		}
		delete cpYDimMap;
	}
	delete cpXDimMap;
	delete cpMapCache;
	assert (uiXDimCount == 0);
	assert (uiYDimCount == 0);
	assert (uiZDimCount == 0);
}

/*template <class ObjectType>
CubeMemoryMapElement* Dynamic3DMap <ObjectType> :: getCubeMemoryMapPtr (const CubePosition &cCubeToSearch) 
{
	throw ();
	return (NULL);
}*/

template <class ObjectType, int XDim, int YDim, int ZDim>
bool Dynamic3DMap <ObjectType, XDim, YDim, ZDim> :: get (const CubePosition &cCubePos, ObjectType &cpFromMap)
{
	CubePosition cMapPos, cOffsetPos;
	getMapPosition (cMapPos, cCubePos);
	getOffsetPosition (cOffsetPos, cCubePos);
	ObjectArray *cpArray;// = 0;
	getArrayPointer (&cpArray, cMapPos);
	//assert (cpArray != 0);
	
	return (cpArray->get (cOffsetPos, cpFromMap));
}

template <class ObjectType, int XDim, int YDim, int ZDim>
void Dynamic3DMap <ObjectType, XDim, YDim, ZDim> :: set (const CubePosition &cCubePos, const ObjectType &cpToMap)
{
	CubePosition cMapPos, cOffsetPos;
	getMapPosition (cMapPos, cCubePos);
	getOffsetPosition (cOffsetPos, cCubePos);
	ObjectArray *cpArray;// = 0;
	getArrayPointer (&cpArray, cMapPos);
	//assert (cpArray != 0);
	
	cpArray->set (cOffsetPos, cpToMap);
}

template <class ObjectType, int XDim, int YDim, int ZDim>
void Dynamic3DMap <ObjectType, XDim, YDim, ZDim> :: erase (const CubePosition &cCubePos)
{
	CubePosition cMapPos, cOffsetPos;
	getMapPosition (cMapPos, cCubePos);
	getOffsetPosition (cOffsetPos, cCubePos);
	ObjectArray *cpArray;// = 0;
	getArrayPointer (&cpArray, cMapPos);
	//assert (cpArray != 0);

	cpArray->erase (cOffsetPos);
	if (cpArray->count () != 0) { return; }
	class XDimMap::iterator iXDimIt = cpXDimMap->find (cCubePos.iXPos);
	if (iXDimIt != cpXDimMap->end ()) {
		YDimMap *cpYDimMap = iXDimIt->second;
		class YDimMap::iterator iYDimIt = cpYDimMap->find (cCubePos.iYPos);
		if (iYDimIt != cpYDimMap->end ()) {
			ZDimMap *cpZDimMap = iYDimIt->second;
			class ZDimMap::iterator iZDimIt = cpZDimMap->find (cCubePos.iZPos);
			if (iZDimIt != cpZDimMap->end ()) {
				delete iZDimIt->second;
				uiZDimCount--;
				cpZDimMap->erase (iZDimIt);
				if (cpZDimMap->size () == 0) {
					delete iYDimIt->second;
					uiYDimCount--;
					cpYDimMap->erase (iYDimIt);
					if (cpYDimMap->size () == 0) {
						delete iXDimIt->second;
						uiXDimCount--;
						cpXDimMap->erase (iXDimIt);
					}
				}
				cpMapCache->remove (cCubePos);
			}
		}
	}
}

template <class ObjectType, int XDim, int YDim, int ZDim>
bool Dynamic3DMap <ObjectType, XDim, YDim, ZDim> :: isSet (const CubePosition &cCubePos)
{
	CubePosition cMapPos, cOffsetPos;
	getMapPosition (cMapPos, cCubePos);
	getOffsetPosition (cOffsetPos, cCubePos);
	ObjectArray *cpArray;// = 0;
	getArrayPointer (&cpArray, cMapPos);
	
	return (cpArray->isSet (cOffsetPos));
}

template <class ObjectType, int XDim, int YDim, int ZDim>
void Dynamic3DMap <ObjectType, XDim, YDim, ZDim> :: getMapPosition (CubePosition &cMapPos, const CubePosition &cCubePos)
{
	cMapPos.iXPos = cCubePos.iXPos / XDim;
	cMapPos.iYPos = cCubePos.iYPos / YDim;
	cMapPos.iZPos = cCubePos.iZPos / ZDim;
}

template <class ObjectType, int XDim, int YDim, int ZDim>
void Dynamic3DMap <ObjectType, XDim, YDim, ZDim> :: getOffsetPosition (CubePosition &cOffsetPos, const CubePosition &cCubePos)
{
	cOffsetPos.iXPos = cCubePos.iXPos % XDim;
	cOffsetPos.iYPos = cCubePos.iYPos % YDim;
	cOffsetPos.iZPos = cCubePos.iZPos % ZDim;
	if (cOffsetPos.iXPos < 0) {
		cOffsetPos.iXPos += XDim;
	}
	if (cOffsetPos.iYPos < 0) {
		cOffsetPos.iYPos += YDim;
	}
	if (cOffsetPos.iZPos < 0) {
		cOffsetPos.iZPos += ZDim;
	}

}

template <class ObjectType, int XDim, int YDim, int ZDim>
void Dynamic3DMap <ObjectType, XDim, YDim, ZDim> :: getArrayPointer (ObjectArray **cpObjArray, const CubePosition &cMapPos)
{
	//ObjectArray *cpMemLocation;
	
	if (! cpMapCache->search (cMapPos, *cpObjArray)) {
		class XDimMap::iterator iXDimIt = cpXDimMap->find (cMapPos.iXPos);
		if (iXDimIt == cpXDimMap->end ()) {
			uiXDimCount++;
			cpXDimMap->insert (make_pair (cMapPos.iXPos, new YDimMap ()));
			iXDimIt = cpXDimMap->find (cMapPos.iXPos);
			//cerr << "Adding XDimMemMapEntry with key value: " << cMapPos.iXPos << endl;
		}
		YDimMap *cpYDimMap = iXDimIt->second;
		class YDimMap::iterator iYDimIt = cpYDimMap->find (cMapPos.iYPos);
		if (iYDimIt == cpYDimMap->end ()) {
			uiYDimCount++;
			cpYDimMap->insert (make_pair (cMapPos.iYPos, new ZDimMap ()));
			iYDimIt = cpYDimMap->find (cMapPos.iYPos);
			//cerr << "Adding YDimMemMapEntry with key value: " << cMapPos.iYPos << endl;
		}
		ZDimMap *cpZDimMap = iYDimIt->second;
		class ZDimMap::iterator iZDimIt = cpZDimMap->find (cMapPos.iZPos);
		if (iZDimIt == cpZDimMap->end ()) {
			uiZDimCount++;
			*cpObjArray = new ObjectArray ();
			//cerr << cpObjArray << endl;
			cpZDimMap->insert (make_pair (cMapPos.iZPos, *cpObjArray));
			//cerr << "Adding ZDimMemMapEntry with key value: " << cMapPos.iZPos << endl;
		} else {
			*cpObjArray = iZDimIt->second;
		}
		cpMapCache->insert (cMapPos, *cpObjArray);
	}
}

#endif
