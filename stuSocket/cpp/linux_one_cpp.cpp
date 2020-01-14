//============================================================================
// Name        : linux_one_cpp.cpp
// Author      : JianRong
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <ctime>
#include <iomanip> // binary conversion
#include <fstream>
#include <fcntl.h>
#include <string.h>
#include "mysock.h"

using namespace std;
void setnonblocking(SOCKET _cSock);

int main_t()
{
    exit(EXIT_SUCCESS);
}

int myMemmem(const u_char * a, int alen, const u_char * b, int blen)
{
    int i, j;
    for (i = 0; i <= alen-blen; ++ i)
    {
        for (j = 0; j < blen; ++ j)
        {
            if (a[i + j] != b[j])
            {
                break;
            }
        }
        if (j >= blen)
        {
            return i;
        }
    }
    return -1;
}

void add_task(int connfd,char *buff,int len)
{
	u_char beginflg[4]={0x00,0xBC,0x61,0x4E};
	int pos=myMemmem((u_char *)buff,len,beginflg,4);
	int posbuf=pos;

	cout << "=====pos = " << pos <<endl;
}

const u_char head_gateway = 0x2A;

int main()
{
	MySock soc;
	SOCKET _cSock; // client socket id
	soc.InitSock();
	//char * ip = "127.0.0.1"

	// ip port
	soc.BindSock("127.0.0.1", 8000);
	soc.ListenSock();
	cout << "listen " << endl;

	int epfd = epoll_create(2);
	epoll_event ep_event = {};
	ep_event.events = EPOLLIN;
	ep_event.data.fd = soc._sock;

	int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, soc._sock, &ep_event);
	if (ret == -1)
	{
		cout << "epoll create failure.\n";
	}

	struct epoll_event ep_events[10];
	int time_out = -1;
	int fd_num = 0;

	while(true)
	{
		char data_buf[4096];
		char buff[4096];

		fd_num = epoll_wait(epfd, ep_events, 10, time_out);
		for (int i = 0; i < fd_num; i++)
		{
			// new client join
			if (soc._sock == ep_events[i].data.fd)
			{
				_cSock = soc.AcceptSock();
				if (INVALID_SOCKET == _cSock)
				{
					cout << "client join failure\n";
					continue;
				}
				else
				{
					//setnonblocking(_cSock);
					ep_event.events = EPOLLIN;
					ep_event.data.fd = _cSock;
					epoll_ctl(epfd, EPOLL_CTL_ADD, _cSock, &ep_event);
				}
				cout << "new client join, <socket=" << _cSock << ">"<< endl;
				// exists execute, continue;
				//continue;
			}
			else if (ep_events[i].events & EPOLLIN)
			{
				_cSock = ep_events[i].data.fd;
				int read_len = soc.ReadSock(_cSock, data_buf);

				if (read_len <= 0 )
				{
					cout << "<socket=" << _cSock << "> exit." << endl;
					epoll_ctl(epfd, EPOLL_CTL_DEL, _cSock, NULL);
					close(_cSock);
					ep_events[i].data.fd = -1;
					//errno=0;
					continue;
				}
				//data_buf[read_len] = '\0';
				//cout << data_buf << endl;

			    if(memcmp(data_buf,&head_gateway,1)!=0)
			    {
			    	printf("request header is %x\n", head_gateway);
//			    	cout << "request header is " << head_gateway << endl;
			    }
				//add_task(_cSock, data_buf, read_len);

				ep_event.data.fd = _cSock;
				ep_event.events = EPOLLOUT;
				epoll_ctl(epfd, EPOLL_CTL_MOD, _cSock, &ep_event);
				//continue;
			}
			// send message
			else if (ep_events[i].events & EPOLLOUT)
			{
				strcpy(buff, "0x23451");
				_cSock = ep_events[i].data.fd;
				ret = soc.SendSock(_cSock, buff);

				ep_event.events = EPOLLIN;
				ep_event.data.fd = _cSock;
				epoll_ctl(epfd, EPOLL_CTL_MOD, _cSock, &ep_event);
				//continue;
			}
		}
	}

	soc.CloseSock();
	close(epfd);
	exit(EXIT_SUCCESS);
}
/*
int myMemmem(const u_char * a, int alen, const u_char * b, int blen)
{
    int i, j;
    for (i = 0; i <= alen-blen; ++ i)
    {
        for (j = 0; j < blen; ++ j)
        {
            if (a[i + j] != b[j])
            {
                break;
            }
        }
        if (j >= blen)
        {
            return i;
        }
    }
    return -1;
}
*/

void setnonblocking(SOCKET _cSock)
{
	int opts;
	opts = fcntl(_cSock, F_GETFL);
	if (opts < 0)
	{
		perror("fcntl(_cSock, F_GETFL)");
		exit(1);
	}
	opts = opts | O_NONBLOCK;
	if (fcntl(_cSock, F_SETFL, opts) < 0)
	{
		perror("fcntl(_cSock, F_SETFL, opts");
		exit(1);
	}
}



int main_socket()
{
	char data_buf[4096];
	struct epoll_event events[10]; //用于回传代处理事件的数组
	MySock my_sock;
	my_sock.InitSock();
	char ip[] = "127.0.0.1";
	my_sock.BindSock(ip, 8080);
	my_sock.ListenSock();

	// create epoll
	int epfd = epoll_create(100);
	struct epoll_event ep_event;
	ep_event.events = EPOLLIN;
	ep_event.data.fd = my_sock._sock;
	if (-1 == epoll_ctl(epfd, EPOLL_CTL_ADD, my_sock._sock, &ep_event))
	{
		cout << "epoll_ctl error\n";
	}

	int time_out = -1;
	SOCKET _cSock;
	/*
	struct sockaddr_in cSockAddr;
	int cSockAddrLen = sizeof(cSockAddr);
	*/
	while(1)
	{
		int fd_num = epoll_wait(epfd, events, 10, time_out);
		for (int idx = 0; idx < fd_num; ++idx)
		{
			// have a new socket connection
			if (my_sock._sock == events[idx].data.fd)
			{
				_cSock = my_sock.AcceptSock();
				//_cSock = accept(_sock, (sockaddr*)&cSockAddr, (socklen_t *)&cSockAddrLen);
				cout << "accept result <socket=" << _cSock << ">" << endl;
				if (INVALID_SOCKET == _cSock)
				{
					cout << "accept failure...\n";
					if (errno == EINTR || errno == EWOULDBLOCK)
					{
						errno = 0;
						continue;
					}
					exit(EXIT_FAILURE);
				}
				else
				{
					setnonblocking(_cSock);
					ep_event.data.fd = _cSock;
					ep_event.events = EPOLLIN;
					epoll_ctl(epfd, EPOLL_CTL_ADD, _cSock, &ep_event);
					cout << "accept a new connect\n";
				}
				continue;
			}

			if (events[idx].events & EPOLLIN)
			{
				_cSock = events[idx].data.fd;
				if (INVALID_SOCKET == _cSock)
				{
					cout << "code block [events[idx].events & EPOLLIN] error INVALID_SOCKET" << endl;
					continue;
				}

				int read_len = my_sock.ReadSock(_cSock, data_buf);
				if (read_len <= 0)
				{
					cout << "code block [int read_len = my_sock.ReadSock(_cSock)] error read data length <= 0" << endl;
					epoll_ctl(epfd, EPOLL_CTL_DEL, _cSock, NULL);
					events[idx].data.fd = -1;
					continue;
				}


				if (read_len > 0)
				{
					char buf[1024] = "0x2A";
					//cout << read_len << endl;
					int re = send(_cSock, buf, sizeof(buf), 0);
					if (re <= 0)
					{
						cout << "re <= 0"<<endl;
					}
					else
					{
						cout << "re > 0"<<endl;
					}
					//close(_cSock);
					continue;
				}
			//	my_sock.data_buf[read_len] = '\0';

/*
				my_sock.data_buf[read_len] = '\0';
				char buf[1024] = "0x2A";
				if (events[idx].events & EPOLLOUT)
				{
					int re = send(_cSock, buf, sizeof(buf), 0);
					if (re <= 0)
					{
						cout << "re <= 0"<<endl;
					}
					else
					{
						cout << "re > 0"<<endl;
					}

					_cSock = events[idx].data.fd;
					write(_cSock, buf, sizeof(buf));
					epoll_ctl(epfd, EPOLL_CTL_MOD, _cSock, &events[idx]);

				}

				*/
			}
		}
	}


}

int main_1()
{
	/*
    u_char beginflg[4]={0x00,0xBC,0x61,0x4E};
    int pos=myMemmem((u_char *)buff,len,beginflg,4);
	 */

	/*
	cout<<hex<<i<<endl; //输出十六进制数
	cout<<oct<<i<<endl; //输出八进制数
	cout<<dec<<i<<endl; //输出十进制数
	cout<<bin<<i<<endl; //输出二进制数
	// 输出16进制， setbase（int）可以设置8等。
	cout << setbase(16) << i << endl;
	 */

	cout << setbase(10) << 0x2A << endl;

	time_t a = time(0);
	cout << a<< endl;

	//cout << hex<<a << endl;
	fstream fout("./binary.txt", ios_base::out | ios_base::binary);

	string str = "adfasdf";
	fout.write(str.c_str(), 4);
	fout.clear();
	fout.close();
	/*
	ofstream fou;
	fou.open("./binary.txt", ios_base::out | ios_base::binary);
	string str = "sfasf";
	fou.write(str.c_str(), str.size());
	*/
	return 0;
}

void hex_str(const unsigned char *inchar, unsigned int len, unsigned char *outtxt)
{
    unsigned char hbit,lbit;
    unsigned int i;
    for(i=0;i<len;i++)
    {
        hbit = (*(inchar+i)&0xf0)>>4;
        lbit = *(inchar+i)&0x0f;
        if (hbit>9) outtxt[2*i]='A'+hbit-10;
        else outtxt[2*i]='0'+hbit;
        if (lbit>9) outtxt[2*i+1]='A'+lbit-10;
        else    outtxt[2*i+1]='0'+lbit;
    }
    outtxt[2*i] = 0;
}

typedef  struct pack{
    u_char * buff;
    int  len;
    int socket_id;
} PACK,*P_PACK;

int main_3()
{

	time_t t;
	cout << sizeof(u_char) << endl;
	cout << sizeof(time_t) << endl;

	const u_char head_gateway = 0x2A;
	u_char *buf;
	u_char buff[4096] = "AA8CCA055C000001A066554433221104008DCA055CXXXX55";
	//u_char buff[2000] = "2AF34E2C5D00004180504383AEA7E9020000000B06D5";
	buff[49] = '\0';
	cout << sizeof(buff) << endl;

	u_char beginflg[4]={0x00,0xBC,0x61,0x4E};
	int pos=myMemmem((u_char *)buff,46,beginflg,4);
	cout << pos << endl;
	//memcmp(buf,&head_gateway,1);
	//cout << buf << endl;

	u_char zero_1char=0x00;
	u_char zero_2char[2]={0x00,0x00};
	size_t date_pos = 17;

	u_char gate_mac[13]={0};
	hex_str(buff+9,6,gate_mac);
	string mac((char *)gate_mac);
}
