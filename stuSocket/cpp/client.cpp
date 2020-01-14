// client socket
#include <iostream>
#include <arpa/inet.h>
#include <string.h>
#include <thread>
#include <ctime>

#define SOCKET int
#define INVALID_SOCKET (SOCKET) (~0)
#define SOCKET_ERROR 			(~1)

const u_char cheader = 0x2A;
const u_char ctail 	 = 0x55;

using namespace std;

bool g_bRun = true;
void cmdThread(SOCKET _sock)
{
	//u_char send_data[4096] = {0x2A,'0x1CD38A49',0x00,0x01,0x665544332211,0x06C00100,0x00,0x1CD3,0xD5};
	u_char send_data[24];
	time_t itime;
	char gatway_timehex[4] = {0};
	time(&itime);
	memcpy(gatway_timehex, &itime, 4);

	memcpy(send_data, &cheader, 1);
	memcpy(send_data+1,&gatway_timehex, 4);
	int ret = 0;
	while(true)
	{
		//2A  1CD38A49  00  01 665544332211  06C00100  00  XXXX D5
		//2A  1CD38A49  00  01 665544332211  06C00100  00  XXXX D5
		char cmdBuf[256];
		//memset(&send_data, 0x00, sizeof(send_data)-1);
		scanf("%s", cmdBuf);
		//cout << _sock << endl;
		if (0 == strcmp(cmdBuf, "exit"))
		{
			cout << "cmdTrhead exit" << endl;
			g_bRun = false;
			break;
		}
		else if ( 0 == strcmp(cmdBuf, "login"))
		{
//			strcpy(send_data,);
			cout << "cmdThread login" << endl;
			ret = send(_sock, (const char*)& send_data, sizeof(send_data), 0);
			cout << "login ret = " << ret << endl;
		}
	}

}



int main()
{

	// 1. socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == _sock)
	{
		cout << "establish sock failed..\n";
		exit(EXIT_FAILURE);
	}
	// 2. connect
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_addr.s_addr =  inet_addr("127.0.0.1"); // INADDR_ANY; //
	_sin.sin_port = htons(8000);
	int ret = connect(_sock, (sockaddr *)&_sin, sizeof(sockaddr_in));

	if (ret == -1) {
		cout << "connect failed..\n";
		exit(EXIT_FAILURE);
	}
	thread t1(cmdThread, _sock);
	t1.detach();
	while(g_bRun)
	{
		char szRecv[4096];
		//memset(&szRecv, 0, 1024);
		//send(_sock, );
		int nLen = recv(_sock, szRecv, sizeof(szRecv), 0);
		//cout << nLen << endl;
		cout << "recv data is [" << szRecv << "], length=" << nLen << endl;
		if(nLen <= 0)
		{
			cout << "recv nLen <= 0" << endl;
			exit(EXIT_FAILURE);
		}
		recv(_sock, szRecv, sizeof(szRecv), 0);

	}
	return 0;
}




