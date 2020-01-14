//============================================================================
// Name        : ipc.cpp
// Author      : JianRong
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unistd.h>

using namespace std;

/**
 * Unix IPC
 *
 * Channel [管道]
 * 	是UNIX IPC的最老形式,且所有UNIX都提供此此种通信，管道有两种限制:
 * 	1. 它们是半双工的,数据只能在一个方向上流动
 *	2. 它们只能在具有公共祖先的进程之间使用。通常,一个管道由一个进程创建,然后该进程调用fork,
 *	   此后父,子进程之间就可应用该管道 (流管道没有第一种限制,FIFO和命名流管道没有第二种限制)
 * fork之后做什么取决于我们想要有的数据流的方向。对于从父进程到子进程的管道,父进程关闭管道的读端(fd[0]),子进程则关闭写端(fd[1])
 *
 * header file:
 * 		<unistd.h>
 *
 * function:
 * int pipe(int filedes[2]); // 创建管道
 * 		返回: 若成功返回 0, 若出错返回 -1
 *		由filedes返回两个文件描述符: filedes[0]为读而打开，
 *		filedes[1]为写而打开,filedes[1]的输出是filedes[0]的输入
 * int fstat(int filedes, struct stat *buf)
 * 		对管道的每一端返回一个FIFO类型的文件描述符,可以用S_ISFIFO宏测试管道
 *
 * FIFO
 *
 * Signal
 *
 * Share memory
 *
 * Message queue
 */

int main() {
	cout << "main" << endl; // prints main

	int res, filedes[2];
	pid_t pid;

	if (pipe(filedes) < 0) {

	}

	res = pipe(filedes);
	cout << res << endl;

	return 0;
}
