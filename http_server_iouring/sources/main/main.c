#include "bufandfiles.h"
#include "event_loop.h"
#include "liburing.h"
#include "setup.h"
#include <linux/io_uring.h>
#include <signal.h>
#include <stdio.h>

struct io_uring ring;
char *dir_name;

int main(int argc, char *argv[])
{
    if ((argc > 2 || (argc == 1)))
    {
        printf("please specify just a directory, exiting..\n");
        exit(1);
    }
    setup_buffers(MAX_CONNECTIONS); // establish buffers
    char *dir_name = argv[1];
    get_files_in_dir(argv[1]); // get dir and files
    int serv_fd = setup_serv_sock(12345);
    setup_iouring(&ring, MAX_CONNECTIONS, false);
    signal(SIGPIPE, SIG_IGN);

    event_loop(serv_fd, &ring);

    teardown_server_sock(serv_fd);
    io_uring_queue_exit(&ring);
    wrap_destroy_buffer();
    return 0;
}
