#include <stdio.h>
#include <stdlib.h>
#include <linux/io_uring.h>
#include "setup.h"

int main(int argc, char *argv[])
{
	setup_serv_sock(12345);

    return 0;
}
