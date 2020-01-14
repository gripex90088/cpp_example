/*
 * main.cpp
 * Linux-UNIX系统编程手册（上、下册）.pdf, chapter 55
 * 劝告式锁 和 强制式锁
 *  Created on: Jul 24, 2019
 *      Author: Jian Rong
 */

/**
 * two file locking API
 * flock(); file whole locking  : 源自BSD
 * fcntl(); locking for a file area : 源自System V
 */
/***
 * flock锁存在的限制 chapter 55.2.2
 */

/***
 * 由于stdio库会在用户空间进行缓冲，因此在混合使用stdio函数与加锁时要特别小心，
 * 存在的问题是一个输入缓冲器在被加锁之前可能被填满或者一个输出缓冲器在锁被删除之后
 * 可能会刷新，避免这些问题可采用以下方法：
 * a) 使用read()和write()（以及相关的系统调用）取代stdio库来执行文件I/O
 * b) 在对文件加锁之后立即刷新stdio流，并且在释放锁之前立即再次刷新这个流
 * c) 使用setbuf()（或类似的函数)来禁用stdio缓冲，可能会牺牲一些效率
 */

/**
 * extern int flock (int __fd, int __operation) __THROW;
 *
 * [fd]：
 * 		一个打开的文件描述符
 * [operation]:
 *		LOCK_SH	在fd引用的文件上放置一把共享
 *		LOCK_EX	在fd引用的文件上放置一把互斥锁
 *
 *		LOCK_UN	解锁fd引用的文件
 *		LOCK_NB	发起一个非阻塞锁请求
 */


/***
 * extern int fcntl (int __fd, int __cmd, ...);
 * [fd]
 *		一个打开的文件描述符
 * [cmd]
 *
 * [flock]
 * F_RDLCK	读锁			从语意上对应flock()共享锁
 * F_WDLCK	写锁			从语意上对应flock()互斥锁
 * F_UNLCK	删除既有锁
 * 为了在一个文件位置放置就必须打开文件以允许读取，要放置
 * 写锁必须要打开文件以允许写入，放置两种锁就必须需打开文件
 * 以允许读写(O_RDWR),试图在文件位置上放置一把与文件访问
 * 模式不兼容的锁将会导致一个EBADF错误
 */
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/file.h>
#include <fcntl.h>

using namespace std;

const int MAX_LINE = 1024;
int read();
int read();

int write()
{
	int (*i) (void) = read;
	int num = (*i)();
	return 1;
}

int read()
{
	char cNum[MAX_LINE];
	fstream fin("test_num", ios_base::in);
	fin.getline(cNum, MAX_LINE);
	fin.close();
	//cout << cNum << endl;
	return atoi(cNum);
}

int main()
{
	int i = 200000;
	while(i--)
	{
//		write();
//		sleep(2);
	}
	return 0;
}






