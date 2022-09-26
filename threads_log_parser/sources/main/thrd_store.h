#ifndef THRD_STORE
#define THRD_STORE

#include "files.h"
#include "misc.h"
#include "string_parse.h"
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

void process_data(int *fds);
#endif
