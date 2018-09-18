/**
 * FileName:   mmio.c
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
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define NAME_LEN_LIMIT 32

struct student_info
{
    char name[NAME_LEN_LIMIT];
    int age;
    int score;
};

/**
 * Expand file to size desired
 * Implemented by seeking to the last byte and writing a zero byte
 *
 * Arguments
 *     fd: file descriptor of the opened file to expand
 *
 *     size: size desired
 *
 * Returns
 *     0 if success, -1 if some error happened.
 **/
int expand_file(int fd, off_t size) {
    // call fstat to check current size
    struct stat st;
    int rv = fstat(fd, &st);
    if (rv == -1) {
        perror("fail to stat file");
        return -1;
    }

    // already satisfied
    if (st.st_size >= size) {
        return 0;
    }

    // seek to the last byte needed
    rv = lseek(fd, size-1, SEEK_SET);
    if (rv == -1) {
        perror("fail to seek file");
        return -1;
    }

    // write a zero byte
    rv = write(fd, "\0", 1);
    if (rv == -1) {
        perror("fail to expand file");
        return -1;
    }

    return 0;
}

/**
 * Use mmap to read struct from file
 *
 * Arguments
 *     path: path of the file for reading
 *
 * Returns
 *     0 if success, -1 if some error happened.
 **/
int read_info(char *path)
{
    // open file in read only mode
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("fail to open file");
        return -1;
    }

    // map the opened file to memory area
    struct student_info *infop = (struct student_info *)mmap(
        NULL,
        sizeof(struct student_info),
        PROT_READ,
        MAP_SHARED,
        fd,
        0
    );
    if (infop == NULL) {
        perror("fail to map file");
        return -1;
    }

    // print info
    printf("Name: %s\n", infop->name);
    printf("Age: %d\n", infop->age);
    printf("Score: %d\n", infop->score);

    return 0;
}

/**
 * Use system call mmap to write struct to file
 *
 * Arguments
 *     path: path of the file for writing
 *
 * Returns
 *     0 if success, -1 if some error happened.
 **/
int write_info(char *path, char *name, int age, int score)
{
    // open file in read-write mode
    // if exists, truncate it; else, create with 644
    int fd = open(
        path,
        O_RDWR|O_CREAT|O_TRUNC,
        S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH
    );
    if (fd == -1) {
        perror("fail to open file");
        return -1;
    }

    // if no enough space, expand it
    if (expand_file(fd, sizeof(struct student_info)) == -1) {
        return -1;
    }

    // map the opened file to memory area
    struct student_info *infop = (struct student_info *)mmap(
        NULL,
        sizeof(struct student_info),
        PROT_WRITE,
        MAP_SHARED,
        fd,
        0
    );
    if (infop == MAP_FAILED) {
        perror("fail to map file");
        return -1;
    }

    // copy name string
    strncpy(infop->name, name, NAME_LEN_LIMIT-1);
    infop->name[NAME_LEN_LIMIT-1] = '\0';

    // set other fields
    infop->age = age;
    infop->score = score;

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 2) {
        read_info(argv[1]);
    }
    else {
        write_info(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]));
    }
}
