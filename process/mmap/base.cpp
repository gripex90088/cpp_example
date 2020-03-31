// shared memory
#include <iostream>
#include <fcntl.h>

int main()
{
    int fd;
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
    p = mmap(NULL, );
    std::cout << "Hello world" << std::endl;
    return 0;
}

