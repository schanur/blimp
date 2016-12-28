#ifndef __PLATFORM_SPECIFICS_MASKROS_H__
#define __PLATFORM_SPECIFICS_MASKROS_H__

#ifdef __cplusplus
	#define __PLATFORM 1
#else
	#define __PLATFORM 2
#endif

#include "../blimp__pc/platform_specifics_blimp_pc.h"
#include "../blimp__atmega_mc/platform_specifics_atmega.h"

#endif