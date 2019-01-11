/**
 * FileName:   daemonize.c
 * Author:     Fasion Chan
 * @contact:   fasionchan@gmail.com
 * @version:   $Id$
 *
 * Description:
 *
 * Changelog:
 *
 **/

#include "daemonize.h"

#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>

int
daemonize()
{
    // fork to run in background
    int pid = fork();
    if (pid == -1) {
        return -1;
    }
    else if (pid != 0) {
        exit(0);
    }

    // become session leader to lose controlling TTY
    setsid();

    // fork again in order to forbid reallocating new controlling TTY
    pid = fork();
    if (pid == -1) {
        return -1;
    }
    else if (pid != 0) {
        exit(0);
    }

    // get maximun number of file descriptors
    struct rlimit rl;
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0) {
        return -1;
    }
    if (rl.rlim_max == RLIM_INFINITY) {
        rl.rlim_max = 1024;
    }

    // close all open file descriptors
    for (int i=0; i<rl.rlim_max; i++) {
        close(i);
    }

    // reopen stdin, stdout and stderr
    int stdin = open("/dev/null", O_RDWR);
    int stdout = dup(stdin);
    int stderr = dup(stdin);
    if (stdin != 0 || stdout != 1 || stderr != 2) {
        return -1;
    }

    // change the current working directory to root
    // in order not to prevent file system from being umounted
    if (chdir("/") < 0) {
        return -1;
    }

    // clear file creation mask
    umask(0);

    // set up signal handler
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) == -1) {
        return -1;
    }

    return 0;
}
