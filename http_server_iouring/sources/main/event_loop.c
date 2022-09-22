#include "event_loop.h"
#include "connection_handlers.h"
#include "misc.h"
#include <asm-generic/socket.h>
#include <liburing.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void event_loop(int sockfd, struct io_uring *ring)
{

    struct sockaddr_in client_addr = {0};
    socklen_t client_addr_len = sizeof(client_addr);
    int current_client_fd = -1;
    int sndsize = 65536;
    int err;
    if ((err = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_SNDBUF, (char *)&sndsize, (int)sizeof(sndsize))))
        strerror(err);
    if ((err = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_RCVBUF, (char *)&sndsize, (int)sizeof(sndsize))))
        strerror(err);

    add_accept_request(ring, sockfd, &client_addr, &client_addr_len);

    for (;;)
    {
        struct io_uring_cqe *cqe;

        if (UNLIKELY(io_uring_wait_cqe(ring, &cqe)))
            die("error accepting a connection");
        printf("current event: %u, fd is %d \n", request_data_event_type(cqe->user_data),
               request_data_client_fd(cqe->user_data));

        switch (request_data_event_type(cqe->user_data)) // get type
        {
        case FLAG_ACCEPT:
            add_accept_request(ring, sockfd, &client_addr,
                               &client_addr_len); // add requst one more time  and set socket id
            buffer_lengths[cqe->res] = 0;         // set current read buffer 0
            add_read_request(ring, cqe->res);     // res = fd of the socket res -> n bytes
            printf("current event after submit: %u, fd is %d \n", request_data_event_type(ring->sq.sqes->user_data),
                   request_data_client_fd(ring->sq.sqes->user_data));
            break;
        case FLAG_READ:
            printf("read done\n");
            if (LIKELY(cqe->res)) // non-empty request?  set fd test not zero read
                handle_request(ring, request_data_client_fd(cqe->user_data), cqe->res); //  //
            break;
        case FLAG_WRITE:
	    current_client_fd = request_data_client_fd(cqe->user_data); // get current fd
	    if (LIKELY( current_client_fd !=0  )){
		    off_t offset = 0;
                    if(sendfile(current_client_fd, file_fds[current_client_fd],
                                &offset, buffer_lengths[current_client_fd]) < 0)
                        perror("sendfile");
		    printf("sended\n");
// 	            if(sendfile(current_client_fd, file_fds[current_client_fd+1],
//                                &offset, buffer_lengths[current_client_fd+1]) < 0)
 //                       perror("sendfile");

//		    close(current_client_fd);
	    }

            break;
        }
        io_uring_cqe_seen(ring, cqe);
    }
}
