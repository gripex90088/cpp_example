// shared memory
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h> // define function mmap
#include <string.h>

int main()
{
    int fd, len, ret;
    /* void *p = NULL: // void *是一个泛型指针  */
    char *p = NULL;

    // O_RDWR
    fd = open("shared.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open error: ");
        exit(1);
    }

    // get file size
    // :!man lseek 在vim中打开manpages
    // 不可以忽略， 否则会报错， 总线错误， 因为mmap不能扩展一个内容为空的新文件，因为大小为0，所以没有与之对应的合法的物理页不能扩展
    len = ftruncate(fd, 4);
    if (len == -1) {
        perror("ftruncate error:");
        exit(1);
    }

    // MAP_PRIVATE
    p = mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap error:");
        exit(1);
    }

    strcpy(p, "abc"); // write
    ret = munmap(p, 4); // close
    if (ret == -1) {
        perror("mmap error: ");
        exit(1);
    }

    close(fd);

    return 0;
}

