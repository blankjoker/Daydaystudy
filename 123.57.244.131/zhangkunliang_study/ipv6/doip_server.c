

#include <stdio.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 13400
#define IPADDR "fe80::5555:6666:7777:8888"
#define MAX_TCP_SOCKET 255
#define DOIP_IPV6_ADDR_LEN 64

int main()
{
	int fd;
    struct sockaddr_in6 addr6;
    memset(&addr6, 0, sizeof(struct sockaddr_in6));
    fd = socket(AF_INET6, SOCK_STREAM | SOCK_CLOEXEC, 0);
    if (fd < 0) {
        printf("socket create error code >>:%d, message:%s\n", errno, strerror(errno));
        return -1;
    }
    else {
    	printf("socket create tcp socket [%d] success\n", fd);
    }

    addr6.sin6_family = AF_INET6;
    addr6.sin6_port = htons(PORT);
    addr6.sin6_addr = in6addr_any;
    // inet_pton(AF_INET6, IPADDR, &addr6.sin6_addr);

    const int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt)) {
        close(fd);
        fd = -1;
        printf("setsockopt error code >>:%d, message:%s\n", errno, strerror(errno));
        return;
    }

    if (bind(fd, (struct sockaddr *) &addr6, sizeof(addr6))) {
	    printf("bind socket error code >>:%d, message:%s\n", errno, strerror(errno));
	    return;
    }
    else {
        printf("bind tcp socket [%d] success\n", fd);
    }

    if (listen(fd, MAX_TCP_SOCKET)) {
        printf("listen socket error code >>:%d, message:%s\n", errno, strerror(errno));
        close(fd);
        return;
    }
    else {
        printf("Listen tcp socket [%d] success\n", fd);
    }

    struct sockaddr_in6 client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_fd;
	client_fd = accept(fd, (struct sockaddr*)&client_addr, &client_addr_len);
	if (client_fd < 0) {
		printf("accept socket error code >>:%d, message:%s\n", errno, strerror(errno));
	}
	else {
		printf("accept tcp socket [%d] success\n", client_fd);
	}

    char fromIp[DOIP_IPV6_ADDR_LEN] = { 0 };
    inet_ntop(AF_INET6, &((struct sockaddr_in6*)&client_addr)->sin6_addr, fromIp, sizeof(fromIp));
    uint32_t fromPort = ntohs(((struct sockaddr_in6*)&client_addr)->sin6_port);
    printf("Receive TCP message from IP [%s], Port [%d]\n", fromIp, fromPort);

    while (1) {
    	int ret = 0;
    	char buff[100] = { 0 };
	    ret = read(client_fd, &buff, 100);
        if (ret <= 0) {
            printf("read data is <= 0, close socket\n");
            close(client_fd);
            sleep(1);
            continue;
        }
        printf("read data is :[%s]  data size is :[%zu]\n", buff, strlen(buff));       
    }


	close(fd);
	close(client_fd);



}