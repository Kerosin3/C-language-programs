#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <alloca.h>
#include <limits.h>
#include <pthread.h>



pthread_t trd0,trd1;

static size_t j;

void* trd0_fun(void* arg){
	int *some = (int*) arg;
	printf("thread 0 started!passed arg is %d\n",*some );
	unsigned long temp = 2;
	printf("trd0 value of j is %u\n",j);
	printf("thread0 finished working!\n");
	int retval = 11;
	*(int*)arg = 100500;
	pthread_exit((void*) retval);
}

void* trd1_fun(void* arg){
	printf("trd1 value of j is %u\n",j);
	pthread_exit((void*) 1);
}


int main(int argc, char *argv[])
{
	j = 0;
	int init_value = 666;
	printf("init value is %d\n",init_value);
	pthread_create(&trd0, (void*)0 , trd0_fun ,(void*) &init_value);
	pthread_create(&trd1, (void*)0 , trd1_fun ,(void*) &init_value);
	
	for (size_t i = 0; i<10000000; i++) {
		j+=i;
	}	
	printf("j final value is %u \n",j);
	void* ret = 0 ;
	pthread_join(trd0,(void**) &ret );
	pthread_join(trd1,(void**) &ret );
	printf("init value after is %d\n",init_value); //changed value!!!
	printf("main thread has finished! returned: %d\n", ( ret  ) );
	return 0;
}
