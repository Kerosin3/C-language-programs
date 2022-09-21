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
#include <limits.h>

typedef enum
{
    FLAG_ACCEPT = 0,
    FLAG_READ = 1,
    FLAG_WRITE = 2,
} flag_state;

//concat fd and state to uin64
u_int64_t make_request_data( int client_fd,flag_state flag ); 


inline int request_data_client_fd(uint64_t request_data)
{
    // UNIT_MAX = 0x00000000FFFFFFFF
    return request_data & UINT_MAX;
}

inline flag_state request_data_event_type(uint64_t request_data)
{
    uint64_t mask = ULLONG_MAX - UINT_MAX;
    // ULLONG_MAX - UINT_MAX = 0xFFFFFFFF00000000
    uint64_t ret = (request_data & (mask)) >> 32;
    return (flag_state) ret;
}


void add_accept_request(struct io_uring *ring, int serverfd, struct sockaddr_in *a_client_adrd, socklen_t *client_addr_len);
void add_read_request(struct io_uring *ring, int client_fd); 
void handle_request(struct io_uring* ring, int client_fd,size_t n_read);

inline char *get_client_buffer(int client_fd)
{
    return &buffers[client_fd * BUFFER_SIZE];
}


#endif
