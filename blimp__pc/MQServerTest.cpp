//#define _REENTRANT
#include "MessageQueueServer.cpp"
#include <stdlib.h>



int main (void) 
{

	MessageQueueServer  mqs;
	mqs.RunMessageQueueServer (123L);

	return (0);
}
