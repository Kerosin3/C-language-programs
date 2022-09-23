#include "bufandfiles.h"
#include "event_loop.h"
#include "liburing.h"
#include "setup.h"
#include <linux/io_uring.h>
#include <signal.h>
#include <stdio.h>

struct io_uring ring;

int main(int argc, char *argv[])
{
    if ((argc > 2 || (argc == 1)))
    {
        printf("please specify just a directory, exiting..\n");
        exit(1);
    }

    setup_buffers(MAX_CONNECTIONS); // establish buffers
    get_files_in_dir(argv[1]);
    int serv_fd = setup_serv_sock(12345);
    setup_iouring(&ring, 100, false);
    signal(SIGPIPE, SIG_IGN);

    event_loop(serv_fd, &ring);

    teardown_server_sock(serv_fd);
    io_uring_queue_exit(&ring);
//     close_fd_to_send(fds_to_send);
    return 0;
}
