#ifndef CONNECTIONHANDLERS
#define CONNECTIONHANDLERS

#include "bufandfiles.h"
#include "misc.h"
#include <liburing.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>

typedef enum
{
    FLAG_ACCEPT = 0,
    FLAG_READ = 1,
    FLAG_WRITE = 2,
} flag_state;

//concat fd and state to uin64
u_int64_t make_request_data( int client_fd,flag_state flag ); 

void add_accept_request(struct io_uring *ring, int serverfd, struct sockaddr_in *a_client_adrd, socklen_t *client_addr_len);
void add_read_request(struct io_uring *ring, int client_fd); 
void handle_request(struct io_uring* ring, int client_fd,size_t n_read);

inline char *get_client_buffer(int client_fd)
{
    return &buffers[client_fd * BUFFER_SIZE];
}

// void add_read_request(struct io_uring* ring, int client_fd);

#endif
