/**
 * FileName:   echo.c
 * Author:     Fasion Chan
 * @contact:   fasionchan@gmail.com
 * @version:   $Id$
 *
 * Description:
 *
 * Changelog:
 *
 **/

#include <syslog.h>
#include <unistd.h>

void echo_forever(char *ident, char *msg)
{
    openlog(ident, (LOG_CONS | LOG_PID), LOG_USER);
    setlogmask(LOG_UPTO(LOG_INFO));

    for(;;) {
        syslog(LOG_ERR, "%s\n", msg);
        sleep(10);
    }
}

int main(int argc, const char *argv[])
{
    echo_forever("echo-forever", "Hello, world!");
}
