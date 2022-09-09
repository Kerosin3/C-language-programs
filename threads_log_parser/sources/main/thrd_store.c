#include "thrd_store.h"
#include "misc.h"
#include <stdlib.h>
#include <threads.h>
#include <stdatomic.h>
#include <stdbool.h>


atomic_llong total_bytes = 0;
mtx_t mtx_murl_storage;
mtx_t mtx_mrefer_storage;



typedef struct {
	int*         fds;
	int          n_files;
	thrd_t*      thr_pool;
	unsigned      n_thrd;
	mtx_t*       mtx_thr;
	bool        flag;
} arbitre_data;


typedef struct storage_cont{
	storage_url* main_storage_url;
	storage_url* main_storage_refer;
	storage_url* url_storage;
	storage_url* refer_storage;
	int  assoc_fd;
	mtx_t* mtx_done;
	bool  flags;

} storage_cont;

void wrap_string_parse(storage_cont* g_storage){
	printf("thread %lu fd is %d\n",thrd_current(),g_storage->assoc_fd);
	signed long long total_bytesF = parse_string(g_storage->assoc_fd, g_storage->url_storage , g_storage->refer_storage);
	total_bytes+= total_bytesF;

	mtx_lock(&mtx_murl_storage);
	merge_structs(g_storage->main_storage_url, g_storage->url_storage);
	mtx_unlock(&mtx_murl_storage);

	mtx_lock(&mtx_mrefer_storage);
	merge_structs(g_storage->main_storage_refer, g_storage->refer_storage);
	mtx_unlock(&mtx_mrefer_storage);

	mtx_lock(g_storage->mtx_done);
	g_storage->flags = true;
	printf(">>work done<<%d \n",g_storage->flags);
	mtx_unlock(g_storage->mtx_done);

	free((g_storage->url_storage));
	free((g_storage->refer_storage));
	free(g_storage);
	thrd_exit(1);
}


void process_data(int* fds){
	int n_files = 0;
	unsigned n_thrd = 0;
	    while ( (fds[n_files] != -1  )  ){
		    n_files++;
	}
	n_thrd = n_files;
	mtx_init(&mtx_mrefer_storage, mtx_plain); // init mtx
	mtx_init(&mtx_murl_storage, mtx_plain);  //init mtx
	

	printf("number of threads %u \n",n_thrd);
	
	thrd_t threads_pool[n_thrd]; // create threads
	
	mtx_t mtx_flags_done[n_thrd]; // create mutexes
	bool flags[n_thrd]; // create flags

	for (size_t i =0; i<n_thrd;i++) {
		mtx_init(&mtx_flags_done[i],mtx_plain);	//init mutexes
		flags[i]=false;  			//int flags
	}


/*				     
	thrd_t arbitre;
	arbitre_data arb_data;
	arb_data.n_thrd = n_thrd;
	arb_data.fds = fds;
	arb_data.n_files = n_files;
	arb_data.thr_pool = threads_pool;
	
	
	arb_data.mtx_thr = mtx_flags_done; // assign data arb
	arb_data.flag = flags;   		// assign flags arb
	*/
	storage_url main_storage_url = create_url_storage();
	storage_url main_storage_refer = create_url_storage();

	

	//int tc_ret = thrd_create(&arbitre, (thrd_start_t) decide,(void*) flag_work_done );

	size_t i = 0;
	while ( (fds[i] != -1  )  ){
		    if (fds[i] == -1) break; 
			

		    storage_cont* t_storage_cont = malloc(sizeof(storage_cont));
		    t_storage_cont->main_storage_refer = &main_storage_refer;//assign main
		    t_storage_cont->main_storage_url = &main_storage_url;   //assign main
		    

		    storage_url* t_url_storage = malloc(sizeof(storage_url));
		    *t_url_storage = create_url_storage();

		    storage_url* t_refer_storage = malloc(sizeof(storage_url));
		    *t_refer_storage = create_url_storage();

		    if (!t_storage_cont || !t_url_storage || !t_refer_storage ) exit(1);

		    t_storage_cont->refer_storage = t_url_storage; // assign thrd storages
		    t_storage_cont->url_storage = t_refer_storage;  // assign thrd storages
			
		    t_storage_cont->assoc_fd = fds[i]; // assign fd
		    t_storage_cont->mtx_done = &(mtx_flags_done[i]);
		    flags[i] = false;
		    t_storage_cont->flags = flags[i];

		    int tc_ret = thrd_create(&threads_pool[i], (thrd_start_t) wrap_string_parse,(void*) t_storage_cont );
		    if (tc_ret == thrd_error){
			printf("error while %zu thread creation\n",i);
			exit(1);
		    }
		    i++;

	    }
		for (size_t j = 0; j < n_thrd;j++) {
		int rez = -1;
		if (thrd_join(threads_pool[j],&rez)!=thrd_success){
			printf("error joining thread %lu\n",j);
		}
		printf("waiting %lu ,rez is %d \n",j,rez);
	}

	destroy_url_storage(&main_storage_url);
	destroy_url_storage(&main_storage_refer);

	printf("finishing..\n");

	close_all_fd(fds);

}



