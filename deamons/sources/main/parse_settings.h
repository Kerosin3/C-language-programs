#ifndef PARSEJSON
#define PARSEJSON
#include <stdio.h>
#include <stdlib.h>
#include "jzon.h"
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define NUL (void*)0

char** paths_to_analyze(_Bool*);
void destroy_paths(char** pathz);

#endif
