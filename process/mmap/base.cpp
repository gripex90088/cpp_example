// shared memory
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <cstring>

int main()
{
    int fd, ret;
    /* void *p = NULL: // void *是一个泛型指针  */
    char *p = NULL;
    /* void *p = nullptr; */
    
    // O_RDWR
    fd = open("shared.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open error: ");
        exit(1);
    }

    // get file size
    // :!man lseek 在vim中打开manpages
#if 0
/* delete */
    int len = ftruncdte(fd, 4);
    if (len == -1) {
        perror("ftruncate error:");
        exit(1);
    }
#endif

#if 0
    // 保证文件大小非0, 不可以忽略， 否则会报错， 总线错误， 因为mmap不能扩展一个内容为空的新文件，因为大小为0，所以没有与之对应的合法的物理页不能扩展
    write(fd, "1", 4); // 这里write长度要足够长， 此处长度似乎影响后续共享内存实际长度, 4如改为1， 后续strcpy将只写入一个字符
   // lseek(fd, 4, SEEK_SET);
#else
    // 同理
    // 不可以忽略， 否则会报错， 总线错误， 因为mmap不能扩展一个内容为空的新文件，因为大小为0，所以没有与之对应的合法的物理页不能扩展
    int len = ftruncate(fd, 4);
    if (len == -1) {
        perror("ftruncate error: ");
        exit(1);
    }
#endif

    p = (char *)mmap(NULL, 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap error:");
        exit(1);
    }

    close(fd);
    strcpy(p, "ccccccc"); // 
    printf("%s\n", p);
    
    ret = munmap((void *)p, 4);
    if (-1 == ret ) {
        perror("munmap error: ");
        exit(1);
    }

    return 0;
}

