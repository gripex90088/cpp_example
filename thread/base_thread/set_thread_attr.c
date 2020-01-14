#include <pthread.h>
#include <sched.h>

void CallBack(void)
{

}

int main()
{
	pthread_attr_t attr;
	pthread_t tid;
	struct sched_param param;
	int newprio = 20;

	pthread_attr_init(&attr);
	pthread_attr_getschedparam(&attr, &param);
	param.sched_priority=newprio;
	/*
	 * pthread_attr_setschedparam
	 * 第二个参数可选为:
	 * PTHREAD_CREATE_DETACHED(分离线程)
	 * PTHREAD _CREATE_JOINABLE(非分离线程)
	 */
	pthread_attr_setschedparam(&attr, PTHREAD_CREATE_JOINABLE);
	pthread_create(&tid, &attr, (void*)CallBack, NULL);

	return 0;
}



