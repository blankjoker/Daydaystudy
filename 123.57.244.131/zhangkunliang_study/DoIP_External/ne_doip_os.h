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
/**
 * @file ne_doip_os.h
 * @brief 1. Provide a common interface 2. System API adaptation for multiple platforms
 */

#ifndef NE_DOIP_OS_H
#define NE_DOIP_OS_H

/* Create an epoll and return a file descriptor */
int32_t ne_doip_os_epoll_create(void);

/* Create a socket */
int32_t ne_doip_os_socket(int32_t domain, int32_t type, int32_t protocol);

/* Listening link */
int32_t ne_doip_os_accept(int32_t sockfd, struct sockaddr *addr, socklen_t *addrlen);

/* connect to server */
int32_t ne_doip_os_connect(int32_t sockfd, struct sockaddr *addr, socklen_t addrlen);

/* get ifname by ip address */
void ne_doip_os_get_ifname(char* ifname, int32_t fd, char *ip);

/* get ip address by ifname */
int32_t ne_doip_os_get_ip(const char *ifname, char *ip, int32_t iplen);

#endif /* NE_DOIP_OS_H */
/* EOF */