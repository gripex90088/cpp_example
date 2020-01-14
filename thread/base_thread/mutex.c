#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <bits/pthreadtypes.h>

void reader_function(void);
void writer_function(void);

char buffer;
int buffer_has_item = 0;
pthread_mutex_t mutex; /* mutex */
struct timespec delay;

void main(void)
{
	pthread_t reader;
	/* 定义延迟时间 */
	delay.tv_sec = 2;
	delay.tv_nsec = 0;

	/* 用默认属性初始化一个互斥锁对象 */
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&reader, PTHREAD_CREATE_JOINABLE,
			(void *)&reader_function, NULL);
	writer_function();
}

void writer_function(void)
{
	while(1) {
		/* locking mutex*/
		pthread_mutex_lock(&mutex);
		if (buffer_has_item == 0) {
			buffer = make_new_item();
			buffer_has_item = 1;
		}

		/* unlock mutex */
		pthread_mutex_unlock(&mutex);
		pthread_delay_np(delay);
	}
}

