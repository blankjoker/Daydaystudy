#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>

int main()
{
	int sockfd;
	int len;
	struct sockaddr_un address;
	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, "server_socket");
	printf(">>>>>>>>>>>>>>>>>>>>>:%s\n", address.sun_path);
	int i = 0;
	for (; i < strlen(address.sun_path); i++) {
		printf(">>%d\n", address.sun_path[i]);
	}
	len = sizeof(address);
	connect(sockfd, (struct sockaddr*)&address, len);

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