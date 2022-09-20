#include "buf&files.h"


/*
 * setup buffers 
 */
void setup_buffers(int nconnections)
{
    buffers = malloc(nconnections * BUFFER_SIZE);
    if(!buffers)
        die("malloc");

    buffer_lengths = malloc(nconnections * sizeof(size_t));
    if(!buffer_lengths)
        die("malloc");

    file_fds = malloc(nconnections * sizeof(int));
    if(!file_fds)
        die("malloc");
}

inline char* client_buffer(int client_fd)
{
    return &buffers[client_fd * BUFFER_SIZE];
}

