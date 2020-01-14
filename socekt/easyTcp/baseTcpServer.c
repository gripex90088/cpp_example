/*
 * baseTcp.c
 *
 *  Created on: Aug 25, 2019
 *      Author: JianRong
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>		// socket API
#include <netinet/in.h> 	// INADDR_ANY
#include <unistd.h>
#include <fcntl.h>

/*******************************************************************************************************************
 * 1. int socket(int family, int type, int protocol);
 * family:
 * 		ָ��ʹ�õ�Э����: AF_INET (IPV4), AF_INET6 (IPV6), AF_LOCAL (Unix��), AF_ROUTE (·���׽���), AF_KEY (��Կ�׽���)
 * type:
 * 		�׽�������: SOCK_STREAM (�ֽ����׽���), SOCK_DGRAM (���ݱ��׽���),SOCK_SEQPACKET (��������׽���), SOCK_RAW (ԭʼ�׽���)
 * protocol:
 *		�׽���Э�飺 ����׽������Ͳ�Ϊԭʼ�׽���, ������Ϊ0, TPPROTO_TCP (TCP����Э��), IPPROTO_UDP (UDP����Э��)�� IPPROTO_SCTP (SCTP����Э��)
 *
 * 2. bind: bind(int sockfd, struct sockaddr *mySockAddr, int mySockAddrLen);
 * sockaddr:
 *		socket���ص��׽���������
 * mySockAddr:
 *		ָ�򱾵�IP��ַ�Ľṹ��ָ��
 * mySockAddrLen:
 * 		�ṹ����
 * struct sockaddr {
 *      unsigned short sa_family; // ͨ��Э��������
 *		char sa_data[14]; 		  // 14�ֽ�Э���ַ,����socket��IP��ַ�Ͷ˿ں�
 * };
 *
 * struct sockaddr_in {
 *		short int sa_family;			//	ͨ��Э��������
 *		unsigned short int sin_port;	// �˿ں�
 *		struct in_addr sin_addr;		// IP��ַ
 *		unsigned char si_zero[8];		// ���0������sockaddr�ṹ�峤����ͬ
 * }
 *
 * 3. int connect(int sockfd, const struct sockaddr *_serverAddr, socklen_t addrlen)
 * sockfd:
 * 		socket���������׽���������
 * _serverAddr:
 * 		������IP��ַ�ṹָ��
 * addrlen:
 *		�ṹ��ָ�볤��
 * 4. int listen(int sockfd, int backlog)
 * sockfd:
 * 		socket������bind���׽���������
 * backlog:
 *		���ÿ����ӿͻ��˵���������������ж���ͻ������������������ʱ���ܵ���ֵӰ�죬Ĭ��20
 *
 * 5.int accept(int sockfd, struct sockaddr *client_addr, socklen_t *addrlen)
 *  sockfd:
 *  	socket��������linsten���׽���������
 * client_addr:
 * 		�ͻ����׽��ֽӿڵ�ַ�ṹ��
 * addrlen:
 * 		�ͻ��˵�ַ�ṹ����
 * 6. int send(int sockfd, const void *msg, int len, int flags)
 * 7. int recv(int sockfd, void * buf, int len, unsighed int flags)
 * sockfd:
 * 		sockfd�������׽���������
 * msg:
 * 		�������ݵ�ָ��
 * buf:
 * 		��Ž������ݵĻ�����
 * len:
 * 		���ݵĳ���,��flags����Ϊ0
 *******************************************************************************************************************/

uint16_t generateCrc_CCITT(uint8_t *bBuff, uint32_t len);
uint8_t jiangBongGneratecheckSum(uint8_t *, uint32_t size);

uint16_t generateCrc_CCITT(uint8_t *bBuff, uint32_t len)
{
	uint32_t i;
	uint16_t crc = 0xFFF;

	for (i = 0; i < len; i++) {
		crc = (unsigned char)(crc >> 8) | (crc << 8);
		crc ^= bBuff[i];
		crc ^= (unsigned char)(crc & 0xff) >> 4;
		crc ^= (crc << 8) << 4;
		crc ^= ((crc & 0xff) << 4) << 1;
	}
	return crc;
}

uint8_t jiangBongGneratecheckSum(uint8_t *p, uint32_t size)
{
	uint32_t i;
	uint8_t sum = 0;
	for (i = 0; i < size; i++) {
		sum += p[i];
	}
	return (~sum+1);
}

int main()
{
	int fd, _sockLen, new_fd, numbytes, file_fd;
	struct sockaddr_in serv_sock;
	struct sockaddr_in client_sock;
	char buff[BUFSIZ];
	uint64_t checkSum;
	uint8_t bBuff[5];
	uint8_t bbBuff[6];

	uint8_t sof = 0x0A;
	uint8_t addr = 0xFF;
	uint8_t len = 0x02;
	uint8_t cmd = 0x91;

	serv_sock.sin_family = AF_INET;
	serv_sock.sin_port = htons(8080);
	serv_sock.sin_addr.s_addr = INADDR_ANY; // htonl("IP ADDRESS");

	_sockLen = sizeof(struct sockaddr_in);

	// establish socket
	fd = socket(PF_INET, SOCK_STREAM, 0);

	// bind
	if(bind(fd, (struct sockaddr *)&serv_sock, _sockLen) == -1) {
		printf("Bind address failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Bind Success\n");

	// listen
	if (listen(fd, 10) == -1) {
		printf("Listen failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Listening......\n");
	printf("Ready for Accept, waitting...\n");
	file_fd = open("test.h264", O_RDWR | O_CREAT | O_APPEND);
	while (1) {
		// accept
		new_fd = accept(fd, (struct sockaddr *)&client_sock, &_sockLen);
		if (new_fd == -1) {
			printf("accept failed\n");
			continue;
		}
		printf("Get the Client\n");

		if (fork() == 0) {
			// recv
			while(1) {
				numbytes = recv(new_fd, buff, BUFSIZ, 0);

				if ( -1 == write(file_fd, (void *)buff,sizeof(buff)) ) {
					fprintf(stderr, "write failed\n");
				}

				printf("recive data is %s\n", buff);
				if (numbytes < 0) {
					close(new_fd);
					break;
				}
				//printf("%d\n", buff[0]);

				/*
				memset(bBuff, 0x00, sizeof(buff));
				memcpy(bBuff, &sof, 1);
				memcpy(bBuff+1, &addr, 1);
				memcpy(bBuff+1+1, &len, 1);
				memcpy(bBuff+1+1+1, &cmd, 1);
				checkSum = jiangBongGneratecheckSum(bBuff, sizeof(bBuff));
				memcpy(bBuff+1+1+1+1, &checkSum, 1);
				send(new_fd, bBuff, sizeof(bbBuff), 0);
				*/
			}
			close(new_fd);
			exit(EXIT_SUCCESS);
		}
	}

	close(file_fd);
	// close
	close(fd);
	return 0;
}
