#include <alloca.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAX_BUF_SIZE 4096
#define MAX_TEXT_SIZE 1000
#define MAX_FONT_SIZE 100

void DumpHex(const void *data, size_t size); // for debugging

int main(int argc, char *argv[]) {

  if ((argc > 2 || (argc == 1))) {
    printf("please make input your text (limit 1000 chars), exiting..\n");
    exit(1);
  }
  if (strnlen(argv[1], MAX_TEXT_SIZE) > MAX_TEXT_SIZE) {
    printf("please enter less that 1000 chars\n");
    exit(1);
  }
  struct addrinfo hints, *res, *p;
  int status;
  char ipstr[INET6_ADDRSTRLEN];

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  if ((status = getaddrinfo("telehack.com", "23", &hints, &res))) {
    printf("getaddrinfo error:%s\n", gai_strerror(status));
    exit(1);
  }
  for (p = res; p != NULL; p = p->ai_next) {
    void *addr;

    if (p->ai_family == AF_INET) {
      struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
      addr = &(ipv4->sin_addr);
    } else {
      struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
      addr = &(ipv6->sin6_addr);
    }
    inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
  }

  int s = socket(res->ai_family, res->ai_socktype,
                 res->ai_protocol); // get a socket
  if (s < 0) {
    perror("error while assigning a socket");
    exit(1);
  }

  int c_done = connect(s, res->ai_addr, res->ai_addrlen);

  if (c_done < 0) {
    perror("error connecting to socket\n");
    exit(1);
  }

  char font[MAX_FONT_SIZE] = {0};
  char s_msg[MAX_TEXT_SIZE] = {0};

  puts("please enter a desired font:");
  if (!fgets(font, MAX_FONT_SIZE, stdin)) {
    fprintf(stderr, "error while reading input");
  }

  font[strcspn(font, "\n")] = 0;

  size_t s_msg_len = snprintf(0, 0, "figlet /%s %s\r\n", font, argv[1]);
  snprintf(s_msg, s_msg_len + 1, "figlet /%s %s\r\n", font, argv[1]);

  static char buffer[MAX_BUF_SIZE] = {0};
  int len = 0;
  int r = -1;

  do {
    r = (recv(s, &buffer[len], MAX_BUF_SIZE - len, 0));
    len += r;
  } while (((strcmp(buffer + (len - 3), "\r\n."))));
  ssize_t sret = -1;
  ssize_t left = s_msg_len + 1;
  do {
    sret = send(s, s_msg, left, 0);
    if (sret < 0) {
      printf("error while sending to the server, error %d\n", errno);
      left = -1;
      len = -1;
      goto end;
    }
    left -= sret;

  } while (left > 0);
  len = 0;
  r = -1;
  memset(buffer, 0, MAX_BUF_SIZE);
  while (((r = (recv(s, &buffer[len], MAX_BUF_SIZE - len, 0))) > 0)) {
    len += r;
    if (len >= MAX_BUF_SIZE) {
      printf("max buffer size exeeded!\n");
      buffer[MAX_BUF_SIZE - 1] = '\0';
      break;
    }
    if (!(strncmp(buffer + (len - 3), "\r\n.", 3)))
      break;
  }

  if (r < 0) {
    printf("error reading server response\n");
    goto end;
  }
  buffer[len - 2] = '\0';
  puts(buffer + s_msg_len);
end:
  shutdown(s, SHUT_RDWR);
  freeaddrinfo(res);
  freeaddrinfo(p);

  return 0;
}

/*
 * for debugging
 * */
void DumpHex(const void *data, size_t size) {
  char ascii[17];
  size_t i, j;
  ascii[16] = '\0';
  for (i = 0; i < size; ++i) {
    printf("%02X ", ((unsigned char *)data)[i]);
    if (((unsigned char *)data)[i] >= ' ' &&
        ((unsigned char *)data)[i] <= '~') {
      ascii[i % 16] = ((unsigned char *)data)[i];
    } else {
      ascii[i % 16] = '.';
    }
    if ((i + 1) % 8 == 0 || i + 1 == size) {
      printf(" ");
      if ((i + 1) % 16 == 0) {
        printf("|  %s \n", ascii);
      } else if (i + 1 == size) {
        ascii[(i + 1) % 16] = '\0';
        if ((i + 1) % 16 <= 8) {
          printf(" ");
        }
        for (j = (i + 1) % 16; j < 16; ++j) {
          printf("   ");
        }
        printf("|  %s \n", ascii);
      }
    }
  }
}
