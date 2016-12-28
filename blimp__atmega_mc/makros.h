#ifndef __MAKROS_H
#define __MAKROS_H

/*#include <stdlib.h>
  #include <avr/io.h>
  #include <stdint.h>*/

#define __ENTER_CRITICAL_SECTION	unsigned char _sreg = SREG; cli()
#define __LEAVE_CRITICAL_SECTION	SREG = _sreg

#endif
