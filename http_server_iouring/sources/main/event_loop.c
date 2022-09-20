#include "event_loop.h"

void event_loop(int sockfd, struct io_uring *ring)
{

    struct sockaddr_in client_addr = {0};
    socklen_t client_addr_len = sizeof(client_addr);

    add_accept_request(ring, sockfd, &client_addr, &client_addr_len);

    for (;;)
    {
        struct io_uring_cqe *cqe;

        if (UNLIKELY(io_uring_wait_cqe(ring, &cqe)) < 0)
            die("error accepting a connection");

        switch (cqe->user_data) // get type
        {
        case FLAG_ACCEPT:
            add_accept_request(ring, sockfd, &client_addr, &client_addr_len); // add another accept
            buffer_lengths[cqe->res] = 0;                                     // set current buffer sock 0
            //                 add_read_request(ring, cqe->res);// res = fd
            break;
        case FLAG_READ:
            // 		if(LIKELY(cqe->res)) // non-empty request?  set fd
            //                     handle_request(ring,
            //                                    request_data_client_fd(cqe->user_data),
            //                                    cqe->res);
            break;
        }
    }
}
