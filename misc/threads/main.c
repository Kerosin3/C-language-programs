#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <alloca.h>
#include <limits.h>
#include <threads.h>
#include <stdatomic.h>


typedef struct {
	int someint;
} strc;

atomic_llong shard_val = 0;

void somef(void* arg){
	strc* a_strct = (strc*) arg;
	printf("thread %lu, value is %d \n",thrd_current(),a_strct->someint);
	size_t tid = thrd_current();
	shard_val+=(unsigned)a_strct->someint;
	thrd_exit((int) tid);
}



int main(int argc, char *argv[])
{
	thrd_t thrd_pool[10];
	strc strct_pool[10];
	int result[10] = {0};

	int trd_ret=-1;
	for (size_t i = 0; i<10; i++) {
		strct_pool[i].someint= (size_t) i;
		trd_ret = thrd_create(&thrd_pool[i], (thrd_start_t) somef, (void*) &strct_pool[i] );
		if (trd_ret == thrd_error){
			printf("error while thread creation \n");
			exit(1);
		}
	}
	
	for (size_t i=0; i<10; i++) {
		thrd_join(thrd_pool[i], &result[i]);
	}
	printf("value common is %llu \n",shard_val);
	return 0;
}
