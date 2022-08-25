#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <alloca.h>
#include <limits.h>
#include <setjmp.h>
#include <sys/syslog.h>
#include <tgmath.h>
#include <syslog.h>


int main(int argc, char *argv[])
{
	openlog("my test log", LOG_CONS | LOG_PID, LOG_DEBUG);
	syslog(LOG_DEBUG,"blablabaa"); 
	syslog(LOG_ERR,"ERROR!"); 
	syslog(LOG_ALERT,"ALERT!"); 
	syslog(LOG_INFO,"FSOME INFO");
	syslog(LOG_CRIT,"CRITICAL INFO");
	closelog();
	return 0 ;

}

