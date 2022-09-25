#ifndef MISC
#define MISC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <time.h>
#include "khash.h"
#include "khash_setup.h"



#define kh_get_val(kname, hash, key, defVal) ({k=kh_get(kname, hash, key);(k!=kh_end(hash)?kh_val(hash,k):defVal);})


#define kh_set(kname, hash, key, val) ({int ret; k = kh_put(kname, hash,key,&ret); kh_value(hash,k) = val; ret;})

#define URL 1
#define REFERERENCES 2

extern mtx_t mtx_khash_store;

KHASH_MAP_INIT_STR(filemap_t, int)

extern khash_t(filemap_t)* file_map;

extern int* get_file(const char* someurl);

typedef struct {
	unsigned long count;
	char* a_str;
} a_url;

typedef struct {
	a_url** root_storage;
	unsigned current_size;
	unsigned max_size;
	int      khSerial;
	khash_t(khSerial)  tablemapfile;

} storage_url;

void get_10_most(storage_url* storage,int PARAM);
storage_url create_url_storage();
a_url* create_a_url(char*);
long int append_a_url(a_url* url,storage_url* storage);
long int append_url_if_nexistsV2(storage_url* storage,char* a_url_str);
long int append_url_if_nexists(storage_url* storage,char* a_url_str);
void destroy_url_storage(storage_url* storage);
void merge_structs(storage_url* main_storage,storage_url* a_storage);
#endif
