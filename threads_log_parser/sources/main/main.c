#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include "signal.h"

#define NUL (void*)0

typedef  signed pid_t;


int main(){
	
	pid_t pid;
	unsigned t = 10;
	unsigned child_pid = 0;
	fprintf(stdout,"current pid is %d \n",getpid());
	fprintf(stdout,"current user is %d \n",getuid());
	
	if  ( (pid = fork() ) < 0 ){
		perror("error fork execution\n");
	} else if (!pid){  // == 0 -> child!
		child_pid = getpid();
		fprintf(stdout,"child pid is %d \n",getpid());
		fprintf(stdout,"parent pid is %d \n",getppid());
		t++;
	} else { // sleep parent
		sleep(2);
	}
	fprintf(stdout,"value is %u \n",t);
	//kill(pid, SIGTERM);
	return 0;
	
}
