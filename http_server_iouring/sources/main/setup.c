#include "setup.h"

#include "liburing.h"
#define MAX_CONNECTIONS 100

_Noreturn void die(const char *message) {
  perror(message);
  exit(EXIT_FAILURE);
}

int setup_serv_sock(uint16_t port) {
  struct protoent *proto = getprotobyname("tcp");
  int sockfd = socket(AF_INET, SOCK_STREAM, proto->p_proto);
  if (sockfd < 0)
    die("error assigning socket");
  struct sockaddr_in s_addr = {0};
  s_addr.sin_family = AF_INET; // fill sock struct
  s_addr.sin_port = htons(port);
  s_addr.sin_addr.s_addr = htonl(INADDR_ANY); // ine interfac
                                              //
  if (bind(sockfd, (const struct sockaddr *)&s_addr, sizeof(s_addr)) <
      0) // relate socket to an adress
    die("error while binding");

  if (listen(sockfd, MAX_CONNECTIONS) < 0)
    die("error while establishing server socket listen");
  return sockfd;
}

void teardown_server_sock(int servsock) { shutdown(servsock, SHUT_RDWR); }

void setup_iouring(struct io_uring* ring, int ncon, bool pool){
        struct io_uring_params params = {0};
        params.flags = 0;
        params.sq_thread_idle = 2147483647;
        if ((io_uring_queue_init_params(ncon, ring, &params) ) != 0)
                die("error io uring initialization");
	printf("successully inited io uring\n");
}