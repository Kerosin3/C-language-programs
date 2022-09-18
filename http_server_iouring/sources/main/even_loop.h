#ifndef EVENT_LOOP
#define EVENT_LOOP

#include "liburing.h"
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

typedef enum {
	FLAG_ACCEPT = 0,
	FLAG_READ = 1,
	FLAG_WRITE = 2,
} flag_state;


void event_loop(int serv_sock,struct io_uring* ring);

#endif
