/**
 * FileName:   append.c
 * Author:     Fasion Chan
 * @contact:   fasionchan@gmail.com
 * @version:   $Id$
 *
 * Description:
 *
 * Changelog:
 *
 **/

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // check cmdline arguments
    if (argc != 3) {
        fprintf(stderr, "Bad arguments!");
        return 1;
    }

    char *pathname = argv[1];
    char *data = argv[2];

    // open file
    int fd = open(pathname, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
    if (fd == -1) {
        perror("Can not open file");
        return 2;
    }

    // write data
    int bytes_written = write(fd, data, strlen(data));
    if (bytes_written == -1) {
        perror("Can not write file");
        return 3;
    }

    // sync data to disk
    int ret = fsync(fd);
    if (ret == -1) {
        perror("Fail to sync data");
        return 4;
    }

    // prompt bytes appended
    printf("Bytes appended: %d\n", bytes_written);

    // close file
    close(fd);

    return 0;
}
