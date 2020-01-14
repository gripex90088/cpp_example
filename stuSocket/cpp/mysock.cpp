#include <iostream>

/*
#include <sys/socket.h>
#include <netinet/in.h>
*/

#include "mysock.h"

using namespace std;

MySock::MySock() // @suppress("Class members should be properly initialized")
{

	_sock = INVALID_SOCKET;
}

MySock::~MySock()
{
	CloseSock();
}

void MySock::InitSock()
{

	_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == _sock)
	{
		cout << "establish socket failure..\n";
	}
	cout << "establish socket success..\n";
}


void MySock::BindSock(char *ip, int port)
{
	int ret;
	struct sockaddr_in _sin;
	_sin.sin_family = AF_INET;
	_sin.sin_addr.s_addr = inet_addr(ip); // INADDR_ANY;// inet_addr(""); htonl();
	_sin.sin_port = htons(port);
	ret = bind(_sock, (sockaddr *)&_sin, sizeof(_sin));
	if (-1 == ret)
	{
		cout << "bind <socket="
				<<_sock
				<< ">, <ip="
				<< ip
				<<">, <port="
				<<port
				<< "> failure.."
				<< endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << "bind <socket="
			<<_sock
			<< ">, <ip="
			<< ip
			<<">, <port="
			<<port
			<< "> success.."
			<< endl;
	}
}

void MySock::ListenSock()
{
	int ret = listen(_sock, 10);
	if (-1 == ret)
	{
		cout << "listen <socket="
			<< _sock
			<<"> failure..\n";
	}
	else
	{
		cout << "listen <socket="
		<< _sock
		<<"> success..\n";
	}

}


SOCKET MySock::AcceptSock()
{
	SOCKET _cSock = INVALID_SOCKET;
	sockaddr_in cSockAddr = {};
	int sockLen = sizeof(cSockAddr);
	_cSock = accept(_sock, (sockaddr *)&cSockAddr, (socklen_t *)&sockLen);
	cout << "<client_socket = "<< _cSock << ">"<< endl;
	if (INVALID_SOCKET == _cSock)
	{
		return INVALID_SOCKET;
	}

	return _cSock;
}


int MySock::ReadSock(SOCKET _cSock, char * data_buf)
{
	if (INVALID_SOCKET == _cSock)
	{
		cout << "invalid socket...\n";
		return -1;
	}

	int read_len = read(_cSock, data_buf, sizeof(data_buf)-1);


	if (read_len <= 0)
	{
		cout << "read err..\n";
		if (errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK)
		{
			return -1;
		}
	}
	else
	{
		//cout << "read data " << data_buf << ", length=" << sizeof(data_buf)<<endl;
	}

	data_buf[read_len] = '\0';

	return read_len;
}

int MySock::RecvSock(SOCKET _cSock, char * data_buf)
{
	int nLen = recv(_cSock, data_buf, sizeof(data_buf), 0);
	if (nLen <= 0 )
	{
		cout << "receive err..\n";
		close(_cSock);
		if (errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK)
		{
			return -1;
		}
	}

	return nLen;
}

int MySock::SendSock(SOCKET _cSock, char * data_buf)
{

	if ( -1 == send(_cSock, (const char *)data_buf, sizeof(data_buf),0)){
		return -1;
	}

	return 0;
}


void MySock::AddTask(SOCKET _cSock, int read_len)
{

}

void MySock::CloseSock()
{
	close(_sock);
}
