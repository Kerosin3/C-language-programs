#ifndef DEAMONIZE
#define DEAMONIZE
#include <bits/types/struct_rusage.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syslog.h>
#include <unistd.h>
#include <errno.h>
#include <features.h>
#include <signal.h>
#include <sys/types.h>
#include <syslog.h>
#include <sys/times.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "deamon_magic.h"
#include "parse_settings.h"
#include <threads.h>
#include <stdatomic.h>
typedef  signed pid_t;
typedef struct rusage rusage;
typedef struct timeval timeval;
typedef struct rlimit rlimit;


void deamonize();

#endif
