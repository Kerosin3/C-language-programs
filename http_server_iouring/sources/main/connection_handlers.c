#include "connection_handlers.h"


void add_read_request(struct io_uring* ring, int client_fd)
{
    struct io_uring_sqe* sqe = io_uring_get_sqe(ring); // add to ring
    size_t current_length = buffer_lengths[client_fd]; // get current length
    io_uring_prep_recv(sqe, client_fd,
                       get_client_buffer(client_fd) + current_length,
                       BUFFER_SIZE - current_length, 0);
    //io_uring_sqe_set_data64(sqe, 1 );
    io_uring_sqe_set_data64(sqe, make_request_data(client_fd,FLAG_READ) );
    printf("udata is :%LX,event: %u \n",sqe->user_data, request_data_event_type(sqe->user_data));
    if (io_uring_submit(ring)<0)  printf("error submitting\n");
}

void add_accept_request(struct io_uring *ring, int serverfd, struct sockaddr_in *a_client_adrd,
                        socklen_t *client_addr_len)
{
    struct io_uring_sqe *sqe = io_uring_get_sqe(ring); // pop
    if (!sqe)
    {
        printf("error adding to que\n");
    }
    io_uring_prep_accept(sqe, serverfd, (struct sockaddr *)a_client_adrd, client_addr_len, 0);
    io_uring_sqe_set_data64(sqe, make_request_data(0, FLAG_ACCEPT));
    io_uring_submit(ring); // use timeout?
}

void handle_request(struct io_uring* ring, int client_fd,size_t n_read){
	size_t cur_len = buffer_lengths[client_fd];
	printf("----->%zu\n",n_read);
}
/*
 *  ---flag---clientfd
 */
u_int64_t make_request_data( int client_fd,flag_state flag ){
	return (uint64_t) (flag) << 32 | client_fd; 
}

