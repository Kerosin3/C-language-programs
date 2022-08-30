#ifndef PARSEJSON
#define PARSEJSON
#include <stdio.h>
#include <stdlib.h>
#include "jzon.h"
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <syslog.h>
#include <sys/syslog.h>

#define NUL (void*)0

char** paths_to_analyze();
void destroy_paths(char** pathz);
_Bool if_deamon();

#endif
