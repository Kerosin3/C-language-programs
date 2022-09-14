#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>


void DumpHex(const void* data, size_t size);
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

	if ( (status = getaddrinfo(argv[1], "telnet", &hints, &res)) ){
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

	printf("returned socket is %d \n",s);

	
	if (c_done < 0) {
		printf("error connecting to socket\n");
	} else {
		printf("successfully opened a socket\n");
	}

	if (s <0){ 
		printf("error opening socket\n");
	}

/*	printf("Please enter the message=");
	char buffers[256] = {0};
	bzero(buffers, 256);
        fgets(buffers, 255, stdin);

	int n = write(s, buffers, strlen(buffer));
    	if (n < 0)
        printf("ERROR writing in socket %d  len %d", n, strlen(buffers));
	n = read(s, buffer, 255);
         if (n < 0)
        perror("ERROR reading from socket");

	printf("%s\n", buffers);
	send(s,buffers,strlen(buffers),0) ;

*/
	/*if (send(s,"figlet",strlen(("figlet"))+1,0) <0 ){
		printf("error sending a message\n");
		close(s);
		return 1;
	} */

	static char buffer[4096] = {0};
	int len= 0 ;
	int r;
	while ((r = (recv(s,&buffer[len],4096-len,0))) >0 ) {
		len+=r;
		printf("len is %d \n",r);
		DumpHex(buffer, r);
		if (r == 1 ){
			printf("sending------||------\n");
			send(s,"figlet\r\n",strlen(("figlet\r\n")),0);
			len = 0;
		}
	}
	if (r <0) printf("error\n");
	printf("finishing\n");
//	while((r = recv(s,buffer)))
	puts(buffer);
	shutdown(s,SHUT_RDWR);

freeaddrinfo(res);

    return 0;
}



void DumpHex(const void* data, size_t size) {
	char ascii[17];
	size_t i, j;
	ascii[16] = '\0';
	for (i = 0; i < size; ++i) {
		printf("%02X ", ((unsigned char*)data)[i]);
		if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') {
			ascii[i % 16] = ((unsigned char*)data)[i];
		} else {
			ascii[i % 16] = '.';
		}
		if ((i+1) % 8 == 0 || i+1 == size) {
			printf(" ");
			if ((i+1) % 16 == 0) {
				printf("|  %s \n", ascii);
			} else if (i+1 == size) {
				ascii[(i+1) % 16] = '\0';
				if ((i+1) % 16 <= 8) {
					printf(" ");
				}
				for (j = (i+1) % 16; j < 16; ++j) {
					printf("   ");
				}
				printf("|  %s \n", ascii);
			}
		}
	}
}
