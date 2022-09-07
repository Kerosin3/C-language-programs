#ifndef STRING_PARSE
#define STRING_PARSE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "misc.h"
#define MAX_LEN 9000


long int extract_bytes(char buf[static 1]);
char* extract_refer(char buf[static 1]);
char* find_url(char str[static 1]);
signed long long parse_string(FILE* fp,storage_url*,storage_url*);

#endif
