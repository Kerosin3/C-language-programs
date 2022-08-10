#ifndef HASH_F
#define HASH_F
#include "spookyhash_api.h"
#include <alloca.h>
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
//#include "BSD_strings.c"
#define SALT 19
enum flag_empty
{
    non_empty,
    empty
};
enum flag_written
{
    not_written,
    written,
    moved
};

typedef struct
{
    unsigned long long id; // aka hash
    char *key;
    unsigned long value;
    enum flag_written flag;
} record;

typedef struct
{
    unsigned long current_size;
    unsigned long max_size;
    record **start_record;
} record_storage;

record init_a_record();
record_storage init_storage(unsigned);

unsigned long long calc_hash(const char *);
unsigned try_append_to_storage(record_storage *, record);
void storage_destroy(record_storage *);
unsigned check_position(record_storage *, record *, unsigned long);
unsigned long get_value_v2(record_storage *storage,const char* in_string);
void set_a_record(record *, const char *);
void test0();

#endif /* ifndef HASH_F */
