#include "debug_logger.h"
#include <stdlib.h>

#define OK 1
#define FAIL 0
#define FAIL2 1024
#define MAX_MSG 2000

#define NTRIES 10000

#define DEBUG 0
#define INFO 1
#define WARNING 2
#define ERROR 3

#define write_to_log(...) wrap_gglog(__LINE__, __VA_ARGS__);

typedef enum log_level
{
    debug,
    info,
    warning,
    error
} log_level;

typedef struct internal_init
{
    char *filename;
} internal_init;

static internal_init init_t;

static char *get_level(log_level);
static void write_backlog(int linen, char filename[static 1], char *message);
static FILE *get_file(char filename[static 1]);
static void write_to_file(FILE *log_file, int n, ...);
static void write_gglog(int, unsigned LOG_LEVEL, char *message);
static void write_log(int lineno, char filename[static 1], log_level level, char *message);
void wrap_gglog(int lineno, unsigned LOG_LEVEL, char *message);
int init_recording(char *filename);

static char *get_level(log_level level)
{

    char *levels[4] = {"debug", "info", "warning", "error"};
    return levels[level];
}

static void write_backlog(int linen, char filename[static 1], char *message)
{
    static const char *start_bt = "-----------------LOG:ERRORS,BACKTRACE-------------------\n";
    static const char *end_bt = "--------------------------------------------------------\n";
    unsigned i = 0;
    unsigned bt_size = 0;

    unsigned long init_size = 1024;

    jmp_buf j1_jump;
    if (FAIL == setjmp(j1_jump))
    {
        i++;
        if (i >= NTRIES)
            exit(1); // many tries
    }
    if (FAIL2 == setjmp(j1_jump))
    {
        i++;
        init_size += (unsigned)FAIL2;
        if (i >= NTRIES)
            exit(1); // many tries
    }
    void *log = calloc(init_size, sizeof(void *));

    if (!log)
        longjmp(j1_jump, FAIL); // try again
                                //
    char ln[100] = {0};
    size_t s_msg_len = snprintf(0, 0, "---------------------LINE NUMBER %u --------------------\n", linen);
    snprintf(ln, s_msg_len + 1, "---------------------LINE NUMBER %u --------------------\n", linen);

    bt_size = backtrace(log, init_size);
    if (!(bt_size < init_size))
    { // truncated
        longjmp(j1_jump, FAIL2);
    }

    FILE *log_file = get_file(filename);

    fcntl(fileno(log_file), F_SETLKW);

    fwrite(start_bt, sizeof(char), strlen(start_bt), log_file);
    fwrite(ln, sizeof(char), strlen(ln), log_file);
    fwrite(message, sizeof(char), strlen(message), log_file);
    fflush(log_file); //!
    backtrace_symbols_fd(log, bt_size, fileno(log_file));
    fwrite(end_bt, sizeof(char), strlen(end_bt), log_file);

    fcntl(fileno(log_file), F_UNLCK);

    free(log);
    fclose(log_file);
}

static void write_to_file(FILE *log_file, int n, ...)
{
    va_list ptr;
    va_start(ptr, n);
    fcntl(fileno(log_file), F_SETLKW);
    for (size_t i = 0; i < (unsigned) n; i++)
    {
        char *to_write = va_arg(ptr, char *);
        fwrite(to_write, sizeof(char), strlen(to_write), log_file);
    }
    fcntl(fileno(log_file), F_UNLCK);
    fclose(log_file);
}

static void write_log(int lineno, char filename[static 1], log_level level, char *message)
{
    char buf[MAX_MSG] = {0};
    if (strnlen(message, MAX_MSG) == MAX_MSG)
    {
        printf("maximum message limit reached\n");
        buf[MAX_MSG - 1] = '\0';
    }
    strcpy(buf, message);

    FILE *file_log = get_file(filename);
    char ln[100] = {0};
    size_t s_msg_len = snprintf(0, 0, "---------------------LINE NUMBER %u --------------------\n", lineno);
    snprintf(ln, s_msg_len + 1, "---------------------LINE NUMBER %u --------------------\n", lineno);
    char sn[100] = {0};
    size_t l_msg_len = snprintf(0, 0, "---------------------LOG LEVEL %s --------------------\n", get_level(level));
    snprintf(sn, l_msg_len + 1, "---------------------LOG LEVEL %s --------------------\n", get_level(level));
    static const char *end_bt = "--------------------------------------------------------\n";

    write_to_file(file_log, 4, sn, ln, buf, end_bt);
}

void wrap_gglog(int lineno, unsigned LOG_LEVEL, char *message)
{
    write_gglog(lineno, LOG_LEVEL, message);
}

static void write_gglog(int lineno, unsigned LOG_LEVEL, char *message)
{
    char *filename = init_t.filename;
    if (!init_t.filename){
        printf("error open file to logging\n");
	exit(1);
    }
    if ((LOG_LEVEL) > 3)
    {
        printf("error setting log level,setting to default");
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
        write_backlog(lineno, filename, msg);
        return;
    }
    write_log(lineno, filename, LOG_LEVEL, msg);
}

int init_recording(char *filename)
{
    FILE *ret;
    if (!(ret = get_file(filename)))
    {
    	init_t.filename = 0;
	return 0;
    }
    init_t.filename = filename;
    fclose(ret);
    return 1;
}

static FILE *get_file(char filename[static 1])
{
    FILE *log_file;
    log_file = fopen(filename, "a+");
    if (!log_file)
    {
        printf("error while opening the log file\n");
        exit(1);
    }
    return log_file;
}
