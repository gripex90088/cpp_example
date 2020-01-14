/*
 * shmread.c
 *
 *  Created on: 2019年8月29日
 *      Author: Administrator
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

#define TEXT_SZ 2048

struct shared_use_st
{
	int written; 		//作为一个标志,非0:表示可读,0表示可写
	char text[TEXT_SZ]; // 记录写入和读取地文本
};


int main()
{
	int running = 1; // 程序是否继续运行地标志
	void *shm = NULL; // 分配地共享内存地原始首地址
	struct shared_use_st *shared; // 指向shm
	int shmid; //共享内存标识

	// 创建共享内存
	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
	if (shmid == -1) {
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}

	// 将共享内存连接到当前进程的地址空间
	shm = shmat(shmid, 0, 0);
	if (shm == (void*)-1) {
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}

	printf("\nMemory attached at %X\n", (int)shm);
	// 设置共享内存
	shared = (struct shared_use_st*)shm;
	shared->written = 0;
	while (running) { // 读取共享内存数据
		// 没有进程向共享内存写数据,有数据可读
		if (shared->written != 0) {
			printf("You wrote: %s", shared->text);
			sleep(rand() % 3);
			// 读取完成,设置written为可写
			shared->written = 0;
			// 输入end,退出
			if (strncmp(shared->text, "end", 3) == 0)
				running = 0;
		} else { // 有进程在写数据,不能读取数据
			sleep(1);
		}
	}

	// 把共享内存从当前进程中分离
	if (shmdt(shm) == -1) {
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	// 删除共享内存
	if (shmctl(shmid, IPC_RMID, 0) == -1) {
		fprintf(stderr, "shmctl(IPC_RMID) falied\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
