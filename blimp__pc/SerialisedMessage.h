#ifndef __SERIALISEDMESSAGE_H__
#define __SERIALISEDMESSAGE_H__

#include <sys/types.h>

struct sSerialisedMsg {
	sSerialisedMsg ();
	char text[8];
};

#endif
