#ifndef PARSEJSON
#define PARSEJSON
#include <stdio.h>
#include <stdlib.h>
#include "jzon.h"
#include <string.h>
#include <assert.h>

#define NUL (void*)0

char** paths_to_analyze();
void destroy_paths(char** pathz);

#endif
