#ifndef __SERIALISEDMESSAGE_CPP__
#define __SERIALISEDMESSAGE_CPP__

#include "SerialisedMessage.h"

sSerialisedMsg :: sSerialisedMsg ()
{
	for (uint8_t i = 0; i < 8; i++) {
		text[i] = 0;
	}
}

#endif
