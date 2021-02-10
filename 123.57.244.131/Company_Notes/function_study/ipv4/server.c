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

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{

	int sockfd, connfd;

	/*1. 创建套接字*/
	if (0 > (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	printf("socoket........\n");


	/*2. 绑定本机地址和端口号*/
	struct sockaddr_in myaddr;
	memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(6666);
	myaddr.sin_addr.s_addr = inet_addr("0.0.0.0");
	if (0 > bind(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr)))
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	printf("bind.............\n");

	/*3. 设置监听套接字*/
	if (0 > listen(sockfd, 1024))
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	printf("listen..........\n");

	/*4. 接收客户端连接，并生成通信套接字*/
	struct sockaddr_in cliaddr;
	int addrlen = sizeof(cliaddr);
	if (0 > (connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &addrlen)))
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	printf("accept: %s\n", inet_ntoa(cliaddr.sin_addr));

	char buf[100];
	int ret;
	while (1)
	{
		/*
		if (0 > (ret = recv(connfd, buf, sizeof(buf), 0)))
		{
			perror("recv");
			break;
		}
		else if (0 == ret)
		{
			printf("write close!\n");
			break;
		}
		fputs(buf, stdout);
		*/
                fgets(buf, sizeof(buf), stdin);
                if (0 > send(connfd, buf, sizeof(buf), 0))
                {
                        perror("send");
                        break;
                }

	}
	close(sockfd);
	close(connfd);
	printf("please enter the computer.........");

	return 0;
}
