#include <bits/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>

size_t get_timestamp(void* buffer){
	char date[32];
        time_t t = time(NULL);
	struct timeval ts;
	gettimeofday(&ts,NULL);
    	struct tm* tm = gmtime(&t);
    	strftime(date, sizeof(date), "%d/%m/%Y %H:%M:%S GMT", tm);
	int n = snprintf(buffer, strlen(date)+1, "%s", date);
	printf("%s\n",buffer);
	return n;
}

static long get_nanos(){
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	return (long) ts.tv_sec * 1000000000L +ts.tv_nsec;
}

int main(int argc, char *argv[]){
//	char datee[40] = {0};
//	get_timestamp(datee);
	
	long int ns;
	u_int64_t all;
	time_t sec;
	unsigned long one_bill = 1000000000L;
	struct timespec spec;
	
	clock_gettime(CLOCK_REALTIME,&spec);
	sec = spec.tv_sec;
	ns = spec.tv_nsec;
	printf("nanosec :%lu\n",all);
	size_t i = 0;
	for (;;){
		all = (u_int64_t) sec *  one_bill + (u_int64_t) ns;
		if (i==20) break;
		printf("nanosec value epoch %lu\n",all);
		i++;
	}
	return 0;
}
