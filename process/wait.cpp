#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    pid_t pid, wpid;
    int status;
    int fd;
    fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    for (int i = 0; i < 5; i++) {

        pid = fork();
        if (pid == -1) {
            perror("fork error: ");
            exit(1);
        } else if (pid == 0) {
            printf("--child, my parent %u, going to sleep 10s\n", getppid());
            sleep(2);
            exit(0);
        }
    }
#if 1
#if 0
        wpid = wait(NULL);
#endif
        while( (wpid  = wait(&status)) ) {
        if (wpid == -1) {
            perror("wait error: ");
            break;
            /* exit(1); */
        }
        
        std::cout << WIFEXITED(status) << std::endl;
        std::cout << WEXITSTATUS(status) << std::endl;
        printf("id is %u son child exit, status is %d\n", wpid, status);
        }
#endif
        while (1) {
            dup2(fd, STDOUT_FILENO);
            execlp("ls", "ls", "-lh",  NULL);
        }

    return 0;
}

