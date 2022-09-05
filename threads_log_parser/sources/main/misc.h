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

storage_url create_url_storage();

a_url* create_a_url(char*);



int append_a_url(a_url* url,storage_url* storage);

void test(void);

#endif
