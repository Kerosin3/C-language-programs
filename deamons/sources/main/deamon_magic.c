#include "deamonize.h"
#include <string.h>
#include <sys/syslog.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define MAX_CONNECTIONS 10
#define SOCKNAME "my_socket.socket"

void test(){
	syslog(LOG_WARNING,"starting server app");
	int sock, msgsock, rval;
	struct sockaddr_un server;
	char buf[1024];
	sock = socket(AF_UNIX,SOCK_STREAM,0);
	if (sock <0 ){
		syslog(LOG_CRIT,"cannot open socket stream");
		goto end_sock;
	}
	server.sun_family = AF_UNIX;
	strcpy(server.sun_path,SOCKNAME);
		if (bind(sock, (struct sockaddr *) &server, sizeof(struct sockaddr_un)  )) {
			syslog(LOG_CRIT, "cannot bind socket stream");
			goto end_sock;
		}
	syslog(LOG_ALERT, "lunched socket has a name: %s", server.sun_path);
	listen(sock, MAX_CONNECTIONS);

	for (;;){
		msgsock = accept(sock,0,0);
		if (msgsock == -1) {
			syslog(LOG_CRIT,"error  reading socket");
			break;
		}
		else do {
			bzero(buf,sizeof(buf));
			if (( rval = read(msgsock,buf,1024))  < 0 )
				syslog(LOG_CRIT,"error reading sock msg");
			else if (rval ==0)
				syslog(LOG_ALERT,"closing connection");
			else
			   send (msgsock,buf,strlen(buf),0);
		} while(rval >0);

		close(msgsock);
		unlink(SOCKNAME);
	}


end_sock:
	close(sock);
	exit(1);

}
