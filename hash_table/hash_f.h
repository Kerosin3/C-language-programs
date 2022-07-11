
#ifndef HASH_F
#define HASH_F 
#include <stdint.h>
#include <stdio.h>
#include <tgmath.h>
#include <stdlib.h>
//#include "BSD_strings.c"
#define SALT 15
unsigned long long calc_hash(char*);
enum flag_empty {non_empty,empty};


typedef struct {
	unsigned long long id; //aka hash
	char* key;
	unsigned long value;
} record;

typedef struct{
	unsigned long current_size;
	unsigned long max_size;
	record** start_record;
} record_storage;

record init_a_record();
record_storage init_storage();
unsigned try_append_to_storage(record_storage*,record);
void storage_destroy(record_storage*);
unsigned check_position(record_storage*,record,unsigned long);

void set_a_record(record*,char*);
//record get_a_record(char* key);
void test0();
//unsigned append_a_record_to_storage(record_storage*,record);

#endif /* ifndef HASH_F */
