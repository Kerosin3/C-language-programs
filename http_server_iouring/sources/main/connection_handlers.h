#ifndef CONNECTIONHANDLERS
#define CONNECTIONHANDLERS

#include <stdlib.h>
#include <stdio.h>
#include "misc.h"
#include "buf&files.h"
#include <liburing.h>


typedef enum
{
    FLAG_ACCEPT = 0,
    FLAG_READ = 1,
    FLAG_WRITE = 2,
} flag_state;

inline char* get_client_buffer(int client_fd)
{
    return &buffers[client_fd * BUFFER_SIZE];
}

void add_read_request(struct io_uring* ring, int client_fd);

void add_accept_request(struct io_uring *ring, 
		        int serverfd, 
		        struct sockaddr_in* a_client_adrd,
                        socklen_t* client_addr_len);
#endif
