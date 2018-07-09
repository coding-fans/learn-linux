/**
 * FileName:   cat.c
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
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10240

int main(int argc, char *argv[])
{
    // 检查参数
    if (argc != 2) {
        fprintf(stderr, "Usage: cat [filepath]\n");
        exit(1);
    }

    // 打开文件
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Open file");
	exit(2);
    }

    // 循环输出
    for (;;) {
        // 缓冲区
        char buffer[BUFFER_SIZE];

        // 读文件
        int bytes = read(fd, buffer, BUFFER_SIZE);
        if (bytes == -1) {
            perror("Read file");
	    exit(3);
        }
        else if (bytes == 0) {
            break;
        }

        // 写到标准输出
        // 文件描述符0代表标准输出
        if (write(0, buffer, bytes) == -1) {
            perror("Write stdout");
            exit(4);
        }
    }

    close(fd);

    return 0;
}
