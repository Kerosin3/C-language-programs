#ifndef MISC
#define MISC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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



long int append_a_url(a_url* url,storage_url* storage);
void parse_string(FILE* fp,storage_url*);

void test(void);
void test2(FILE* fp,FILE*);

#endif
