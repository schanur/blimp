#define _REENTRANT 1

//#include <stdio.h>
//#include <stdlib.h>
#include <pthread.h>
//#include <stdlib>
//#include <stdio>
#include <string>
#include <iostream>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "SerialConnection.cpp"

void *rs232_reader( void *ptr ) 
//void rs232_reader ()
{
    cerr << "rs232_reader start" << endl;
    SerialConnection ser (__DEV_GPS, __SERCON_MODE_ASCII);
    while (1)
    {
	while (ser.newDataArrived () == false)
	{
	    //pthread_yield ();
	    //sleep(1);
	}
	cerr << ser.getData() << endl;
    }
    
    cerr << "rs232_reader end" << endl;

}

void *server (void *ptr)
{
    cerr << "server start" << endl;
    
    while (1) {
	//sleep (1);
	//cerr << "bla" << endl;
	int *innt = new int(2);
	delete innt;
    }
    
    
    
    cerr << "server end" << endl;
}

int main()
{
    // allocate shared memory
    int shm_id = shmget (5, 100, IPC_CREAT | SHM_R | SHM_W);
    if (shm_id == -1) {
	cerr << "error: shmget IPC_CREAT" << endl;
    } 

    // id -> pointer
    void *shm_data = shmat (shm_id, NULL, 0);
    
    // write
    *(int *) shm_data = 5555;
    
    
    sleep (10);
    
    // detach
    if (shmdt (shm_data) != 0) {
	cerr << "error: shmdt" << endl;
    }
    
    // delete
    if ((shmctl (shm_id, IPC_RMID, NULL)) == -1) {
	cerr << "error: shmctl IPC_RMID" << endl;
    }
    
    
    
    pthread_t thread1, thread2;
    char *message1 = "Thread 1";
    char *message2 = "Thread 2";
    int  iret1, iret2;

    /* Create independent threads each of which will execute function */

    iret1 = pthread_create( &thread1, NULL, rs232_reader, (void*) message1);
    iret2 = pthread_create( &thread2, NULL, server, (void*) message2);

     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */

     pthread_join( thread1, NULL);
     pthread_join( thread2, NULL); 

     //printf("Thread 1 returns: %d\n",iret1);
     //printf("Thread 2 returns: %d\n",iret2);
     exit(0);
}
