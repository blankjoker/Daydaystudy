#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>

int main()
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;

    unlink("server_socket");
    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "server_socket");

    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
    listen(server_sockfd, 5);
    printf("server waiting for client connect\n");
    client_len = sizeof(client_address);
    client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, (socklen_t *)&client_len);
    printf("the server wait for client data\n");

    while (1) {

        int ret = 0;
        char buff[100] = { 0 };
        ret = read(client_sockfd, &buff, 100);
        if (ret <= 0) {
            printf("read data is <= 0, close socket\n");
            close(client_sockfd);
            sleep(1);
            continue;
        }
        printf("read data is :%s", buff);

    }

    close(client_sockfd);
    unlink("server_socket");
    return 0;
}