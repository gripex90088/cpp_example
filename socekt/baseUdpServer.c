/*
 * baseUdpServer.c
 *
 *  Created on: Aug 26, 2019
 *      Author: JianRong
 */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h> // define INADDR_ANY

#define SERV_PORT 8087

int main()
{
	int sock_fd, len, recv_num, send_num;
	struct sockaddr_in serv_sock;
	struct sockaddr_in client_sock;
	char send_buf[20] = "I am Server";
	char recv_buf[20];

	sock_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0) {
		perror("socket");
		exit(1);
	}

	memset(&serv_sock, 0, sizeof(struct sockaddr_in));
	serv_sock.sin_family = AF_INET;
	serv_sock.sin_port = htons(SERV_PORT);
	serv_sock.sin_addr.s_addr = htonl(INADDR_ANY); //htonl("IP ADDRESS"); // inet_addr((char *)"IP ADDRESS");
	len = sizeof(serv_sock);

	if (bind(sock_fd, (struct sockaddr*)&serv_sock, sizeof(serv_sock)) < 0) {
		perror("bind error:");
		exit(1);
	}

	while(1) {
		printf("server wait\n");

		recv_num = recvfrom(sock_fd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&client_sock, (socklen_t *)&len);
		if (recv_num < 0) {
			perror("recvfrom error:");
			exit(1);
		}

		recv_buf[recv_num] = '\0';
		printf("server receive %d bytes: %s \n", recv_num, recv_buf);

		send_num = sendto(sock_fd, send_buf, recv_num, 0, (struct sockaddr *)&client_sock, (socklen_t)&len);
		if (send_num < 0) {
			perror("send error:");
			exit(1);
		}
	}

	close(sock_fd);

	return 0;
}


