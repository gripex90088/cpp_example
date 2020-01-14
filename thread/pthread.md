## pthread

### 线程创建

##### pthread_create()

```C
void *thread_func(void * argi)
{
	printf("argiment is %d\n", (int *)argi);
	return NULL;
}

int main()
{
	pthread_t pfd;
	int arg = 1;
	pthread_create(pfd, NULL, thread_func, (void *)arg);
	return 0;
}
```

### 线程终止

+ 线程终止包括两大类，主动终止与被动终止
  + 主动终止
    + 线程过程函数执行return正常返回，返回值是线程的退出码
    + 线程过程函数执行prhtred_exit函数退出，其参数是线程退出码
  + 被动终止
    + 在其它线程中调用pthread_cancel函数
    + 任意线程调用exit,\_Exit或者_exit导致整个进程终止
##### pthread_exit()

```c++
void pthread_exit(void *rval_ptr);
该函数的参数是线程的退出码，它是无类型的指针。通过函数pthread_join可以获取到值，该函数有点类似于我们之前学习的waitpid函数，它可以回收线程所使用的资源
 
int pthread_join(pthread_t tid, void **rval_ptr);
调用pthread_join会阻塞当前线程，直到指定的线程tid返回(return),执行pthread_exit或者被其它线程取消(pthread_cancel)。rval_ptr是一个输出参数，它用来接收线程退出码(是一个void*类型)
```
##### pthread_cancel()

```c++
int pthread_cancel(pthread_t tid);
默认情况下，该函数的效果相当于在线程tid中调用pthread_exit((void *)PTHREAD_CANCEL)函数
```

