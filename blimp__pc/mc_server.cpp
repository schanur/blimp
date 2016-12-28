#define _REENTRANT 1
#define _PTHREADS 1
#define _POSIX_C_SOURCE 199309
#define _MULTI_THREADED

//#include <stdio.h>
//#include <stdlib.h>
#include <pthread.h>
//#include <stdlib>
//#include <stdio>
#include <string>
#include <iostream>

#include <sys/time.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "SerialConnection.cpp"
SerialConnection *ser;

#include "platform_specifics_blimp_pc.h"
#include "../shared_source/uart_protocol_handler.c"


//#include "Multiplexer.cpp"
//#include "DataExchange.cpp"

int8_t uartProtocolHandlePacket ()
{
	return (__SUCCESS);
}

void (*rs232Connector (void *ptr))
//void rs232_reader ()
{
	cerr << "rs232Connector start" << endl;
	ser = new SerialConnection (__DEV_MC, 9600, __SER_READ | __SER_WRITE);
	
	uartProtocolInitProtocolHandler ();
	char a;
	//int ProtocolStat = 0;
	//sleep (5);
	//pthread_cond_t a1;
	//pthread_mutex_t m1;
	struct timespec t1;
	t1.tv_sec = 0;
	t1.tv_nsec = 1;
	//pthread_mutex_init(&m1, NULL);
	//pthread_cond_init(&a1, NULL);
	while (1) {
		//(void) ser->getChar (&a);
		//cerr << a;
		//nanosleep(&t1, NULL);
		//(void) uartProtocolDoHandlerStep ();
		
		if (ser->getChar(&a) == __SUCCESS) {
			//cerr << a;
			//if (a == ':') {
				//ProtocolStat = 1;
			//}
		//}
		} else {
			//cerr << "9";
		}
		/*if (ser->putChar('5') == __SUCCESS) {
			cerr << "7";
		} else {
			cerr << "8";
		}*/
		
		///FIXME: geht nur wenn mc vorher schon läuft!!!!111elf
		//nanosleep(&t1, NULL); 
		//usleep (50);
	//	pthread_cond_timedwait(&a1, &m1, &t1);
	}

	//ser.setLineTerminator(string ("\0"));
	//cerr << "rs232Connector before while" << endl;
	/*char baum;
	while (1) {
		while (ser.getChar (&baum) == __ERROR)
		{
			//cerr << "rs232Connector: wait for data..." << endl;
			usleep (1);
		}
		cerr << baum;
    	}*/
    
	cerr << "rs232Connector stop" << endl;
}

void (*sharedMemoryConnector (void *ptr))
{
	cerr << "sharedMemoryConnector start" << endl;
    
	while (1) {
		usleep (1);
	}
	cerr << "sharedMemoryConnector end" << endl;
    
}

int main()
{

    
    
	pthread_t thread1, thread2;
	char *message1 = "Thread 1";
	char *message2 = "Thread 2";
	int  iret1, iret2;

	/* Create independent threads each of which will execute function */

	iret1 = pthread_create( &thread1, NULL, rs232Connector, (void*) message1);
	iret2 = pthread_create( &thread2, NULL, sharedMemoryConnector, (void*) message2);

	/* Wait till threads are complete before main continues. Unless we  */
	/* wait we run the risk of executing an exit which will terminate   */
	/* the process and all threads before the threads have completed.   */

	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL); 

	//printf("Thread 1 returns: %d\n",iret1);
	//printf("Thread 2 returns: %d\n",iret2);
	exit(0);
}
