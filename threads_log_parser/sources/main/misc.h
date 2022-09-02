#ifndef MISC
#define MISC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_string(FILE* fp);

typedef struct {
	unsigned long count;
	char* a_str;
} a_url;

typedef struct {
	a_url** root_storage;
	unsigned current_size;
	unsigned max_size;
} storage_url;

a_url** cr_url_storage();


#endif
