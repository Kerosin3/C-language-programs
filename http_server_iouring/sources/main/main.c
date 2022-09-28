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
    if ((argc > 3 || (argc == 1) || (argc == 2)))
    {
        printf("please specify a directory, port, exiting..\n");
        exit(1);
    }
    setup_buffers(MAX_CONNECTIONS); // establish buffers
    get_files_in_dir(argv[1]);      // get dir and files
    uint16_t sock;
    sscanf(argv[2], "%hu", &sock);
    if (sock <= 1000)
    {
        printf("please do not use a port less than 1000\n");
        exit(1);
    }
    if (sock >= 65535)
    {
        printf("please specify a port less than 65535\n");
        exit(1);
    }
    int serv_fd = setup_serv_sock(sock);
    printf(">>launching server on a socket: %d<<\n", sock);
    setup_iouring(&ring, MAX_CONNECTIONS, false);
    signal(SIGPIPE, SIG_IGN);

    event_loop(serv_fd, &ring);

    teardown_server_sock(serv_fd);
    io_uring_queue_exit(&ring);
    wrap_destroy_buffer();
    return 0;
}
