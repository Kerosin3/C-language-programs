#ifndef THRD_STORE
#define THRD_STORE

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <stdatomic.h>
#include "files.h"
#include "string_parse.h"
#include "misc.h"

void process_data(int* fds);
#endif
