#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* 声明一个键 */
pthread_key_t myWinKey;

void freeWinKey(char *win)
{
	//delete win;
}

void createMykey()
{
	pthread_keycreate(*&myWinKey, freeWinKey);
}

/* 函数 createWindow */
void createWindow(void)
{
	//FI_Window * win;

	static pthread_once_t once = PTHREAD_ONCE_INIT;

	/* 调用函数createMyKey, 创建键 */
	pthread_once(&once, createMykey);

	/* 将指针绑定在键上*/
	pthread_setspecific();
	// pthread_getspecific();

	/* */
}
