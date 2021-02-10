#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<errno.h>
#include <net/if.h>
#include <sys/ioctl.h>
#define MAXLINE 4096

int main(int argc, char** argv){
    int   sockfd, n;
    char  recvline[4096], sendline[4096];
    struct sockaddr_in  servaddr;

    // if( argc != 2){
    //     printf("usage: ./client <ipaddress>\n");
    //     return 0;
    // }

    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
        return 0;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    servaddr.sin_addr.s_addr = inet_addr("192.168.28.112");

    // errno = 0;
    // const int opt = 1;
    // if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt)) {
    //     close(sockfd);
    //     printf("ne_doip_udp_socket_send_data_fd setsockopt 1 error code:%d, message:%s!\n", errno, strerror(errno));
    //     sockfd = -1;
    //     return sockfd;
    // }

    errno = 0;
    // struct ifreq ifr;
    // memset(&ifr, 0, sizeof(struct ifreq));
    // strncpy(ifr.ifr_name, "vlan51", IFNAMSIZ);
    // // snprintf(ifr.ifr_name, IFNAMSIZ, "enp1s0");
    // // ioctl(sockfd, SIOCGIFINDEX, &ifr);
    // if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, (char *)&ifr, sizeof(ifr))) {
    //     close(sockfd);
    //     printf("setsockopt 2 error code:%d, message:%s!\n", errno, strerror(errno));
    //     sockfd = -1;
    //     return sockfd;
    // }

    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
        close(sockfd);
        return 0;
    }


    char buf[1024 * 1024 * 1] = { 0 };
    while (1) {
        fgets(sendline, 4096, stdin);
        send(sockfd, buf, sizeof(buf), 0);
        printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
    }
    close(sockfd);
    return 0;
}
