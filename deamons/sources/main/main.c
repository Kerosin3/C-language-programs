#include <bits/types/struct_rusage.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syslog.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <syslog.h>
#include <sys/times.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NUL (void*)0

typedef  signed pid_t;
typedef struct rusage rusage;
typedef struct timeval timeval;
typedef struct rlimit rlimit;


void self_mon(rusage *usage_p);
int main(){
	
	pid_t pid;
	rusage usage_p;
	rlimit rlim;
	struct sigaction sa;
	unsigned child_pid = 0;
	fprintf(stdout,"current pid is %d \n",getpid());
	self_mon(&usage_p);
	rlim.rlim_cur = 1024;
	rlim.rlim_max = 1024;
	if (setrlimit(RLIMIT_NOFILE, &rlim)!=0) fprintf(stderr,"cannot change file limits\n");
	
	if ( (getrlimit(RLIMIT_NOFILE, &rlim) < 0 )) { //-get max file descr n
			fprintf(stderr,"cannot get n of max files\n");
			exit(1);
			}
	openlog("test_log",LOG_CONS,LOG_DAEMON);
	umask(007);
	if  ( (pid = fork() ) < 0 ){
		perror("error fork execution\n");
	} else if (!pid){  // == 0 -> child!
		fprintf(stdout,"child pid is %d \n",getpid());
		fprintf(stdout,"parent pid is %d \n",getppid());
	
	} else { // sleep parent
		getrusage(RUSAGE_SELF, &usage_p);
		printf("system resources consumed: %lu usec \n",usage_p.ru_stime.tv_usec);
		printf("user resources consumed: %lu usec \n",usage_p.ru_utime.tv_usec);
		printf("finishing parent \n");
		exit(0);
	}
	//--child process code--//
	setsid(); // create seance
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP,&sa,NULL)<0) { // mask out sighup
		syslog(LOG_CRIT,"cannot set ignore sighup\n");
	}
	if ((pid=fork()) < 0 ){
		syslog(LOG_CRIT,"cannot fork the process\n");
		exit(1);
	} else if (pid != 0) {
		printf("finishing first child\n");
		exit(0); // finish parent
	}
	fprintf(stdout,"child 2 pid is %d \n",getpid());
	//child here	
	if (chdir("/") < 0) {
		syslog(LOG_CRIT,"cannot change home dir \n");
	}
	fprintf(stdout,"closing file descriptors\n");
	for (size_t i; i< rlim.rlim_max; i++) close(i);
	int fd0,fd1,fd2;
	fd0 = open("/dev/null",O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);
	if (fd0 != 0 || fd1 != 1 || fd2 !=2) {
		syslog(LOG_CRIT,"error with fd0-fd2 creation");
	}
	sleep(30);

}


void self_mon(rusage *usage_p){
	getrusage(RUSAGE_SELF, usage_p);
	//getrusage(RUSAGE_CHILDREN, &usage_p);
}
