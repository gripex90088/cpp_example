#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void static sig_handler(int signo)
{
    printf("child process deaded, signo: %d\n", signo);
    wait(0);
}

int main()
{
    daemon(1, 0);
    int fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    pid_t pid;
    
#if 1
    if (signal(SIGCHLD, sig_handler) == SIG_ERR) {
        perror("signal sigchild error:");
    }
#endif
 
    for (int i = 0; i < 5; i++) {
        pid = fork();
        if (pid == -1) {
            perror("fork error:");
            exit(1);
        }

        if (pid == 0) {
            while(true) {
                printf("child run\n");
                sleep(2);
            }
        }
    }

    sleep(2);
    printf("parent run\n");

    while(true);
    return 0;
}

