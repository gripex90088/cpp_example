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
 * Channel [�ܵ�]
 * 	��UNIX IPC��������ʽ,������UNIX���ṩ�˴���ͨ�ţ��ܵ�����������:
 * 	1. �����ǰ�˫����,����ֻ����һ������������
 *	2. ����ֻ���ھ��й������ȵĽ���֮��ʹ�á�ͨ��,һ���ܵ���һ�����̴���,Ȼ��ý��̵���fork,
 *	   �˺�,�ӽ���֮��Ϳ�Ӧ�øùܵ� (���ܵ�û�е�һ������,FIFO���������ܵ�û�еڶ�������)
 * fork֮����ʲôȡ����������Ҫ�е��������ķ��򡣶��ڴӸ����̵��ӽ��̵Ĺܵ�,�����̹رչܵ��Ķ���(fd[0]),�ӽ�����ر�д��(fd[1])
 *
 * header file:
 * 		<unistd.h>
 *
 * function:
 * int pipe(int filedes[2]); // �����ܵ�
 * 		����: ���ɹ����� 0, �������� -1
 *		��filedes���������ļ�������: filedes[0]Ϊ�����򿪣�
 *		filedes[1]Ϊд����,filedes[1]�������filedes[0]������
 * int fstat(int filedes, struct stat *buf)
 * 		�Թܵ���ÿһ�˷���һ��FIFO���͵��ļ�������,������S_ISFIFO����Թܵ�
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
