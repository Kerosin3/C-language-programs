#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define PORT 23
#define BUF_SIZE 2048
static char buffer[BUF_SIZE];
int main(int argc, char** argv)
{
if(argc != 3)
{
printf("Usage: %s <host> <message>\n", argv[0]);
return EXIT_FAILURE;
}
int sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
if (sock_fd < 0)
{
perror("socket");
return EXIT_FAILURE;
}
struct sockaddr_in sock_addr = {0};
sock_addr.sin_family = AF_INET;
sock_addr.sin_port = htons(PORT);
int r = inet_pton(PF_INET, argv[1], &sock_addr.sin_addr);
if(r <= 0)
{
perror("inet_pton");
close(sock_fd);
return EXIT_FAILURE;
}
if(connect(sock_fd, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) < 0)
{
perror("connect");
close(sock_fd);
return EXIT_FAILURE;
}
if(send(sock_fd, argv[2], strlen(argv[2]), 0) < 0)
{
perror("send");
close(sock_fd);
return EXIT_FAILURE;
}
int len = 0;
while((r = recv(sock_fd, &buffer[len], BUF_SIZE - len, 0)) > 0)
{
len += r;
}
if(r < 0)
{
perror("recv");
close(sock_fd);
return EXIT_FAILURE;
}
puts(buffer);
shutdown(sock_fd, SHUT_RDWR);
close(sock_fd);
return 0;
}
