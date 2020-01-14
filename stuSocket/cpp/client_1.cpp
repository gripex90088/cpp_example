// -pthread ����c++�߳̿� ������Ĭ�ϲ������߳̿� 
// -std=c++11 ֧��c++11��׼
//g++ -std=c++11 -pthread -o name file.cpp
#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#include <WinSock2.h>
	#pragma comment(lib, "ws2_32.lib")

#else
	#include <unistd.h> //uni std
	#include <arpa/inet.h>
	#include <string.h>

	#define SOCKET int
	#define INVALID_SOCKET (SOCKET) (~0)
	#define SOCKET_ERROR (~1)
#endif

#include <iostream>
#include <thread> // C++ ��׼�߳̿�
#include <vector>

#pragma warning(disable:4996)

using namespace std;

/*
* ���籨�ĵ����ݸ�ʽ�Ķ��弰ʹ��
*/
enum CMD
{
	CMD_LOGIN, // ��¼
	CMD_LOGIN_RESULT,
	CMD_LOGINOUT, // �˳�
	CMD_LOGINOUT_RESULT,
	CMD_NEW_USER_JOIN,
	CMD_ERROR // ������Ϣ
};
// ��Ϣͷ
struct Header
{
	short dataLength; // ���ݳ���
	short cmd; // ����
};

// ��֤ �ͻ��˷�����ֽ�˳����ͬ
// �ڴ���� ǰ��˱���ռ���ڴ�һ��
struct Login : public Header
{
	Login()
	{
		dataLength = sizeof(Login);
		cmd = CMD_LOGIN;
	}
	char username[32];
	char password[32];
};

// ��¼���
struct LoginResult : public Header
{
	LoginResult()
	{
		dataLength = sizeof(LoginResult);
		cmd = CMD_LOGIN_RESULT;
	}
	int result;
};

// �˳�
struct LoginOut : public Header
{
	LoginOut()
	{
		dataLength = sizeof(LoginOut);
		cmd = CMD_LOGINOUT;
	}
	char userName[32];
};

struct LoginOutResult : public Header
{
	LoginOutResult()
	{
		dataLength = sizeof(LoginOutResult);
		cmd = CMD_LOGINOUT_RESULT;
	}
	int result;
};

struct NewUserJoin : public Header
{
	NewUserJoin()
	{
		dataLength = sizeof(NewUserJoin);
		cmd = CMD_NEW_USER_JOIN;
		sock = 0;
	}
	int sock;
};

int processor(SOCKET _sock)
{
	/*
	* ���籨�ĵ����ݸ�ʽ���弰ʹ��
	*/
	char szRecv[1024];
	cout << szRecv << endl;
	// 5 recv
	int nLen = recv(_sock, szRecv, sizeof(Header), 0);
	Header* header = (Header*)& szRecv;
	if (nLen <= 0)
	{
		cout << "recv nLen <= 0" << endl;
		return -1;
	}

	cout << "receiving server data,  length = "
		<< header->dataLength
		<< endl;

	// 6 ��������
	switch (header->cmd)
	{
	case CMD_LOGIN_RESULT:
	{
		recv(_sock, szRecv + sizeof(Header), header->dataLength - sizeof(Header), 0);
		LoginResult* loginResult = (LoginResult*)szRecv;
		if (0 == loginResult->result)
		{
			cout << "ִ�� CMD_LOGIN, �յ���������Ϣ, socket = "
				<< (int)_sock
				<< ",dataLength="
				<< loginResult->dataLength
				<< ",result = "
				<< loginResult->result
				<< endl;
		}
	}
	break;
	case CMD_LOGINOUT_RESULT:
	{
		recv(_sock, szRecv + sizeof(Header), header->dataLength - sizeof(Header), 0);
		LoginOutResult* loginOutResult = (LoginOutResult*)szRecv;
		cout << "ִ�� CMD_LOGINOUT, �յ���������Ϣ, socket = "
			<< (int)_sock
			<< ",dataLength="
			<< loginOutResult->dataLength
			<< ",result = "
			<< loginOutResult->result
			<< endl;
	}
	break;
	case CMD_NEW_USER_JOIN:
	{
		recv(_sock, szRecv + sizeof(Header), header->dataLength - sizeof(Header), 0);
		NewUserJoin* newUser = (NewUserJoin*)szRecv;
		cout << "�յ���������Ϣ, socket = "
			<< (int)_sock
			<< ",dataLength="
			<< newUser->dataLength
			<< ",�µ�socket = ("
			<< newUser->sock
			<< "����)";
	}
	break;
	}

	return 0;
}

bool g_bRun = true;

void cmdThread(SOCKET _sock)
{
	while (true)
	{

		char cmdBuf[256];
		scanf("%s", cmdBuf);
		if (0 == strcmp(cmdBuf, "exit"))
		{
			cout << "cmdTrhead exit" << endl;
			g_bRun = false;
			break;
		}
		else if (0 == strcmp(cmdBuf, "login"))
		{
			Login login;
			strcpy(login.username, "Liudehua");
			strcpy(login.password, "Liudehuamima123");
			send(_sock, (const char*)& login, sizeof(Login), 0);
		}
		else if (0 == strcmp(cmdBuf, "loginout"))
		{
			LoginOut loginOut;
			strcpy(loginOut.userName, "Liudehua");
			send(_sock, (const char*)& loginOut, sizeof(LoginOut), 0);
		}
		else
		{
			cout << "not input" << endl;
		}
	}
}

int main()
{
#ifdef _WIN32
	// ���� win socket 2.2����
	WORD ver = MAKEWORD(2, 2);
	WSADATA data = {};
	WSAStartup(ver, &data);

#endif // 

	// 1 establish socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_sock == INVALID_SOCKET)
	{
		cout << "establish socket error" << endl;
	}
	else
	{
		cout << "establish socket success" << endl;
	}

	// 2 connect
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(8080);
	//_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

#ifdef _WIN32
	//_sin.sin_addr.S_un.S_addr = inet_addr("192.168.0.105");
	_sin.sin_addr.S_un.S_addr = inet_addr("39.105.217.28");
#else
	//_sin.sin_addr.s_addr = inet_addr("192.168.0.105");
	_sin.sin_addr.s_addr = INADDR_ANY; //inet_addr("39.105.217.28");
#endif // _WIN32

	int ret = connect(_sock, (sockaddr*)& _sin, sizeof(sockaddr_in));
	if (ret == SOCKET_ERROR)
	{
		cout << "connect server error" << endl;;
	}
	else
	{
		cout << "connect server success" << endl;
	}

	// scanf ��������
	// (�߳�thread)
	std::thread t1(cmdThread, _sock); // �����߳�
	t1.detach();

	while (g_bRun)
	{
		fd_set fdReads;
		FD_ZERO(&fdReads);
		FD_SET(_sock, &fdReads);

		//select(_sock + 1, &fdReads, NULL, NULL, NULL);
		//int sret = select(_sock + 1, &fdReads, NULL, NULL,NULL);
		//timeval t = { 1, 1 };
		ret = select(_sock + 1, &fdReads, nullptr, nullptr, nullptr);
		if (ret < 0)
		{
			cout << "select end 1" << endl;
			break;
		}

		if (FD_ISSET(_sock, &fdReads))
		{
			FD_CLR(_sock, &fdReads);
			if (-1 == processor(_sock))
			{
				cout << "select end 2" << endl;
				break;
			}
		}

		//cout << "��ǰʱ�����,���Դ�������ҵ��" << endl;	
	}

#ifdef _WIN32
	// 7 closesocekt
	closesocket(_sock);
	// clean socket
	WSACleanup();

	system("pause");
#else
	// 7 closesocekt
	close(_sock);
#endif

	return 0;
}
