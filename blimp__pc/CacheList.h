/* Autor: Bjoern Griebenow
 *
 *
 * Die Klasse CacheList kann innerhalb anderer Datenstrukturen
 * mit einer hohen Suchlaufzeit (Bäume) verwendet werden, um den 
 * Zugriff auf die letzen n Elemente zu beschleunigen.
 * Der Performance Vorteil ergibt sich nur, wenn die Zugriffe
 * auf die dahinter liegende Datenstruktur eine geringe 
 * Streuung aufweisen
 */

#ifndef __CACHELIST_H__
#define __CACHELIST_H__

#include <sys/types.h>

#include "defines.h"

/// Anzahl der Cache Groesse wenn eine Instanz.
/// den parameterlosen Constructor verwendet.
#define __CACHE_LIST_DEFAULT_SIZE 8

using namespace std;

template <class Identifier, class Value>
class CacheList
{
	public: 
		CacheList ();
		CacheList (const uint32_t uiInitCacheSize);
		~CacheList ();

	
		/// Fügt ein neues Paar in den Cache ein.
		void insert (const Identifier &cNewIdentifier,
				const Value &cNewValue);

		/// Sucht einen Eintrag im Cache.
		/// false als Rueckgabewert entspricht einem Cache miss.
		bool search (const Identifier &cEntryToSearch,
				Value &cptrValue);

		/// Loescht das entsprechende Paar.
		/// Ist immer dann wichtig wenn der Original
		/// Speicherbereich geloescht werden soll.
		/// Ein vergessenes remove fuehrt dann
		/// zu einem segfault.
		bool remove (const Identifier &cEntryToDelete);

		/// Updated den Wert zu einem Schluessel.
		bool update (const Identifier &cEntryToUpdate, 
				const Value &cNewValue);



	private: 
		void init ();
		bool getPosition (uint32_t &uiFoundPosition,
				const Identifier &cEntryToSearch);
		uint32_t uiCacheSize;

		uint32_t uiUpperPos;
		bool *bapCacheEntryUsable;
		Identifier *capIdentifier;
		Value *capValue;
};

#endif

