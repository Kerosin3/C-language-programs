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

	if ( (status = getaddrinfo(argv[1], NULL, &hints, &res)) ){
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
freeaddrinfo(res);

    return 0;
}
