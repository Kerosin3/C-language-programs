#ifndef EVENT_LOOP
#define EVENT_LOOP

#include "connection_handlers.h"
#include "misc.h"
#include "setup.h"
#include <liburing.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

void event_loop(int serv_sock, struct io_uring *ring);

#endif
