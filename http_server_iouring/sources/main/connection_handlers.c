#include "connection_handlers.h"
#include "bufandfiles.h"

const char *unimplemented_content = \
                                "HTTP/1.0 400 Bad Request\r\n"
                                "Content-type: text/html\r\n"
                                "\r\n"
                                "<html>"
                                "<head>"
                                "<title>ZeroHTTPd: Unimplemented</title>"
                                "</head>"
                                "<body>"
                                "<h1>Bad Request (Unimplemented)</h1>"
                                "<p>Your client sent a request ZeroHTTPd did not understand and it is probably not your fault.</p>"
                                "</body>"
                                "</html>";


static void send_string(struct io_uring* ring, int client_fd,const char* str, size_t str_len);
void add_write_request(struct io_uring* ring, int client_fd,
                              size_t nbytes, bool more_data);

void add_read_request(struct io_uring* ring, int client_fd)
{
    struct io_uring_sqe* sqe = io_uring_get_sqe(ring); // add to ring
    size_t current_length = buffer_lengths[client_fd]; // get current length
    io_uring_prep_recv(sqe, client_fd,
                       get_client_buffer(client_fd) + current_length,
                       BUFFER_SIZE - current_length, 0);
    io_uring_sqe_set_data64(sqe, make_request_data(client_fd,FLAG_READ) );
    printf("setting udata is :%LX,event: %u \n",sqe->user_data, request_data_event_type(sqe->user_data));
    int sndsize = 65536;
    int err;
    if ((err = setsockopt(sqe->fd, SOL_SOCKET, SO_REUSEADDR | SO_SNDBUF, (char *)&sndsize, (int)sizeof(sndsize)) )) 
	    strerror(err);
    if ((err = setsockopt(sqe->fd, SOL_SOCKET, SO_REUSEADDR | SO_RCVBUF,(char *)&sndsize, (int)sizeof(sndsize))))
	    strerror(err);
    printf("updated client sock opts\n");
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
    if (io_uring_submit(ring)<0)  printf("error submitting\n");
}

void add_back_accept_request(struct io_uring* ring, int client_fd)
{
    struct io_uring_sqe *sqe = io_uring_get_sqe(ring); // pop
    if (!sqe)
    {
        printf("error adding to que\n");
    }
    io_uring_sqe_set_data64(sqe, make_request_data(client_fd, FLAG_READ));
    if (io_uring_submit(ring)<0)  printf("error submitting\n");
    printf("set state read\n");
}

void handle_request(struct io_uring* ring, int client_fd,size_t n_read){
	size_t prev_length = buffer_lengths[client_fd];
	size_t length = (buffer_lengths[client_fd] += n_read); // add to length
	printf("----->%s\n", "------>>>>>>>>>>>>>\n" );
	//send_string(ring,client_fd, unimplemented_content ,strlen(unimplemented_content)); // set write here
	send_string(ring,client_fd, get_client_buffer(client_fd)+(prev_length) ,n_read); // send back
 	add_read_request(ring, client_fd); // add read back
}
/*
 *  ---flag---clientfd
 */
u_int64_t make_request_data( int client_fd,flag_state flag ){
	return (uint64_t) (flag) << 32 | client_fd; 
}


void add_write_request(struct io_uring* ring, int client_fd,
                              size_t nbytes, bool more_data)
{
    struct io_uring_sqe* sqe = io_uring_get_sqe(ring);
    io_uring_prep_send(sqe, client_fd, get_client_buffer(client_fd), nbytes,
                       MSG_DONTWAIT | (more_data ? MSG_MORE : 0));
    io_uring_sqe_set_data(
        sqe, (void*)make_request_data(client_fd, FLAG_WRITE));
    io_uring_submit(ring);
}

static void send_string(struct io_uring* ring, int client_fd,
                        const char* str, size_t str_len)
{
    memcpy(get_client_buffer(client_fd), str, str_len);
    add_write_request(ring, client_fd, str_len, false);
}

