#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <bits/stl_algo.h>

using namespace std;

int main(int argc, char *argv[]) {
    int fd = open(argv[1], O_RDONLY | O_LARGEFILE);
    if (fd == -1) {
        perror("open()");
        exit(1);
    }


    uint64_t seek_off = strtoull(argv[2], nullptr, 16);
    printf("User offset: 0x%llx\n", seek_off);
    off64_t offset = lseek64(fd, seek_off, SEEK_SET);
    if (offset == -1) {
        perror("lseek()");
        close(fd);
        exit(1);
    }
    printf("Current offset: 0x%lx\n", offset);

    int count = atoi(argv[3]);
    char *buffer = new char[count];
    ssize_t bufread = read(fd, buffer, count);
    printf("Read %d bytes\n", bufread);
    if (bufread == -1) {
        perror("read()");
    } else {
        int fd1 = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
        ssize_t written = write(fd1, buffer, count);
        printf("Wrote %d bytes\n", written);
        if (written == -1) {
            perror("write()");
        }
        close(fd1);
    }
    delete[] buffer;

    close(fd);
    return 0;
}