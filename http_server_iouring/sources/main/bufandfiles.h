#ifndef BUFANDFILES
#define BUFANDFILES

#include "misc.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096
#define MAX_CONNECTIONS 100

extern char *buffers;
extern size_t *buffer_lengths;
extern int *file_fds;

// inline char* client_buffer(int client_fd);
void setup_buffers(int nconnections);

#endif
