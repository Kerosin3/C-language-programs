#ifndef MISC
#define MISC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <time.h>

#define URL 1
#define REFERERENCES 2

typedef struct {
	unsigned long count;
	char* a_str;
} a_url;


typedef struct {
	a_url** root_storage;
	unsigned current_size;
	unsigned max_size;
} storage_url;

void get_10_most(storage_url* storage,int PARAM);
storage_url create_url_storage();
a_url* create_a_url(char*);
long int append_a_url(a_url* url,storage_url* storage);
long int append_url_if_nexistsV2(storage_url* storage,char* a_url_str);
long int append_url_if_nexists(storage_url* storage,char* a_url_str);
void destroy_url_storage(storage_url* storage);
void merge_structs(storage_url* main_storage,storage_url* a_storage);
signed long long parse_string(FILE* fp,storage_url*,storage_url*);
#endif
