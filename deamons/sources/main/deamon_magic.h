#ifndef MAGIC
#define MAGIC
#include <string.h>
#include <sys/syslog.h>
#include <sys/socket.h>
#include <sys/file.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include "parse_settings.h"

void test(const char**);
size_t calc_filesize(char pathname[static 1]);

#endif
