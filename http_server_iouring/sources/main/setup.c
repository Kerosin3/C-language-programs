#include "setup.h"
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define MAX_CONNECTIONS 100

_Noreturn void die(const char* message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

int setup_serv_sock(uint16_t port){
	struct protoent *proto = getprotobyname("tcp");
	int sockfd = socket(AF_INET,SOCK_STREAM,proto->p_proto);
	if (sockfd < 0) die("error assigning socket");
	struct sockaddr_in s_addr = {0};
	s_addr.sin_family = AF_INET; // fill sock struct
	s_addr.sin_port = htons(port); 
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY); // ine interfac
						    //
	if (bind(sockfd,(const struct sockaddr*) &s_addr, sizeof(s_addr) ) < 0 )  // relate socket to an adress
		die("error while binding");

	if (listen(sockfd,MAX_CONNECTIONS)<0)
		die("error while establishing server socket listen");

}

void teardown_server_sock(int servsock){
	shutdown(servsock, SHUT_RDWR);
}
