#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

/* 线程主动退出 */
#define ERR(name, err) do {							\
		printf("%s:%s\n", #name, strerror(err));	\
		exit(-1);									\
} while(0);

void *th_fn1(void * arg)
{
	puts("thread 1 returning");
	return (void *)10;
}

void *th_fn2(void * arg)
{
	puts("thread 2 exiting");
	pthread_exit((void*)20);
	puts("thread 2 exited");
}

/* 线程主动退出 */
void pthread_active_exit()
{
	pthread_t tid1, tid2;
	int err;
	void *ret;

	err = pthread_create(&tid1, NULL, th_fn1, NULL);
	if (err != 0) ERR(pthread_create1, err);

	err = pthread_create(&tid2, NULL, th_fn2, NULL);
	if (err != 0) ERR(pthread_create2, err);

	sleep(2);

	// 主线程阻塞直到tid1退出
	err = pthread_join(tid1, &ret);
	if (err != 0) ERR(pthread_join1, err);
	printf("thread 1 exit code %d\n", (int)ret);

	// 主线程阻塞直到tid2退出
	err = pthread_join(tid2, &ret);
	if (err != 0) ERR(pthread_join2, err);
	printf("thread 2 exit code %d\n", (int)ret);
}

void* th_fn_1(void *arg)
{
	while(1) {
		puts("thread 1 running");
		sleep(1);
	}
	return (void*)10;
}

void* th_fn_2(void *arg)
{
	while(1) {
		puts("thread 2 running");
		sleep(1);
	}
	pthread_exit((void*)20);
}

/* 线程被动退出 */
void pthread_passive_exit()
{
	pthread_t tid1, tid2;
	int err;
	void *ret;

	err = pthread_create(&tid1, NULL, th_fn_1, NULL);
	if (err != 0) ERR(pthread_create1, err);

	err = pthread_create(&tid2, NULL, th_fn_2, NULL);
	if (err != 0) ERR(pthread_create2, err);

	sleep(5);

	// 通知tid1和tid2退出
	pthread_cancel(tid1);
	pthread_cancel(tid2);

	err = pthread_join(tid1, &ret);

	// 线程退出码都是PTHREAD_CANCELED
	printf("PTHREAD_CANCELED = %d\n", (int)PTHREAD_CANCELED);
	if (err != 0) ERR(pthread_join1, err);
	printf("thread 1 exit code %d\n", (int)ret);

	err = pthread_join(tid2, &ret);
	if (err != 0) ERR(pthread_join2, err);
	printf("thread 2 exit code %d\n", (int)ret);
}

int main()
{
//	pthread_active_exit();
	pthread_passive_exit();
	return 0;
}
