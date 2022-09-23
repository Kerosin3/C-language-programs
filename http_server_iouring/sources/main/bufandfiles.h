#ifndef BUFANDFILES
#define BUFANDFILES

#include "misc.h"
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>
#include <string.h>

#define BUFFER_SIZE 4096
#define MAX_CONNECTIONS 100

extern char *buffers;
extern size_t *buffer_lengths;
extern int *file_fds;

extern char **fds_to_send;

// inline char* client_buffer(int client_fd);
void setup_buffers(int nconnections);
void close_fd_to_send(int *base);

int get_files_in_dir(char *dirname);
#endif
