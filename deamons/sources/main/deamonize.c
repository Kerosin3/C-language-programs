#include "deamonize.h"
#include "deamon_magic.h"



static void self_mon(rusage *usage_p);

void deamonize(const char *){
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
	openlog("my_deamon_test",LOG_CONS | LOG_PID,LOG_DAEMON);
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
	//child code here	
	if (chdir("/") < 0) {
		syslog(LOG_CRIT,"cannot change home dir \n");
	}
	fprintf(stdout,"closing file descriptors\n");
	for (size_t i=0; i< rlim.rlim_max; i++) {
		close(i);
	}
	int fd0,fd1,fd2;
	fd0 = fd1 = fd2 = -1;
	fd0 = open("/dev/null",O_RDWR | 0666);
	if (fd0 < 0) syslog(LOG_ERR,"cannot open stdin fd");
	fd1 = dup(0);
	fd2 = dup(0);
	if (fd0 != 0 || fd1 != 1 || fd2 !=2) {
		syslog(LOG_CRIT,"error with fd0-fd2 creation fd0:%d,fd1:%d,fd2:%d",fd0,fd1,fd2);
	}
	syslog(LOG_INFO, "running deamon with pid %d",getpid() );
	test();
	sleep(50);
}


void self_mon(rusage *usage_p){
	getrusage(RUSAGE_SELF, usage_p);
	//getrusage(RUSAGE_CHILDREN, &usage_p);
}





