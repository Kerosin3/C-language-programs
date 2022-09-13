#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>


int main(int argc, char *argv[])
{
	struct addrinfo hints, * res, *p;
	int status;
	char ipstr[INET6_ADDRSTRLEN];

	memset(&hints,0 ,sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ( (status = getaddrinfo(NULL, "3490", &hints, &res)) ){
		printf("getaddrinfo error:%s\n",gai_strerror(status));
		exit(1);
	}

	int sock_fd = socket(res->ai_family,res->ai_socktype,res->ai_protocol); // get a socket
										if (sock_fd < 0) printf("error socket allocation\n");
									  	int bind_res = bind(sock_fd,res->ai_addr,res->ai_addrlen);
										if (bind_res < 0){
		printf("eeror binding the server socket\n");
										}
	int backlog = 10;	
										listen(sock_fd,backlog);
	struct addrinfo their_addr;
	socklen_t addr_size;

	int new_fd = accept(sock_fd,(struct sockaddr*) & their_addr, & addr_size);
	char* msg_send = "what do you want?\n";
	int len, bytes_send;
	len = strlen(msg_send);
	bytes_send = send(new_fd,msg_send,len,0);
	/*char buffer[2048] = {0};
	int len= 0 ;
	int r;
	while ((r = (recv(new_fd,&buffer[len],2048-len,0))) >0 ) {
		len+=r;
		printf("---\n");
	}
	if (r <0) printf("error\n");
	printf("finishing\n");
//	while((r = recv(s,buffer)))
	puts(buffer);
*/

	/*
	for (p = res; p!=NULL; p = p->ai_next) {
		void *addr;
		char *ipver;

		if (p->ai_family == AF_INET){
			struct sockaddr_in *ipv4 = (struct sockaddr_in *) p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPV4";
		} else {
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *) p->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPV6";
		}
		printf("--------------\n");
		inet_ntop(p->ai_family,addr,ipstr,sizeof(ipstr));
		printf("%s: %s \n",ipver,ipstr);
	}
	
	int s = socket(res->ai_family,res->ai_socktype,res->ai_protocol); // get a socket
	
        int c_done = connect(s,res->ai_addr,res->ai_addrlen);

	if (c_done < 0) {
		printf("error connecting to socket\n");
	} else {
		printf("successfully opened a socket\n");
	}

	if (s <0){ 
		printf("error opening socket\n");
	}
	static char buffer[2048] = {0};

	if (send(s,"figlet",strlen(("@figlet /list")),0) <0 ){
		printf("error sending a message\n");
		close(s);
		return 1;
	}
	int len= 0 ;
	int r;
	while ((r = (recv(s,&buffer[len],2048-len,0))) >0 ) {
		len+=r;
		printf("---\n");
	}
	if (r <0) printf("error\n");
	printf("finishing\n");
//	while((r = recv(s,buffer)))
	puts(buffer);
	*/
	shutdown(sock_fd,SHUT_RDWR);

freeaddrinfo(res);

    return 0;
}
