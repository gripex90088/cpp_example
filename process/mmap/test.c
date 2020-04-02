#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("open.ttt", O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        perror("open failed: ");
        exit(1);
    }

    unlink("open.ttt");
    while(1) {
        write(fd, "a", 1);
    }

    close(fd);
    return 0;
}

