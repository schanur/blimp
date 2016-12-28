#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/select.h>
#include <iostream>
//#include <string>

void reader () {
	int fd1, fd2, maxfd;
	fd_set readfs;
	fd1 = open("/dev/ttyS1", O_RDONLY);
	//fd2 = open("/dev/ttyS2", O_RDWR );
	//if (fd1 < fd2) {maxfd = fd2 + 1;} else {maxfd = fd1 + 1;}
	while (1){
		FD_SET (fd1, &readfs);
		//FD_SET (fd2, &readfs);
		select(fd1 + 1,&readfs,NULL,NULL,NULL);
		if (FD_ISSET(fd1, &readfs)) {
			//std::cout <<  << std::endl;
			
		}
		//if (FD_ISSET(fd2, &readfs)) std::cout << "3333" << std::endl;
	}
}

void writer () {
	int fd1;
	char baum[2] = "4";
	
	fd1 = open("/dev/ttyS1", O_WRONLY);
	write(fd1, baum, 1); 
}

void forker () {
	int pid;
	pid = fork();
	if (pid == 0) {
		reader();
	} else {
		int pid2;
		pid2 = fork();
		if (pid2 == 0) {
			writer();
		}
	}

}

int main (void) {
	
	
	forker();
	while (1){
		usleep(1);
	}
	return 0;
}
