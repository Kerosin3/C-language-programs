#include "event_loop.h"
#include "liburing.h"
#include "setup.h"
#include "buf&files.h"
#include <linux/io_uring.h>
#include <signal.h>
#include <stdio.h>


struct io_uring ring;

int main(int argc, char *argv[])
{
    setup_buffers(MAX_CONNECTIONS);  // establish buffers
    int serv_fd = setup_serv_sock(12345);
    setup_iouring(&ring, 100, false);
    signal(SIGPIPE, SIG_IGN);

    event_loop(serv_fd, &ring);

    teardown_server_sock(serv_fd);
    io_uring_queue_exit(&ring);
    return 0;
}
