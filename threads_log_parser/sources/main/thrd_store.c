#include "thrd_store.h"
#include <stdlib.h>
#include <threads.h>

void process_data(int* fds,unsigned n_thrd){
	thrd_t threads_pool[n_thrd];
	int tc_ret;
	for (size_t i = 0; i<n_thrd; i++) {
		tc_ret = thrd_create(&threads_pool[i], (thrd_start_t) func,(void*) arg );
		if (tc_ret == thrd_error){
			printf("error while %d thread creation\n",i);
			exit(1);
		}
	}
	for (size_t j = 0; j < n_thrd;j++) {
		thrd_join(threads_pool[j],0);
	}
	thrd_exit(EXIT_SUCCESS);

}


