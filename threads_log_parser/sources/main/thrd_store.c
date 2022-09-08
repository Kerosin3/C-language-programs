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
	FILE*  assoc_fd;
} storage_cont;

void wrap_string_parse(storage_cont* g_storage){
	signed long long total_bytes = parse_string(g_storage->assoc_fd, g_storage->url_storage , g_storage->refer_storage);

	total_bytes+= total_bytes;

	mtx_lock(&mtx_murl_storage);	
	merge_structs(g_storage->main_storage_url, g_storage->url_storage);
	mtx_unlock(&mtx_murl_storage);

	mtx_lock(&mtx_mrefer_storage);
	merge_structs(g_storage->main_storage_refer, g_storage->refer_storage);
	mtx_unlock(&mtx_murl_storage);

	thrd_exit(0);
}

void process_data(int* fds){
	unsigned n_thrd = 0;
	    while ( (fds[n_thrd] != -1  )  ){
		    n_thrd++;
	}
	mtx_init(&mtx_mrefer_storage, 0);
	mtx_init(&mtx_murl_storage, 0);

	printf("number of threads %u \n",n_thrd);
	thrd_t threads_pool[n_thrd]; // create threads
	
	storage_url main_storage_url = create_url_storage();
	storage_url main_storage_refer = create_url_storage();

	size_t i = 0;
	while ( (fds[i] != -1  )  ){
		    printf("fd is %d\n",fds[i]);
		    storage_cont t_storage_cont;
		    t_storage_cont.main_storage_refer = &main_storage_refer;//assign main
		    t_storage_cont.main_storage_url = &main_storage_url;   //assign main
		    
		    storage_url t_url_storage = create_url_storage();
		    storage_url t_refer_storage = create_url_storage();

		    t_storage_cont.refer_storage = &t_url_storage; // assign thrd storages
		    t_storage_cont.url_storage = &t_refer_storage;  // assign thrd storages
			
		    t_storage_cont.assoc_fd = fds[i]; // assign fd

		    int tc_ret = thrd_create(&threads_pool[i], (thrd_start_t) wrap_string_parse,(void*) &t_storage_cont );
		    if (tc_ret == thrd_error){
			printf("error while %d thread creation\n",i);
			exit(1);
		    }
		    i++;

	    }

	for (size_t j = 0; j < n_thrd;j++) {
		thrd_join(threads_pool[j],0);
	}
	destroy_url_storage(&main_storage_url);
	destroy_url_storage(&main_storage_refer);
	close_all_fd(fds);

}


