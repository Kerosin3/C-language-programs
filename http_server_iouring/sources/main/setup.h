#ifndef SETUP
#define SETUP

#include "liburing.h"
#include "misc.h"
#include <linux/io_uring.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

int setup_serv_sock(uint16_t port);
void teardown_server_sock(int servsock);
void setup_iouring(struct io_uring *ring, int ncon, bool pool);

#endif
