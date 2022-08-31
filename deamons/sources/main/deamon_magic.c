#include "deamon_magic.h"
#include <threads.h>

#define MAX_CONNECTIONS 10
#define SOCKNAME "filetracker.socket"

atomic_int acnt = 0;

typedef struct
{
    char **pathzz;
    int sock;
} thrd_temp_s;

static int send_filesize(int msgsock, char **paths);
static void wrap_send(thrd_temp_s *data);

void start_server()
{
    syslog(LOG_WARNING, "starting server app");
    int sock, msgsock;
    struct sockaddr_un server;
    sock = socket(AF_UNIX, SOCK_STREAM || SOCK_NONBLOCK, 0);
    if (sock < 0)
        syslog(LOG_ERR, "cannot assign a socket");
    if (sock < 0)
    {
        syslog(LOG_CRIT, "cannot open socket stream");
        goto end_sock;
    }
    server.sun_family = AF_UNIX;
    strcpy(server.sun_path, SOCKNAME);
    if (bind(sock, (struct sockaddr *)&server, sizeof(struct sockaddr_un)))
    {
        syslog(LOG_CRIT, "cannot bind socket stream %d ", errno);
        goto end_sock;
    }
    syslog(LOG_ALERT, "lunched socket has a name: %s", server.sun_path);
    listen(sock, MAX_CONNECTIONS);
    for (;;)
    {
        //    if (acnt == (N - 1))
        //      break; // to limit connections serial number
        msgsock = accept(sock, 0, 0);
        if (msgsock == -1)
        {
            syslog(LOG_CRIT, "error  reading socket");
            break;
        }
        thrd_temp_s *pass_struct = malloc(sizeof(thrd_temp_s));
        if (!pass_struct)
        {
            syslog(LOG_CRIT, "error while assigning memory for request");
            continue;
        }
        pass_struct->sock = msgsock;
        pass_struct->pathzz = (char **)paths_to_analyze();

        thrd_t thread;
        thrd_create(&thread, (thrd_start_t)wrap_send, (void *)pass_struct);
        thrd_detach(thread);
    }
    if (shutdown(sock, SHUT_RDWR))
        syslog(LOG_CRIT, "some errors while shutdowning the socket");
    unlink(SOCKNAME);

end_sock:
    close(sock);
    exit(1);
}

static void wrap_send(thrd_temp_s *data)
{
    send_filesize(data->sock, data->pathzz);
    free(data->pathzz);
    data->pathzz = NUL;
    free(data); // free struct
    data = NUL;
}

static int send_filesize(int msgsock, char **paths)
{
    size_t bufs = 0;
    size_t j = 0;
    size_t filesize = 0;
    char *msg = NUL;
    j = 0;

    while (paths[j])
    {
        if (!(filesize = calc_filesize(paths[j])))
        {
            bufs = snprintf(NUL, 0, "error while processing >>%s<< file, check whether it exists\n", paths[j]);
            msg = calloc((bufs + 1), sizeof(char));
            snprintf(msg, bufs + 1, "error while processing >>%s<< file, check whether it exists\n", paths[j]);
            send(msgsock, msg, bufs + 1, 0);
        }
        else
        {
            bufs = snprintf(NUL, 0, "filename is %s, filesize is >>%lu<< bytes\n", paths[j], filesize);
            msg = calloc((bufs + 1), sizeof(char));
            snprintf(msg, bufs + 1, "filename is %s, filesize is >>%lu<< bytes\n", paths[j], filesize);
            send(msgsock, msg, bufs + 1, 0);
        }
        free(msg);
        free(paths[j]);
        paths[j] = NUL;
        msg = (void *)0;
        j++;
    }
    free(paths[j]);
    acnt++;
    close(msgsock);
    thrd_exit(0);
}

size_t calc_filesize(char pathname[static 1])
{
    struct stat statbuf;
    int fd_fp = 0;
    FILE *fp = NUL;
    if (!(fp = fopen(pathname, "rb")))
    {
        syslog(LOG_ERR, "cannon open %s file, error %d", pathname, errno);
        return 0;
    }
    fd_fp = fileno(fp);
    if (!fd_fp) {
        syslog(LOG_ERR, "there were some error while processing %s filename,cannont assign a fd", pathname);
	return 0;
    }
    int lock = flock(fd_fp, LOCK_EX);
    if (lock)
    {
        syslog(LOG_ERR, "cannot lock fd");
    }
    if ((fstat(fd_fp, &statbuf) != 0) || (!S_ISREG(statbuf.st_mode))) {
        syslog(LOG_ERR, "%s file is probably not a regular file ", pathname);
	return 0;
    }
    size_t filesize = statbuf.st_size;
    if (!filesize) {
	syslog(LOG_ERR,"file %s, filesize is 0",pathname);
	return 0;
    }
    flock(fileno(fp), LOCK_UN);
    if (fclose(fp))
    {
        syslog(LOG_ERR, "error while closing file ");
    }
    return filesize;
}
