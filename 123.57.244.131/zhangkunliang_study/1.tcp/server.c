/*===============================================================
*   Copyright (C) 2018 All rights reserved.
*   
*   文件名称：server.c
*   创 建 者：zhangkunliang
*   创建日期：2018年12月25日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		fprintf(stderr, "Usage: %s <ip> <port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int sockfd, connfd;

	if (0 > (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	printf("socoket........\n");

	struct sockaddr_in myaddr;
	memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(atoi(argv[2]));
	myaddr.sin_addr.s_addr = inet_addr(argv[1]);


	if (0 > bind(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr)))
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}

	printf("bind.............\n");

	if (0 > listen(sockfd, 1024))
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	printf("listen..........\n");

	struct sockaddr_in cliaddr;
	int addrlen = sizeof(cliaddr);
	if (0 > (connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &addrlen)))
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	printf("accept: %s\n", inet_ntoa(cliaddr.sin_addr));

	// struct timeval timeout = {3, 0}; 
	// // set send data timeout
	// if (0 > setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(struct timeval))) {
	// 	printf("setsockopt SO_SNDTIMEO is failed\n");
	// } 
	// // set recv data timeout
	// if (0 > setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval))) {
	// 	printf("setsockopt SO_SNDTIMEO is failed\n");
	// } 

	char buf[100];
	int ret = 0;
	errno = 0;

	// int flags = fcntl(sockfd, F_GETFL, 0);
	// fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
	// , MSG_DONTWAIT
	while (1)
	{
		if (0 > (ret = read(connfd, buf, sizeof(buf))))
		{
			printf("recv error code:%d, message:%s\n", errno, strerror(errno));
			break;
		}
		else if (0 == ret)
		{
			printf("write close!\n");
			break;
		}
		fputs(buf, stdout);
	}
	close(sockfd);
	close(connfd);
	printf("please enter the computer.........");

	return 0;
}
