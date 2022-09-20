#include "connection_handlers.h"


void add_read_request(struct io_uring* ring, int client_fd)
{
    struct io_uring_sqe* sqe = io_uring_get_sqe(ring); // add to ring
    size_t current_length = buffer_lengths[client_fd]; // get current length
    io_uring_prep_recv(sqe, client_fd,
                       client_buffer(client_fd) + current_length,
                       BUFFER_SIZE - current_length, 0);
    io_uring_sqe_set_data(
        sqe, (void*)make_request_data(client_fd, FLAG_READ));
    io_uring_submit(ring);
}


void add_accept_request(struct io_uring *ring, 
		        int serverfd, 
		        struct sockaddr_in* a_client_adrd,
                        socklen_t* client_addr_len)
{
    struct io_uring_sqe *sqe = io_uring_get_sqe(ring); // pop
    if (!sqe) {	    
	    printf("error adding to que\n");
    }
    io_uring_prep_accept(sqe, serverfd, (struct sockaddr*) a_client_adrd, client_addr_len, 0);
    uint64_t to_write = 0;
    flag_state state_accept = FLAG_ACCEPT; // set ACCEPT
    __u64 some = (__u64)state_accept;
    io_uring_sqe_set_data64(sqe, some);
    io_uring_submit(ring); // use timeout?
}
