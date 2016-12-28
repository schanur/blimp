/* Autor: Bjoern Griebenow
 *
 * Die Klasse Dynamic3DMap implementiert
 * eine Dynamische Speicherstruktur
 * die fuer die Speicherung des Rastermodells
 * verwendet wird.
 *
 */

#ifndef __DYNAMIC_3D_MAP_H__
#define __DYNAMIC_3D_MAP_H__


#include <iostream>
#include <string>
#include <map>

#include <sys/types.h>

#include "CubePosition.cpp"
#include "CacheList.cpp"
#include "Array3D.cpp"

#define __DYNAMIC_3D_MAP__CACHE_USE	1
#define __DYNAMIC_3D_MAP__CACHE_SIZE	8



template <class ObjectType, int XDim, int YDim, int ZDim>
class Dynamic3DMap
{
	public: 
		Dynamic3DMap ();
		Dynamic3DMap (Dynamic3DMap &cInit3DMap);
		~Dynamic3DMap ();
		
		/// Frage einen Wert aus der Karte ab
		/// Wenn sich der Wert nicht in der Karte
		/// befindet, wird false zurueck gegeben.
		bool get (const CubePosition &cCubePos, ObjectType &cToMap);
		/// speichern eines neuen Werts oder
		/// ueberschreiben eines existierenden.
		void set (const CubePosition &cCubePos, const ObjectType &cToMap);
		/// Lösche einen Wert aus der Karte
		void erase (const CubePosition &cCubePos);
		/// Prüfe ob ein bestimmtes Element der
		/// Karte mit einem Wert belegt ist.
		bool isSet (const CubePosition &cCubePos);

	private:
		/// Definitionen der einzelnen 
		/// Dimensionsdatentypen sowie
		/// der Speicherstruktur zum
		/// Cachen der letzen Abfragen.
		typedef class Array3D<ObjectType, XDim, YDim, ZDim> ObjectArray;
		typedef class map<int32_t, ObjectArray*> ZDimMap;
		typedef class map<int32_t, ZDimMap*> YDimMap;
		typedef class map<int32_t, YDimMap*> XDimMap;
		typedef class CacheList<CubePosition, ObjectArray*> MapCache;		

		void getMapPosition (CubePosition &cMapPos, const CubePosition &cCubePos);
		void getOffsetPosition (CubePosition &cOffsetPos, const CubePosition &cCubePos);
		void getArrayPointer (ObjectArray **cpMapPos, const CubePosition &cCubePos);

		uint32_t uiMapPointerCacheSize;
		XDimMap *cpXDimMap;
		MapCache *cpMapCache;
		unsigned int uiXDimCount;
		unsigned int uiYDimCount;
		unsigned int uiZDimCount;
};

#endif
