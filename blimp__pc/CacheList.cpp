/* Autor: Bjoern Griebenow
 *
 */

#ifndef __CACHELIST_CPP__
#define __CACHELIST_CPP__

#include "CacheList.h"


template<class Identifier, class Value> 
void CacheList <Identifier, Value> :: init()
{
	uiUpperPos = 0;
	bapCacheEntryUsable = new bool[uiCacheSize];
	capIdentifier = new Identifier[uiCacheSize];
	capValue = new Value[uiCacheSize];
	uint32_t i;
	for (i = 0; i < uiCacheSize; i++) {
		bapCacheEntryUsable[i] = false;
	}
}

template<class Identifier, class Value> 
bool CacheList <Identifier, Value> :: getPosition (uint32_t &uiFoundPosition, const Identifier &cEntryToSearch)
{
	uint32_t i;
	uint32_t uiCurrentPosition;
	for (i = 0; i < uiCacheSize; i++) {
		uiCurrentPosition = (uiUpperPos + i) % (uiCacheSize);
		if (bapCacheEntryUsable[uiCurrentPosition] == true) {
			if (capIdentifier[uiCurrentPosition] == cEntryToSearch) {
				uiFoundPosition = uiCurrentPosition;
				assert (uiFoundPosition < uiCacheSize);
				return (true);
			}
		}
	}
	return (false);
}

template<class Identifier, class Value> 
void CacheList <Identifier, Value> :: insert (const Identifier &cNewIdentifier, const Value &cNewValue)
{
	if (uiUpperPos != 0) {
		uiUpperPos--;
	} else {
		uiUpperPos = uiCacheSize - 1;
	}
	assert (uiUpperPos < uiCacheSize);
	bapCacheEntryUsable[uiUpperPos] = true;
	capIdentifier[uiUpperPos] = cNewIdentifier;
	capValue[uiUpperPos] = cNewValue;
}

template<class Identifier, class Value> 
bool CacheList <Identifier, Value> :: search (const Identifier &cEntryToSearch, Value &cptrValue)
{
	uint32_t uiPosition;
	if (getPosition (uiPosition, cEntryToSearch)) {
		cptrValue = capValue[uiPosition];
		//cerr << "cache hit" << endl;
		return (true);
	}
	//cerr << "cache miss" << endl;
	return (false);
}

template<class Identifier, class Value> 
bool CacheList <Identifier, Value> :: remove (const Identifier &cEntryToDelete)
{
	uint32_t uiPosition;
	if (getPosition (uiPosition, cEntryToDelete)) {
		bapCacheEntryUsable[uiPosition] = false;
		return (true);
	}
	return (false);
}

template<class Identifier, class Value> 
bool CacheList <Identifier, Value> :: update (const Identifier &cEntryToUpdate, const Value &cNewValue)
{
	uint32_t uiPosition;
	if (getPosition (uiPosition, cEntryToUpdate)) {
		capValue[uiPosition] = cNewValue;
		return (true);
	}
	return (false);
}

template<class Identifier, class Value> 
CacheList <Identifier, Value> :: CacheList ()
{
	uiCacheSize = __CACHE_LIST_DEFAULT_SIZE;
	init ();
}

template<class Identifier, class Value> 
CacheList <Identifier, Value> :: CacheList (const uint32_t uiInitCacheSize)
{
	uiCacheSize = uiInitCacheSize;
	init ();
}

template<class Identifier, class Value> 
CacheList <Identifier, Value> :: ~CacheList ()
{
	delete [] bapCacheEntryUsable;
	delete [] capIdentifier;
	delete [] capValue;
}

#endif
