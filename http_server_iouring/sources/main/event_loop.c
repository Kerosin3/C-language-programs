#include "event_loop.h"
#include "bufandfiles.h"
#include "connection_handlers.h"
#include "misc.h"
#include <asm-generic/socket.h>
#include <liburing.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define REPLY_200S                                                                                                     \
    "HTTP/1.1 200 OK\r\nServer: My-test-server \r\n"                                                                   \
    "Content-Type: text/html\r\nConnection: close\r\n"                                                                 \
    "\r\n"                                                                                                             \
    "<!DOCTYPE html>"                                                                                                  \
    "<html>"                                                                                                           \
    "<head>"                                                                                                           \
    "<title>Sendfile</title>"                                                                                          \
    "</head>"                                                                                                          \
    "<body>"                                                                                                           \
    "<h1>Sending file %s</h1>"                                                                                         \
    "<p>Please wait</p>"                                                                                               \
    "</body>"                                                                                                          \
    "</html>"

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
    unsigned long long ii = 0;
    add_accept_request(ring, sockfd, &client_addr, &client_addr_len);

    for (;;)
    {
        struct io_uring_cqe *cqe;

        if (UNLIKELY(io_uring_wait_cqe(ring, &cqe)))
            die("error accepting a connection");
        //printf("current fd is %d, cycle serial:%llu\n", cqe->res, ii);
        switch (request_data_event_type(cqe->user_data)) // get type
        {
        case FLAG_ACCEPT:
            add_accept_request(ring, sockfd, &client_addr,
                               &client_addr_len); // add requst one more time  and set socket id
            buffer_lengths[cqe->res] = 0;         // set current read buffer 0
            set_flags(cqe->res);                  // works out?
            add_read_request(ring, cqe->res);     // res = fd of the socket res -> n bytes
            break;
        case FLAG_READ:
            if (LIKELY(cqe->res)) // non-empty request?  set fd test not zero read
                handle_request(ring, request_data_client_fd(cqe->user_data), cqe->res); //  //
            break;
        case FLAG_WRITE:
            current_client_fd = request_data_client_fd(cqe->user_data); // get current fd
            if (LIKELY(current_client_fd != 0))
            {
                off_t offset = 0;                      // default
                if ((file_fds[current_client_fd]) > 0) // send file
                {
                    long sended = 0;
                    do
                    {
                        sended = sendfile(current_client_fd, file_fds[current_client_fd], &offset,
                                          buffer_lengths[current_client_fd]);
                        if (sended < 0)
                        {
                            perror("sendfile");
                            break;
                        }
                    } while (sended != 0);
//                    send(current_client_fd, REPLY_200S, strlen(REPLY_200S), MSG_CONFIRM); realize as redirect!
                }
                close(file_fds[current_client_fd]);
                shutdown(current_client_fd, SHUT_RDWR);
                int closeret = close(current_client_fd);
                if (closeret < 0)
                    printf("error while closing socket %d, %s\n", current_client_fd, strerror(errno));
            }

            break;
        }
        io_uring_cqe_seen(ring, cqe);
        ii++;
    }
}
