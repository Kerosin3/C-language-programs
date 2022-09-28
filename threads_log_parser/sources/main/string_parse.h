#ifndef STRING_PARSE
#define STRING_PARSE
#include "misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sendfile.h>

#define MAX_LEN 9000

long int extract_bytes(char buf[static 1]);
char *extract_refer(char buf[static 1]);
char *find_url(char str[static 1]);
signed long long parse_string(int, storage_url *, storage_url *);

#endif
