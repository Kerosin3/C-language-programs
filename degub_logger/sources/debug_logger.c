#include "debug_logger.h"
#include <string.h>

#define OK 1
#define FAIL 0
#define FAIL2 1024
#define MAX_MSG 2000
#define MAX_MSG_T 200
#define NTRIES 100

#define write_to_log(...) wrap_gglog(__LINE__, __FILE__, __VA_ARGS__);

struct flock g_flock;

typedef struct internal_init
{
    int fd;
} internal_init;

static internal_init init_t;

static char *get_level(log_level);
static void write_backlog(int linen, char *, int, char *message);
static FILE *get_file(char *filename);
static void write_to_file(int, int n, ...);
static void write_gglog(int, char *, unsigned LOG_LEVEL, char *message);
static void write_log(int lineno, char *, int, log_level level, char *message);
void wrap_gglog(int lineno, char *, unsigned LOG_LEVEL, char *message);
int init_recording(char *filename);
void stop_recording();

static char *get_level(log_level level)
{

    char *levels[4] = {"debug", "info", "warning", "error"};
    return levels[level];
}

static void write_backlog(int linen, char *fname_call, int fd, char *message)
{
    static const char *start_bt = "LOG:ERRORS,BACKTRACE";
    unsigned bt_size = 0;

    unsigned long init_size = 1024;

    char date[32];
    void *log = calloc(init_size, sizeof(void *));

    if (!log){
	time_t t = time(NULL);
    	struct tm* tm = gmtime(&t);
        strftime(date, sizeof(date), "%a, %d %b %Y %H:%M:%S GMT", tm);
        syslog(LOG_ERR, "error while allocing memory @ %s ",date);
	return;
     }                  //
    char ln[MAX_MSG_T] = {0};

    size_t s_msg_len =
        snprintf(0, 0, ",FILE:%s,LINE NUMBER %u", fname_call, linen);
    snprintf(ln, MAX_MSG_T, ",FILE:%s,LINE NUMBER %u, ", fname_call, linen);
    if ((s_msg_len >= MAX_MSG_T))
        syslog(LOG_INFO, "maximum msg reached, truncate output");

    bt_size = backtrace(log, init_size);
    if (!(bt_size < init_size))
    { // truncated
        syslog(LOG_ERR, "truncated backtrace output occurred ");
    }
    g_flock.l_len = 0;
    g_flock.l_start = 0;
    g_flock.l_whence = SEEK_SET;
    g_flock.l_type = F_WRLCK;
    g_flock.l_pid = getpid();

    fcntl(fd, F_SETLKW, &g_flock);

    write(fd, start_bt, strlen(start_bt));
    write(fd, ln, strlen(ln));
    write(fd, message, strlen(message));
    fsync(fd);
    backtrace_symbols_fd(log, bt_size, fd);
    //write(fd, "\n", 1);

    fcntl(fd, F_UNLCK);

    free(log);
}

static void write_to_file(int fd, int n, ...)
{
    va_list ptr;
    va_start(ptr, n);

    g_flock.l_len = 0;
    g_flock.l_start = 0;
    g_flock.l_whence = SEEK_SET;
    g_flock.l_type = F_WRLCK;
    g_flock.l_pid = getpid();

    fcntl(fd, F_SETLKW, &g_flock);

    for (size_t i = 0; i < (unsigned)n; i++)
    {
        char *to_write = va_arg(ptr, char *);
        write(fd, to_write, strlen(to_write));
    }
    fcntl(fd, F_UNLCK);
}

static void write_log(int lineno, char *fname_call, int fd, log_level level, char *message)
{
    char buf[MAX_MSG] = {0};
    if (strnlen(message, MAX_MSG) == MAX_MSG)
    {
        syslog(LOG_INFO, "maximum message length reached");
        buf[MAX_MSG - 1] = '\0';
    }
    strcpy(buf, message);
    char ln[MAX_MSG_T] = {0};
    size_t s_msg_len =
        snprintf(0, 0, "FILE:%s,LINE NUMBER %u,", fname_call, lineno);
    snprintf(ln, MAX_MSG_T, "FILE:%s,LINE NUMBER %u,", fname_call, lineno);
    char sn[MAX_MSG_T] = {0};
    size_t l_msg_len = snprintf(0, 0, "LOG LEVEL %s ", get_level(level));
    if ((s_msg_len >= MAX_MSG_T) || (l_msg_len >= MAX_MSG_T))
        syslog(LOG_INFO, "maximum msg reached, truncate output");
    snprintf(sn, MAX_MSG_T, "LOG LEVEL %s ", get_level(level));
    static const char *end_bt = "";

    write_to_file(fd, 4, sn, ln, buf, end_bt);
}

void wrap_gglog(int lineno, char *fname_call, log_level LOG_LEVEL, char *message)
{
    write_gglog(lineno, fname_call, LOG_LEVEL, message);
}

static void write_gglog(int lineno, char *fname_call, unsigned LOG_LEVEL, char *message)
{
    int fd = init_t.fd;
    if ((LOG_LEVEL) > 3)
    {
        syslog(LOG_INFO, "setting default log level");
        LOG_LEVEL = 0;
    }
    char *occur = strchr(message, '\n');
    char msg[MAX_MSG] = {0};
    strncpy(msg, message, MAX_MSG);
    if (!occur)
    {
        size_t len = strnlen(message, MAX_MSG);
        msg[len - 2] = '\n';
        msg[len - 1] = '\0';
    }
    if (LOG_LEVEL == 3)
    {
        write_backlog(lineno, fname_call, fd, msg);
        return;
    }
    write_log(lineno, fname_call, fd, LOG_LEVEL, msg);
}

int init_recording(char *filename)
{
    openlog("debugger logger", LOG_CONS | LOG_PID, LOG_USER);
    syslog(LOG_INFO, "start debug logging session");
    FILE *ret;
    ret = get_file(filename);
    init_t.fd = fileno(ret);
    return 1;
}

void stop_recording()
{
    close(init_t.fd);
    syslog(LOG_INFO, "stop debug logging session");
}

static FILE *get_file(char *filename)
{
    FILE *log_file;
    log_file = fopen(filename, "a+");
    if (!log_file)
    {
        syslog(LOG_INFO, "error opening file to write");
        exit(1);
    }
    return log_file;
}
