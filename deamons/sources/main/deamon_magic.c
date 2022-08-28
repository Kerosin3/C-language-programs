#include "deamonize.h"
#include <errno.h>

#define MAX_CONNECTIONS 10
#define SOCKNAME "my_socket.socket"
#define NUL (void*)0

void test(const char** paths){
	syslog(LOG_WARNING,"starting server app");
	int sock, msgsock, rval;
	struct sockaddr_un server;
	char buf[1024];
	size_t bufs = 0;
	size_t j = 0;
	size_t filesize = 0;
	sock = socket(AF_UNIX,SOCK_STREAM,0);
	char* msg = NUL;
	if (sock < 0 ){
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
				j = 0;
				while (paths[j]) {
					if (!(filesize = calc_filesize(paths[j]))) {
						bufs = snprintf(NUL,0,"error while processing %s file, check whether it exists\n",paths[j]);
						msg = calloc((bufs+1),sizeof(char));
						snprintf(msg,bufs+1,"error while processing %s file, check whether it exists\n",paths[j]);
			   			send(msgsock,msg,bufs+1,0);
					} else {
					bufs = snprintf(NUL,0,"filename is %s, filesize is %lu bytes\n",paths[j],filesize);
					msg = calloc((bufs+1),sizeof(char));
					snprintf(msg,bufs+1,"filename is %s, filesize is %lu bytes\n",paths[j],filesize);
			   		send(msgsock,msg,bufs+1,0);
					}
					free(msg);
					msg= (void*)0;
					j++;
				}
			   	//send(msgsock,buf,strlen(buf),0);
		} while(rval >0);

		close(msgsock);
		unlink(SOCKNAME);
	}


end_sock:
	close(sock);
	exit(1);

}

size_t calc_filesize(char pathname[static 1]){
	FILE* fp = NUL;
	if (!(fp = fopen(pathname, "rb"))) {
	    fprintf(stderr,"cannon open %s file, error %d\n",pathname,errno);
	    return 0;
    	}
	int lock = flock(fileno(fp), LOCK_EX);
	if (lock){
		syslog(LOG_ERR,"cannot lock fd"); 
	}
    	fseek(fp, 0, SEEK_END);
    	size_t filesize = ftell(fp);
	int release = flock(fileno(fp),LOCK_UN);
	if (fclose(fp)) {
	    fprintf(stderr,"error while closing file \n" );
	}
	return filesize++;
}
