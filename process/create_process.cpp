#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void child_printf() 
{
    printf("Child process exec\n");   
    exit(0);
}

int create_signal_process()
{
    pid_t pid;
    printf("create fork test\n");

    pid = fork();
    if (pid == -1) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        printf("I'm child process, pid = %u, ppid = %u\n", getpid(), getppid());
    } else {
        printf("I'm parent, pid = %u, ppid = %u\n", getpid(), getppid());
    }
    printf("Process execute subsequent code\n");
   
    // ps -aux | grep parent_ppid
    return 0;
}


// create multiple process
int main()
{
    int i;
    pid_t pid;
    printf("create multiple child process\n");

    for (i = 0; i < 5; i++) {
        pid = fork();
        if (pid == -1) {
            perror("fork error:");
            exit(1);
        } else if (pid == 0) {
            break;
        } else {
           //printf("I'm parent process, pid = %u, ppid = %u\n", getpid(), getppid());
           //sleep(1);
        }
    }

    sleep(i);
    if (i < 5) {
        printf("I'm %d child process, pid = %u\n", i, getpid());
        /* exit(1); */
    } else {
        printf("I'm parent process\n");
    }

    while(1);

    return 0;
}

