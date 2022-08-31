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
#include <sys/stat.h>
#include "parse_settings.h"
#include "deamonize.h"

#define DEAMON_SETUP 1
#define APP_SETUP    2

void start_server(int);
signed long calc_filesize(char pathname[static 1]);

#endif
