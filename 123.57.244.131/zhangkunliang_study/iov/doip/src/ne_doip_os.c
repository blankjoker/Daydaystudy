/**
 * Copyright @ 2015 - 2019 iAuto Software(Shanghai) Co., Ltd.
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are NOT permitted except as agreed by
 * iAuto Software(Shanghai) Co., Ltd.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */

#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#ifdef LINUX_OS
#include <sys/epoll.h>
#endif
#include <net/if.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/select.h>
#include <stdio.h>

#include "ne_doip_os.h"
#include "ne_doip_util.h"

#define CONNECTION_TIMEOUT_SEC      0
#define CONNECTION_TIMEOUT_USEC     100000 /* 100ms */

static int32_t
ne_doip_set_cloexec_or_close(int32_t fd)
{
    int32_t flags;

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

int32_t
ne_doip_os_epoll_create(void)
{
#ifdef LINUX_OS
    int32_t fd;

#ifdef EPOLL_CLOEXEC
    errno = 0;
    fd = epoll_create1(EPOLL_CLOEXEC);
    if (fd >= 0) {
        return fd;
    }
    if (errno != EINVAL) {
        return -1;
    }
#endif

    fd = epoll_create(1);
    return ne_doip_set_cloexec_or_close(fd);
#else
    return -1;
#endif /* LINUX_OS */
}

int32_t
ne_doip_os_socket(int32_t domain, int32_t type, int32_t protocol)
{
    int32_t fd;
    errno = 0;
    fd = socket(domain, type | SOCK_CLOEXEC, protocol);
    if (fd >= 0) {
        return fd;
    }
    if (errno != EINVAL) {
        return -1;
    }

    fd = socket(domain, type, protocol);
    return ne_doip_set_cloexec_or_close(fd);
}

int32_t
ne_doip_os_accept(int32_t sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int32_t fd;

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
    return ne_doip_set_cloexec_or_close(fd);
}

int32_t
ne_doip_os_connect(int32_t sockfd, struct sockaddr *addr, socklen_t addrlen)
{
    if (sockfd < 0) {
        return -1;
    }

    if (addr == NULL) {
        return -1;
    }

    int32_t flags = fcntl(sockfd, F_SETFL, O_NONBLOCK);
    if (flags < 0) {
        NE_DOIP_PRINT("os_connect set nonblock fail,fd:[%d]\n", sockfd);
        return -1;
    }

    int32_t fail = 0;

    do {
        int32_t ret = connect(sockfd, addr, addrlen);
        if (ret == 0) {
            break;
        }

        if (errno != EINPROGRESS) {
            NE_DOIP_PRINT("os_connect connect error\n");
            fail = 1;
            break;
        }

        errno = 0;
        fd_set wset;
        FD_ZERO(&wset);
        FD_SET(sockfd, &wset);
        NE_DOIP_PRINT("os_connect fd_set size:[%ld] bytes\n", sizeof wset);

        struct timeval timeout;
        timeout.tv_sec = CONNECTION_TIMEOUT_SEC;
        timeout.tv_usec = CONNECTION_TIMEOUT_USEC;

        ret = select(sockfd + 1, NULL, &wset, NULL, &timeout);

        if (ret < 0) {
            NE_DOIP_PRINT("os_connect select error\n");
            fail = 1;
            break;
        }

        if (ret == 0) {
            NE_DOIP_PRINT("os_connect select time out\n");
            errno = ETIMEDOUT;
            fail = 1;
            break;
        }

        if (!FD_ISSET(sockfd, &wset)) {
            NE_DOIP_PRINT("os_connect FD_ISSET unknown event!\n");
            fail = 1;
            break;
        }

        int32_t error = -1;
        socklen_t len = sizeof(int32_t);
        if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0) {
            NE_DOIP_PRINT("os_connect getsockopt error code:%d, message:%s\n", errno, strerror(errno));
            fail = 1;
            break;
        }

        if (error) {
            NE_DOIP_PRINT("os_connect SO_ERROR exists! error:[%d]\n", error);
            errno = error;
            fail = 1;
            break;
        }
    } while (0);

    if (fcntl(sockfd, F_SETFL, flags) < 0) {
        NE_DOIP_PRINT("os_connect restore fail,fd:[%d]\n", sockfd);
        return -1;
    }

    if (fail) {
        return -1;
    }

    return 0;
}

void ne_doip_os_get_ifname(char* ifname, int32_t fd, char *ip)
{
    NE_DOIP_PRINT("ne_doip_os_get_ifname is enter. fd[%d], ip:[%s].\n", fd, ip);
    char *ip_tmp = malloc(strlen(ip) + 1);
    if (ip_tmp == NULL) {
        NE_DOIP_PRINT("os_get_ifname ip_tmp == NULL\n");
        return;
    }

    memcpy(ip_tmp, ip, strlen(ip) + 1);

    struct ifconf ifc;
    char buf[512];
    struct ifreq *ifr;

    ifc.ifc_buf = buf;
    ifc.ifc_len = 512;

    if (ioctl(fd, SIOCGIFCONF, &ifc) < 0) {
        NE_DOIP_PRINT("call ioctl is failed..\n");
    }

    ifr = (struct ifreq*)buf;
    int32_t i = 0;
    for (i = (ifc.ifc_len / sizeof(struct ifreq)); i > 0; i--) {
        char *ip_t = inet_ntoa(((struct sockaddr_in*)&(ifr->ifr_addr))->sin_addr);
        if (0 == strcmp(ip_tmp, ip_t)) {
            memcpy(ifname, ifr->ifr_name, strlen(ifr->ifr_name));
            break;
        }
        ifr++;
    }

    free(ip_tmp);
}

int32_t
ne_doip_os_get_ip(const char *ifname, char *ip, int32_t iplen)
{
    NE_DOIP_PRINT("ne_doip_os_get_ip ioctl ifname is:%s\n", ifname);
    int32_t fd;
    struct sockaddr_in sin;
    struct ifreq ifr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        return -1;
    }

    memset(&ifr, 0, sizeof ifr);
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ - 1);
    ifr.ifr_name[IFNAMSIZ - 1] = 0;

    // if error: No such device
    if (ioctl(fd, SIOCGIFADDR, &ifr) < 0) {
        NE_DOIP_PRINT("os_get_ip ioctl error code:%d, message:%s\n", errno, strerror(errno));
        close(fd);
        return -1;
    }

    memcpy(&sin, &ifr.ifr_addr, sizeof sin);
    snprintf(ip, iplen, "%s", inet_ntoa(sin.sin_addr));

    close(fd);
    return 0;
}
/* EOF */
