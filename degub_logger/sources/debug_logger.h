#ifndef DEBUG_LOGGER
#define DEBUG_LOGGER

#include <execinfo.h>
#include <unistd.h>
#include <fcntl.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <syslog.h>

#define DEBUG 0
#define INFO 1
#define WARNING 2
#define ERROR 3

#define write_to_log(...) wrap_gglog(__LINE__,__FILE__, __VA_ARGS__);

void wrap_gglog(int,char*, unsigned, char*);
int init_recording(char *filename);
void stop_recording();

#endif
