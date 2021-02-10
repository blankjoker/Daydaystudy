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
#include <fcntl.h>	
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <signal.h>

void printf_time()
{
	char buff[100] = {0};
	// memset(buff, 0, 100);
	int size = 100;
	tzset();
    struct timespec tv = {0, 0};
    clock_gettime(CLOCK_REALTIME, &tv);
    time_t timep = tv.tv_sec;
    struct tm  ti_ptr;
    localtime_r(&timep, &ti_ptr);
    snprintf(buff, size, "[%04d/%02d/%02d %02d:%02d:%02d.%03ld]",
    ti_ptr.tm_year+1900,
    ti_ptr.tm_mon+1,
    ti_ptr.tm_mday,
    ti_ptr.tm_hour,
    ti_ptr.tm_min,
    ti_ptr.tm_sec,
    tv.tv_nsec / 1000);
    printf("%s", buff);
    // free(buff);
}

#define DOIP_PRINT (printf_time(), printf("[%s] line[%u]", __FILE__, __LINE__), printf)

int main(int argc, char *argv[])
{
	signal(SIGPIPE, SIG_IGN);
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

	struct sockaddr_in srv_addr;
	memset(&srv_addr, 0, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(atoi(argv[2]));
	srv_addr.sin_addr.s_addr = inet_addr(argv[1]);


	if (0 > connect(sockfd, (struct sockaddr*)&srv_addr, sizeof(srv_addr)))
	{
		perror("connect");
		exit(EXIT_FAILURE);
	}
	printf("connect.............\n");
	// struct timeval timeout = {20, 0}; 
	// // set send data timeout
	// if (0 > setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(struct timeval))) {
	// 	printf("setsockopt SO_SNDTIMEO is failed\n");
	// } 
	// // set recv data timeout
	// if (0 > setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval))) {
	// 	printf("setsockopt SO_SNDTIMEO is failed\n");
	// } 

	// char buf[100];
	int ret;
	errno = 0;

	// int flags = fcntl(sockfd, F_GETFL, 0);
	// fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
	// MSG_DONTWAIT
	char buf[1024 * 3] = { 0 };
	memset(buf, 4, 1024 * 3);
	// write(22, buf, sizeof(buf));
	while (1)
	{
		sleep(1);

		// fgets(buf, sizeof(buf), stdin);
		errno = 0;
		ret = write(sockfd, buf, sizeof(buf));
		if (0 > ret)
		{
			DOIP_PRINT("send error code:%d, message:%s\n", errno, strerror(errno));
			DOIP_PRINT("send");
			fflush(stdout);
			break;
		}
		DOIP_PRINT(">>>>error code:%d, message:%s\n", errno, strerror(errno));

		// if ( 0 > recv(sockfd, buf, sizeof(buf), MSG_DONTWAIT)) {
		// 	printf("recv error code:%d, message:%s\n", errno, strerror(errno));
		// 	perror("recv");
		// 	break ;
		// }
	}
	close(sockfd);
	sleep(10);
	return 0;
}
