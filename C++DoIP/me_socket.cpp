
#include "me_socket.h"
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/select.h>
#include <stdio.h>

#define CONNECTION_TIMEOUT_SEC      1
#define CONNECTION_TIMEOUT_USEC     0

Me_Socket::Me_Socket()
{

}

Me_Socket::~Me_Socket()
{
    delete m_instance;
}

Me_Socket* Me_Socket::m_instance = NULL;
Me_Socket* Me_Socket::insrance()
{
    if (m_instance == NULL) {
        m_instance = new Me_Socket();
    }
    return m_instance;
}

static int me_set_cloexec_or_close(int fd)
{
    long flags;

    if (fd == -1) {
        return -1;
    }

    flags = fcntl(fd, F_GETFD);
    if (flags == -1) {
        goto err;
    }

    if (fcntl(fd, F_SETFD, flags | FD_CLOEXEC) == -1) {
        goto err;
    }

    return fd;

err:
    close(fd);
    fd = -1;
    return fd;
}

int Me_Socket::me_os_socket(int domain, int type, int protocol)
{
    int fd;
    errno = 0;
    fd = socket(domain, type | SOCK_CLOEXEC, protocol);
    if (fd >= 0) {
        return fd;
    }
    if (errno != EINVAL) {
        return -1;
    }

    fd = socket(domain, type, protocol);
    return me_set_cloexec_or_close(fd);
}

int Me_Socket::me_os_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int fd;

#ifdef HAVE_ACCEPT4
    errno = 0;
    fd = accept4(sockfd, addr, addrlen, SOCK_CLOEXEC);
    if (fd >= 0) {
        return fd;
    }
    if (errno != ENOSYS) {
        return -1;
    }
#endif

    fd = accept(sockfd, addr, addrlen);
    return me_set_cloexec_or_close(fd);
}

int Me_Socket::me_os_connect(int sockfd, struct sockaddr *addr, socklen_t addrlen)
{
    if (sockfd < 0) {
        return -1;
    }

    if (addr == NULL) {
        return -1;
    }

    int flags = fcntl(sockfd, F_SETFL, O_NONBLOCK);
    if (flags < 0) {
        printf("os_connect set nonblock fail,fd:[%d]\n", sockfd);
        return -1;
    }

    int fail = 0;

    do {
        int ret = connect(sockfd, addr, addrlen);
        if (ret == 0) {
            break;
        }

        if (errno != EINPROGRESS) {
            printf("os_connect connect error\n");
            fail = 1;
            break;
        }

        errno = 0;
        fd_set wset;
        FD_ZERO(&wset);
        FD_SET(sockfd, &wset);
        printf("os_connect fd_set size:[%d] bytes\n", (int)sizeof wset);

        struct timeval tm;
        tm.tv_sec = CONNECTION_TIMEOUT_SEC;
        tm.tv_usec = CONNECTION_TIMEOUT_USEC;

        ret = select(sockfd + 1, NULL, &wset, NULL, &tm);

        if (ret < 0) {
            printf("os_connect select error\n");
            fail = 1;
            break;
        }

        if (ret == 0) {
            printf("os_connect select time out\n");
            errno = ETIMEDOUT;
            fail = 1;
            break;
        }

        if (!FD_ISSET(sockfd, &wset)) {
            printf("os_connect FD_ISSET unknown event!\n");
            fail = 1;
            break;
        }

        int error = -1;
        socklen_t len = sizeof(int);
        if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0) {
            printf("os_connect getsockopt error code:%d, message:%s\n", errno, strerror(errno));
            fail = 1;
            break;
        }

        if (error) {
            printf("os_connect SO_ERROR exists! error:[%d]\n", error);
            errno = error;
            fail = 1;
            break;
        }
    } while (0);

    if (fcntl(sockfd, F_SETFL, flags) < 0) {
        printf("os_connect restore fail,fd:[%d]\n", sockfd);
        return -1;
    }

    if (fail) {
        return -1;
    }

    return 0;
}

void Me_Socket::me_os_get_ifname(char* ifname, int fd, char *ip)
{

}

int Me_Socket::me_os_get_ip(const char *ifname, char *ip, int iplen)
{
    return 0;
}

