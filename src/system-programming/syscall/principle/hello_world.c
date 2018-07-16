/**
 * FileName:   hello_world.c
 * Author:     Fasion Chan
 * @contact:   fasionchan@gmail.com
 * @version:   $Id$
 *
 * Description:
 *
 * Changelog:
 *
 **/

#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *msg = "Hello, world!\n";
    write(1, msg, strlen(msg));

    return 0;
}
