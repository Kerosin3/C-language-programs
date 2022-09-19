#include "event_loop.h"
#include "liburing.h"
#include "setup.h"
#include <linux/io_uring.h>
#include <signal.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int serv_fd = setup_serv_sock(12345);
    struct io_uring ring;
    setup_iouring(&ring, 100, false);
    signal(SIGPIPE, SIG_IGN);

    event_loop(serv_fd, &ring);

    teardown_server_sock(serv_fd);
    io_uring_queue_exit(&ring);
    return 0;
}
