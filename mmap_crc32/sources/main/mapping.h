#ifndef MAPPING
#define MAPPING

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <bits/types/struct_rusage.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <inttypes.h>
#include <sys/resource.h>
#include <string.h>

#define NUL (void*)0

int calc_hashcrc32();

#endif
