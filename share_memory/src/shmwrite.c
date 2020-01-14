/*
 * shmwrite.c
 *
 *  Created on: 2019年8月29日
 *      Author: Administrator
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>

#define TEXT_SZ 2048

struct shared_use_st
{
	int written;
	char text[TEXT_SZ];
};

int main()
{
	int running = 1;
	void *shm = NULL;
	struct shared_use_st *shared = NULL;

	char buffer[BUFSIZ + 1]; // 用于保存输入的文本
	int shmid;
	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
	if (shmid == -1) {
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}

	// 将共享内存连接到当前进程的地址空间
	shm = shmat(shmid, (void*)0, 0);
	if (shm == (void*)-1) {
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Memory attached at %X\n", (int)shm);
	// 设置共享内存
	shared = (struct shared_use_st*)shm;
	while(running) { // 向共享内存中写数据
		// 数据还没有被读取,则等待数据被读取,不能向共享内存中写入文本
		while( shared->written == 1) {
			sleep(1);
			printf("Waiting...\n");
		}
		// 向共享内存中写数据
		printf("Enter some text: ");
		fgets(buffer, BUFSIZ, stdin);
		strncpy(shared->text, buffer, TEXT_SZ);
		// 写入数据,设置written使共享内存可读
		shared->written = 1;
		// 输入end,退出
		if (strncmp(buffer, "end", 3) == 0) {
			running = 0;
		}
	}

	if (shmdt(shm) == -1) {
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}

	sleep(2);
	exit(EXIT_SUCCESS);
}
