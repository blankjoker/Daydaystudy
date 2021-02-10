
#include <stdio.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 13400
#define SERVERADDR "fe80::8edc:d4ff:fe4c:ee46"
#define CLIENTADDR "fe80::5555:6666:7777:8888"
#define DOIP_IPV6_ADDR_LEN 64

int main()
{
	int sockfd, connfd;
	if (0 > (sockfd = socket(AF_INET6, SOCK_STREAM, 0))) {
		printf("socket create error code >>:%d, message:%s\n", errno, strerror(errno));
		return -1;
	}
	else {
		printf("socket create fd is: [%d] success\n", sockfd);
	}

	struct sockaddr_in6 serveraddr6;
	memset(&serveraddr6, 0, sizeof(serveraddr6));
	serveraddr6.sin6_family = AF_INET6;
	serveraddr6.sin6_port = htons(PORT);
	inet_pton(AF_INET6, SERVERADDR, &serveraddr6.sin6_addr);
	serveraddr6.sin6_scope_id = if_nametoindex("eno1");

	struct sockaddr_in6 serveraddr6_c;
	memset(&serveraddr6_c, 0, sizeof(serveraddr6_c));
	serveraddr6_c.sin6_family = AF_INET6;
	serveraddr6_c.sin6_port = htons(PORT);
	inet_pton(AF_INET6, CLIENTADDR, &serveraddr6_c.sin6_addr);
	serveraddr6_c.sin6_scope_id = if_nametoindex("eno1");


	if (0 > bind(sockfd, (struct sockaddr*)&serveraddr6_c, sizeof(serveraddr6_c))){
		printf("bind error code:%d, message:%s\n", errno, strerror(errno));
		return -1;
	}

	if (0 > connect(sockfd, (struct sockaddr*)&serveraddr6, sizeof(serveraddr6))) {
		printf("connect socket error code >>:%d, message:%s\n", errno, strerror(errno));
		return -1;
	}
	else {
		printf("connect socket fd is: [%d] success\n", sockfd); 
	}

	char buf[100];
	while (1)
	{
		fgets(buf, sizeof(buf), stdin);
		if (0 > write(sockfd, buf, sizeof(buf)))
		{
			perror("send");
			break;
		}
	}
	close(sockfd);

	return 0;
}