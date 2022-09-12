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
    if ((argc > 2 || (argc == 1)))
    {
	    printf("specity a  hostname\n");
	    exit(1);
    }

	struct addrinfo hints, * res, *p;
	int status;
	char ipstr[INET6_ADDRSTRLEN];

	memset(&hints,0 ,sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if ( (status = getaddrinfo(argv[1], "23", &hints, &res)) ){
		printf("getaddrinfo error:%s\n",gai_strerror(status));
		exit(1);
	}
	printf("IP addresses for %s \n \n",argv[1]);
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
	shutdown(s,SHUT_RDWR);

freeaddrinfo(res);

    return 0;
}
