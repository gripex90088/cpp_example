#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void *th_func(void *arg)
{
	char *name = (char*)arg;
	int i;

	int fd;
	for (i = 1; i <= 10; i++) {
		printf("%s: %d\n", name, i);

		// 判断是Allen 还是Luffy
		if (strcmp("Allen", name) == 0)
			usleep(1000 * 10); // 10ms
		else
			usleep(1000 * 5); // 5ms
	}

	return NULL;
}

int main()
{
	int err;
	pthread_t allen, luffy;
	char *name1 = "allen";
	char *name2 = "luffy";
	err = pthread_create(&allen, NULL, th_func, (void*)name1);
	if (err != 0) {
		printf("create thread allen failed\n");
		exit(1);
	}

	err = pthread_create(&luffy, NULL, th_func, (void*)name2);
	if ( err != 0) {
		printf("create thread luffy failed\n");
		exit(1);
	}

	sleep(3);

	printf("Allen is %lx\n", allen);
	printf("luffy is %lx\n", luffy);

	return 0;
}




