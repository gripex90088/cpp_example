#ifndef _MY_SOCK_H_
#define _MY_SOCK_H_

#include <sys/epoll.h> // epoll header file
#include <arpa/inet.h> // socket header file
#include <unistd.h> // read

#define SOCKET int
#define INVALID_SOCKET (SOCKET) (~0)
#define SOCKET_ERROR			(~1)

class MySock
{

public:
	SOCKET _sock;
	MySock();
	~MySock();
	void InitSock();
	void BindSock(char * ip, int port);
	void ListenSock();
	SOCKET AcceptSock();
	int ReadSock(SOCKET _cSock, char * data_buf);
	int SendSock(SOCKET _cSock,  char * data_buf);
	int RecvSock(SOCKET _cSock, char * data_buf);
	void AddTask(SOCKET _cSock, int read_len);
	void CloseSock();
private:
};


#endif
