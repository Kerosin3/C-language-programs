#include "deamonize.h"
#include <sys/syslog.h>

#define MAX_CONNECTIONS 10
#define SOCKNAME "my_socket.socket"

atomic_int acnt = 0;

typedef struct {
  char **pathzz;
  int sock;
} thrd_temp_s;

static int send_filesize(int msgsock, char **paths);
static void wrap_send(thrd_temp_s *data);

void start_server(const char **paths) {
  syslog(LOG_WARNING, "starting server app");
  int sock, msgsock, rval;
  struct sockaddr_un server;
  sock = socket(AF_UNIX, SOCK_STREAM || SOCK_NONBLOCK, 0);
  if (sock < 0) syslog(LOG_ERR,"cannot assign a socket");
  syslog(LOG_ALERT, "socket is %d", sock);
  char *msg = NUL;
  if (sock < 0) {
    syslog(LOG_CRIT, "cannot open socket stream");
    goto end_sock;
  }
  server.sun_family = AF_UNIX;
  strcpy(server.sun_path, SOCKNAME);
  if (bind(sock, (struct sockaddr *)&server, sizeof(struct sockaddr_un))) {
    syslog(LOG_CRIT, "cannot bind socket stream %d ",errno);
    goto end_sock;
  }
  syslog(LOG_ALERT, "lunched socket has a name: %s", server.sun_path);
  listen(sock, MAX_CONNECTIONS);
  thrd_temp_s pass_struct;
  pass_struct.pathzz = (char**) paths;
  for (;;) {
//    if (acnt == (4 - 1))
//      break; // limit connections
    msgsock = accept(sock, 0, 0);
    if (msgsock == -1) {
      syslog(LOG_CRIT, "error  reading socket");
      break;
    }
    thrd_temp_s *pass_struct = malloc(sizeof(thrd_temp_s));
    if (!pass_struct) {
      syslog(LOG_CRIT, "error while assigning memory for request");
      continue;
    }
    pass_struct->sock = msgsock;
    pass_struct->pathzz = (char**) paths;

    thrd_t thread;
    thrd_create(&thread, (void*) wrap_send, (void *)pass_struct);
    thrd_detach(thread);
  }
  if (shutdown(sock, SHUT_RDWR))
    syslog(LOG_CRIT, "some errors while shutdowning the socket");
  unlink(SOCKNAME);

end_sock:
  close(sock);
  exit(1);
}

static void wrap_send(thrd_temp_s *data) {
  send_filesize(data->sock, data->pathzz);
  free(data);
  data = NUL;
}

static int send_filesize(int msgsock, char **paths) {
  size_t bufs = 0;
  size_t j = 0;
  size_t filesize = 0;
  char *msg = NUL;
  j = 0;

  while (paths[j]) {
    if (!(filesize = calc_filesize(paths[j]))) {
      bufs = snprintf(
          NUL, 0,
          "error while processing >>%s<< file, check whether it exists\n",
          paths[j]);
      msg = calloc((bufs + 1), sizeof(char));
      snprintf(msg, bufs + 1,
               "error while processing >>%s<< file, check whether it exists\n",
               paths[j]);
      send(msgsock, msg, bufs + 1, 0);
    } else {
      bufs = snprintf(NUL, 0, "filename is %s, filesize is >>%lu<< bytes\n",
                      paths[j], filesize);
      msg = calloc((bufs + 1), sizeof(char));
      snprintf(msg, bufs + 1, "filename is %s, filesize is >>%lu<< bytes\n",
               paths[j], filesize);
      send(msgsock, msg, bufs + 1, 0);
    }
    free(msg);
    msg = (void *)0;
    j++;
  }

  acnt++;
  close(msgsock);
  thrd_exit(0);
}

size_t calc_filesize(char pathname[static 1]) {
  FILE *fp = NUL;
  if (!(fp = fopen(pathname, "rb"))) {
    syslog(LOG_ERR, "cannon open %s file, error %d", pathname, errno);
    return 0;
  }
  int lock = flock(fileno(fp), LOCK_EX);
  if (lock) {
    syslog(LOG_ERR, "cannot lock fd");
  }
  fseek(fp, 0, SEEK_END);
  size_t filesize = ftell(fp);
  int release = flock(fileno(fp), LOCK_UN);
  if (fclose(fp)) {
    syslog(LOG_ERR, "error while closing file ");
  }
  return filesize++;
}
