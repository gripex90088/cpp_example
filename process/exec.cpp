#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


int main()
{
    int fd;
    fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    pid_t pid;
    pid = fork();
    if (pid == -1) {
        perror("fork error: ");
        exit(1);
    } else if (pid == 0) {
        dup2(fd, STDOUT_FILENO);
        execlp("ls", "ls", "/home", "-lh", NULL);
    }


    return 0;
}
