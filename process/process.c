#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int pid;
    int *status;

    printf("%s\n", "start parent process");
    if ( (pid = fork()) < 0) {
        printf("%s\n", "create child process");
        exit(1);
    } else {
        if (pid == 0) {
            printf("%s\n", "enter subprocess");
            sleep(4);
            exit(0);
        } else {
            wait(status);
            printf("%s\n", "recovery completed");
        }
    }
    while(1) {

    }
    return 0;
}

