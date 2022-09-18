#ifndef SETUP
#define SETUP

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>


int setup_serv_sock(uint16_t port);
void teardown_server_sock(int servsock);
void setup_iouring

#endif
