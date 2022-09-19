#include "event_loop.h"
#include "liburing.h"
#include "liburing/io_uring.h"
#include <netinet/in.h>
#include <stdint.h>
#include <unistd.h>

void add_accept_request(struct io_uring *ring, 
		        int serverfd, 
		        struct sockaddr_in* a_client_adrd,
                        socklen_t* client_addr_len);


void event_loop(int sockfd, struct io_uring *ring)
{
    struct sockaddr_in client_addr = {0};
    socklen_t client_addr_len = sizeof(client_addr);
    printf("sockfd is:::: %d\n",sockfd);

    add_accept_request(ring, sockfd, &client_addr, &client_addr_len);

    for (;;)
    {
        struct io_uring_cqe *cqe;
        if (UNLIKELY(io_uring_wait_cqe(ring, &cqe)) < 0)
            die("error accepting a connection");
        // if (UNLIKELY(cqe->res) <0 ) ???

        switch (cqe->user_data)
        {
        case FLAG_ACCEPT:
            add_accept_request(ring, sockfd, &client_addr, &client_addr_len);
            if (cqe->res < 1000)
            {   // get fd
                // write to buf some

            } // n conn{}
        }
    }
}

void add_accept_request(struct io_uring *ring, 
		        int serverfd, 
		        struct sockaddr_in* a_client_adrd,
                        socklen_t* client_addr_len)
{
    struct io_uring_sqe *sqe = io_uring_get_sqe(ring); // pop
    printf("%u\n",sqe->len);
    if (!sqe) {	    
	    printf("error!\n");
	    //exit(1);
    }

    io_uring_prep_accept(sqe, serverfd, (struct sockaddr*) a_client_adrd, client_addr_len, 0);
    uint64_t to_write = 0;
    flag_state state_accept = FLAG_ACCEPT;
    __u64 some = (__u64)state_accept;
    io_uring_sqe_set_data64(sqe, some);
    io_uring_submit(ring); // use timeout?
}
