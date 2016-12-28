#ifndef __TIMING_C__
#define __TIMING_C__

#include "timing.h"

void wait_ms (uint16_t ms)
{
	for (; ms > 0; ms--) {
		uint16_t __c = 4000;
		__asm__ volatile (
		"1: sbiw %0,1" "\n\t"
		"brne 1b"
		: "=w" (__c)
		: "0" (__c)
	);
    }
}

#endif
