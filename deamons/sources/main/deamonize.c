#include "deamonize.h"
#include "deamon_magic.h"

void deamonize()
{
    pid_t pid;
    rlimit rlim;
    struct sigaction sa;
    rlim.rlim_cur = 1024;
    rlim.rlim_max = 1024;
    if (setrlimit(RLIMIT_NOFILE, &rlim) != 0)
        fprintf(stderr, "cannot change file limits\n");

    if ((getrlimit(RLIMIT_NOFILE, &rlim) < 0))
    { //-get max file descr n
        fprintf(stderr, "cannot get n of max files\n");
        exit(1);
    }
    openlog("filesize tracker deamon", LOG_CONS | LOG_PID, LOG_DAEMON);
    umask(007);
    if ((pid = fork()) < 0)
    {
        perror("error fork execution\n");
    }
    else if (!pid)
    { // == 0 -> child!
    }
    else
    { // sleep parent
        exit(0);
    }
    setsid(); // create a session
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
    { // mask out sighup
        syslog(LOG_CRIT, "cannot set ignore sighup\n");
    }
    if ((pid = fork()) < 0)
    {
        syslog(LOG_CRIT, "cannot fork the process\n");
        exit(1);
    }
    else if (pid != 0)
    {
        exit(0); // finish parent
    }
    fprintf(stdout, "starting deamon with pid: %d \n", getpid());
    // child code here
    char cwd[257];
    getcwd(cwd, sizeof(cwd));
    if (chdir(cwd) < 0)
    {
        syslog(LOG_CRIT, "cannot change home dir \n");
    }
    for (size_t i = 0; i < rlim.rlim_max; i++)
    {
        close(i);
    }
    int fd0, fd1, fd2;
    fd0 = fd1 = fd2 = -1;
    fd0 = open("/dev/null", O_RDWR | 0666);
    if (fd0 < 0)
        syslog(LOG_ERR, "cannot open stdin fd");
    fd1 = dup(0);
    fd2 = dup(0);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2)
    {
        syslog(LOG_CRIT, "error with fd0-fd2 creation fd0:%d,fd1:%d,fd2:%d", fd0, fd1, fd2);
    }
    syslog(LOG_INFO, "running deamon with pid %d", getpid());
    start_server(DEAMON_SETUP);
}
