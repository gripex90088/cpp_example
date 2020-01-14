/**
 * pthread_create
 * 当创建线程成功时,函数返回 0,
 * 若不为 0 则说明创建线程失败,常见的错误返回代码为 EAGAIN 和 EINVAL。前者表示系
 * 统限制创建新的线程,例如线程数目过多了;后者表示第二个参数代表的线程属性值非法。
 * 创建线程成功后,新创建的线程则运行参数三和参数四确定的函数,原来的线程则继续运行
 * 下一行代码。
 *
 **********************************************************************
 * pthread_join
 * [返回值]
 * 调用成功完成后,pthread_join() 将返回零。其他任何返回值都表示出现了错误。
 * 如果检测到以下任一情况,pthread_join() 将失败并返回相应的值。
 * ESRCH
 * 描述: 没有找到与给定的线程 ID 相对应的线程。
 * EDEADLK
 * 描述: 将出现死锁,如一个线程等待其本身,或者线程 A 和线程 B 互相等待。
 * EINVAL
 * 描述: 与给定的线程 ID 相对应的线程是分离线程。
 * pthread_join() 仅适用于非分离的目标线程。如果没有必要等待特定线程终止之后才
 * 进行其他处理,则应当将该线程分离。
 *
 * [parameter]
 * 第一个参数为被等待的线程标识符,第二个参数为一个用户定义的指针,它可以用来存
 * 储被等待线程的返回值。这个函数是一个线程阻塞的函数,调用它的函数将一直等待到被等
 * 待的线程结束为止,当函数返回时,被等待线程的资源被收回。一个线程的结束有两种途径,
 * 一种是象我们上面的例子一样,函数结束了,调用它的线程也就结束了;另一种方式是通过
 * 函数 pthread_exit 来实现。
 *
 *
 ************************************************************************
 * pthread_exit()
 * 一个线程的结束有两种途径:
 * 一种是象我们上面的例子一样,函数结束了,调用它的线程也就结束了;另一种方式是通过
 * 函数 pthread_exit 来实现
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void thread(void)
{
	int i;
	for (i = 0; i < 3; i++)
	{
		printf("%ld\n", pthread_self());
		printf("This is a pthread\n");
	}
}

int main(void)
{
	pthread_t id;
	int i, ret;
	// create a thread, if return value is not 0, the creation fails.
	ret = pthread_create(&id, NULL, (void*)thread, NULL);
	if (ret != 0)
	{
		printf("Create pthread error!\n");
		exit(1);
	}

	for (i = 0; i < 3; i++)
	{
		printf("This is the main process\n");
		//thread();
		// waiting for a thread to end
		pthread_join(id, NULL);
	}

	return (0);
}
