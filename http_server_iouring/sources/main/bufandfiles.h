#ifndef BUFANDFILES
#define BUFANDFILES

#include "misc.h"
#include <dirent.h>
#include <fcntl.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 4096
#define MAX_CONNECTIONS 1000
#define MAXFILESINTHEDIR 512

extern char *dir_name;

extern char *buffers;
extern char *filesinthedir;
extern size_t *buffer_lengths;
extern int *file_fds;

extern char **files_in_dir;

void wrap_destroy_buffer();

// inline char* client_buffer(int client_fd);
void setup_buffers(int nconnections);
void close_fd_to_send(int *base);

int get_files_in_dir(char *dirname);
#endif
