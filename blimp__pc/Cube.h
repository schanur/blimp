/* Autor: Bjoern Griebenow
 *

 * Cube Isst das zentrale Element der
 * Hindernisekennung.
 * In ihm werden die verschieden
 * Informationengespeichert, die fuer
 * die Rasterkarte relevant ist.
 */

#ifndef __CUBE_H__
#define __CUBE_H__

//#include <sys/types.h>
#include "inttypes.h"

//#include "defines.h"

#define __CUBE_OCCUPIED 0x00

using namespace std;


class Cube
{
	public:
		uint8_t uiValue;
};


#endif
