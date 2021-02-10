/*===============================================================
*   Copyright (C) 2018 All rights reserved.
*   
*   文件名称：server.c
*   创 建 者：liujing
*   创建日期：2018年07月08日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{
	/*1. 创建套接字*/
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	printf("socket..........\n");

	/*2. 绑定本机地址和端口*/
	struct sockaddr_in myaddr;
	memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family 		= AF_INET;
	myaddr.sin_port 		= htons(13400);
	myaddr.sin_addr.s_addr 	= inet_addr("192.168.29.36");  //0.0.0.0
	if (0 > bind(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr)))
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	printf("bind.............\n");

    char *ip = inet_ntoa(myaddr.sin_addr);
    uint16_t port = ntohs(myaddr.sin_port);
    printf("udp socketfd i.ip is [%s], port is [%u]\n", ip, port);




	char buf[100];
	int ret;
	/*3. 接收数据*/
	while (1) 
	{
		ret = recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);
		if (ret < 0)
		{
			perror("recvfrom");
			break;
		}
		fputs(buf, stdout);
	}

	/*4. 关闭套接字*/
	close(sockfd);

	return 0;
}
