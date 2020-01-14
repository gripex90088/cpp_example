/*
 * shmread.c
 *
 *  Created on: 2019��8��29��
 *      Author: Administrator
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

#define TEXT_SZ 2048

struct shared_use_st
{
	int written; 		//��Ϊһ����־,��0:��ʾ�ɶ�,0��ʾ��д
	char text[TEXT_SZ]; // ��¼д��Ͷ�ȡ���ı�
};


int main()
{
	int running = 1; // �����Ƿ�������еر�־
	void *shm = NULL; // ����ع����ڴ��ԭʼ�׵�ַ
	struct shared_use_st *shared; // ָ��shm
	int shmid; //�����ڴ��ʶ

	// ���������ڴ�
	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
	if (shmid == -1) {
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}

	// �������ڴ����ӵ���ǰ���̵ĵ�ַ�ռ�
	shm = shmat(shmid, 0, 0);
	if (shm == (void*)-1) {
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}

	printf("\nMemory attached at %X\n", (int)shm);
	// ���ù����ڴ�
	shared = (struct shared_use_st*)shm;
	shared->written = 0;
	while (running) { // ��ȡ�����ڴ�����
		// û�н��������ڴ�д����,�����ݿɶ�
		if (shared->written != 0) {
			printf("You wrote: %s", shared->text);
			sleep(rand() % 3);
			// ��ȡ���,����writtenΪ��д
			shared->written = 0;
			// ����end,�˳�
			if (strncmp(shared->text, "end", 3) == 0)
				running = 0;
		} else { // �н�����д����,���ܶ�ȡ����
			sleep(1);
		}
	}

	// �ѹ����ڴ�ӵ�ǰ�����з���
	if (shmdt(shm) == -1) {
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	// ɾ�������ڴ�
	if (shmctl(shmid, IPC_RMID, 0) == -1) {
		fprintf(stderr, "shmctl(IPC_RMID) falied\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
