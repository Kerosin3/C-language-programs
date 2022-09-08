#include "thrd_store.h"
#include "misc.h"
#include <stdlib.h>
#include <threads.h>
#include <stdatomic.h>


atomic_llong total_bytes = 0;
mtx_t mtx_murl_storage;
mtx_t mtx_mrefer_storage;


typedef struct storage_cont{
	storage_url* main_storage_url;
	storage_url* main_storage_refer;
	storage_url* url_storage;
	storage_url* refer_storage;
	int  assoc_fd;
} storage_cont;

void wrap_string_parse(storage_cont* g_storage){
	printf("thread %lu fd is %d\n",thrd_current(),g_storage->assoc_fd);
	//signed long long total_bytesF = parse_string(g_storage->assoc_fd, g_storage->url_storage , g_storage->refer_storage);
	//printf("total bytes %lld\n",total_bytesF);
	//total_bytes+= total_bytesF;

	//mtx_trylock(&mtx_murl_storage);	
	//merge_structs(g_storage->main_storage_url, g_storage->url_storage);
	//mtx_unlock(&mtx_murl_storage);

	mtx_trylock(&mtx_mrefer_storage);
	merge_structs(g_storage->main_storage_refer, g_storage->refer_storage);
	mtx_unlock(&mtx_murl_storage);

	printf("addr thr is %p\n",g_storage);
	//free((void*) g_storage);

	thrd_exit(0);
}

void process_data(int* fds){
	unsigned n_thrd = 0;
	    while ( (fds[n_thrd] != -1  )  ){
		    n_thrd++;
	}
	//    n_thrd = 1;
	mtx_init(&mtx_mrefer_storage, 0);
	mtx_init(&mtx_murl_storage, 0);

	printf("number of threads %u \n",n_thrd);
	thrd_t threads_pool[n_thrd]; // create threads
	
	storage_url main_storage_url = create_url_storage();
	storage_url main_storage_refer = create_url_storage();
	storage_cont* spt[n_thrd];
	size_t i = 0;
	while ( (fds[i] != -1  )  ){
	//while ( ( i<n_thrd  )  ){
		    printf("LAUNCH THREAD\n");
		    storage_cont* t_storage_cont = malloc(sizeof(storage_cont*));
		    spt[i] = t_storage_cont;
		    printf("addr is %p\n",t_storage_cont);
		    t_storage_cont->main_storage_refer = &main_storage_refer;//assign main
		    t_storage_cont->main_storage_url = &main_storage_url;   //assign main
		    

		    storage_url* t_url_storage = malloc(sizeof(storage_url*));
		    *t_url_storage = create_url_storage();

		    storage_url* t_refer_storage = malloc(sizeof(storage_url*));
		    *t_refer_storage = create_url_storage();

		    t_storage_cont->refer_storage = t_url_storage; // assign thrd storages
		    t_storage_cont->url_storage = t_refer_storage;  // assign thrd storages
			
		    t_storage_cont->assoc_fd = fds[i]; // assign fd

		    int tc_ret = thrd_create(&threads_pool[i], (thrd_start_t) wrap_string_parse,(void*) t_storage_cont );
		    if (tc_ret == thrd_error){
			printf("error while %zu thread creation\n",i);
			exit(1);
		    }
		    i++;

	    }
		for (size_t j = 0; j < i;j++) {
		printf("waiting %lu \n",j);
		thrd_join(threads_pool[j],0);
	}

	destroy_url_storage(&main_storage_url);
	destroy_url_storage(&main_storage_refer);
	printf("finishing..\n");
	for (size_t jj = 0; jj<(i) ; jj++) {
		free(spt[jj]);
	}

	close_all_fd(fds);

}


