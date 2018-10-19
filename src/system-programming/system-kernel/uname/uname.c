/**
 * FileName:   uname.c
 * Author:     Fasion Chan
 * @contact:   fasionchan@gmail.com
 * @version:   $Id$
 *
 * Description:
 *
 * Changelog:
 *
 **/

#include <stdio.h>
#include <sys/utsname.h>


int main(int argc, char *argv[])
{
    struct utsname utsname;

    int rv = uname(&utsname);
    if (rv == -1) {
        perror("uname");
        return 1;
    }

    printf("sysname: %s\n", utsname.sysname);
    printf("nodename: %s\n", utsname.nodename);
    printf("release: %s\n", utsname.release);
    printf("version: %s\n", utsname.version);
    printf("machine: %s\n", utsname.machine);
#ifdef _GNU_SOURCE
    printf("dnsdomainname: %s\n", utsname.domainname);
#endif

    return 0;
}
