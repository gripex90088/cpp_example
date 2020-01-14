#include <iostream>
#include <unistd.h>
#include <sys/shm.h>
#include <cstring>

#define TEST_SIZE 2048

using namespace std;

typedef struct RATE
{
    int flag = 0;
    char task_id[100];
    int result;
    int rate;
} Rate;

int main()
{
    int shmid = shmget((key_t)11111, sizeof(Rate), 0666 | IPC_CREAT);
    void *shm = shmat(shmid, (void *)0, 0);
    Rate *pRate = (Rate *)shm;

    while(true) {
        while(pRate->flag == 0) {
            memcpy(pRate->task_id, "asdfasdf", strlen("asdfasdf"));
            pRate->rate = 123;
            pRate->result = 123;
            pRate->flag = 1;
        }
    }

    shmdt(shm);
    return 0;
}


int shareMemory() {

    /**
     * key: 1234, share memory key
     * 100: 共享内存大小， size of share memory
     *
     */
    int shmid = shmget((key_t)1236, 100, 0666 | IPC_CREAT);
    printf("shmid %d\n", shmid);

    return 0;
}
