#include "bufandfiles.h"

/*
 * setup buffers
 */



char *buffers;
size_t *buffer_lengths;
int *file_fds;

void setup_buffers(int nconnections)
{
    buffers = malloc(nconnections * BUFFER_SIZE);
    if (!buffers)
        die("malloc");

    buffer_lengths = malloc(nconnections * sizeof(size_t));
    if (!buffer_lengths)
        die("malloc");

    file_fds = malloc(nconnections * sizeof(int));
    if (!file_fds)
        die("malloc");
}

