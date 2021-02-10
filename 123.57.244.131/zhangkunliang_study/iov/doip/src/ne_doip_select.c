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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>

#include "ne_doip_select.h"

#define FD_SET_SIZE     1024
#define FD_SET_BITS     (8 * sizeof(fd_mask))

#define FD_BITS_TO_BYTES(n) \
    ((((n) - 1) / FD_SET_BITS + 1) * sizeof(fd_mask))

static int32_t ne_doip_internal_socket(int32_t notify_fd[2]);
static int32_t ne_doip_init_notify(ne_doip_select_t *sel_ptr);
static int32_t ne_doip_select_notify_internal(ne_doip_select_t *sel_ptr);
static int32_t ne_doip_select_add(ne_doip_select_t *sel_ptr, int32_t fd, ne_doip_event_t *event);
static int32_t ne_doip_select_del(ne_doip_select_t *sel_ptr, int32_t fd);
static ne_doip_event_t *ne_doip_select_find(ne_doip_select_t *sel_ptr, int32_t fd);
static int32_t ne_doip_select_response(ne_doip_select_t *sel_ptr);

DOIP_EXPORT ne_doip_select_t *
ne_doip_select_create(void)
{
    ne_doip_select_t *sel_ptr = malloc(sizeof *sel_ptr);
    if (sel_ptr == NULL) {
        return NULL;
    }

    memset(sel_ptr, 0, sizeof *sel_ptr);

    sel_ptr->fd_setsize = FD_BITS_TO_BYTES(FD_SET_SIZE);
    int32_t fail = 0;
    do {
        sel_ptr->event_readset_in = malloc(sel_ptr->fd_setsize);
        if (sel_ptr->event_readset_in == NULL) {
            fail = 1;
            break;
        }

        sel_ptr->event_readset_out = malloc(sel_ptr->fd_setsize);
        if (sel_ptr->event_readset_out == NULL) {
            fail = 1;
            break;
        }

        sel_ptr->event_writeset_in = malloc(sel_ptr->fd_setsize);
        if (sel_ptr->event_writeset_in == NULL) {
            fail = 1;
            break;
        }

        sel_ptr->event_writeset_out = malloc(sel_ptr->fd_setsize);
        if (sel_ptr->event_writeset_out == NULL) {
            fail = 1;
            break;
        }
    } while (0);

    if (fail) {
        if (sel_ptr->event_readset_in) {
            free(sel_ptr->event_readset_in);
        }
        if (sel_ptr->event_readset_out) {
            free(sel_ptr->event_readset_out);
        }
        if (sel_ptr->event_writeset_in) {
            free(sel_ptr->event_writeset_in);
        }
        if (sel_ptr->event_writeset_out) {
            free(sel_ptr->event_writeset_out);
        }

        free(sel_ptr);
        return NULL;
    }

    memset(sel_ptr->event_readset_in, 0, sel_ptr->fd_setsize);
    memset(sel_ptr->event_readset_out, 0, sel_ptr->fd_setsize);
    memset(sel_ptr->event_writeset_in, 0, sel_ptr->fd_setsize);
    memset(sel_ptr->event_writeset_out, 0, sel_ptr->fd_setsize);

    ne_doip_list_init(&sel_ptr->event_list);
    sel_ptr->event_sync = ne_doip_sync_create();
    sel_ptr->max_fd = 0;
    sel_ptr->notify_fd[0] = -1;
    sel_ptr->notify_fd[1] = -1;

    NE_DOIP_PRINT("select_create fd_setsize:[%d]\n", sel_ptr->fd_setsize);

    if (ne_doip_init_notify(sel_ptr) < 0) {
        ne_doip_select_destroy(sel_ptr);
        return NULL;
    }

    return sel_ptr;
}


DOIP_EXPORT void
ne_doip_select_destroy(ne_doip_select_t *sel_ptr)
{
    if (sel_ptr == NULL) {
        return;
    }

    if (sel_ptr->event_readset_in != NULL) {
        free(sel_ptr->event_readset_in);
    }
    if (sel_ptr->event_readset_out != NULL) {
        free(sel_ptr->event_readset_out);
    }
    if (sel_ptr->event_writeset_in != NULL) {
        free(sel_ptr->event_writeset_in);
    }
    if (sel_ptr->event_writeset_out != NULL) {
        free(sel_ptr->event_writeset_out);
    }

    ne_doip_sync_start(sel_ptr->event_sync);

    ne_doip_event_t *iter;
    ne_doip_event_t *tmp;
    ne_doip_list_for_each_safe(iter, tmp, &(sel_ptr->event_list), base) {
        ne_doip_list_remove((ne_doip_list_t *)iter);
        free(iter);
    }

    ne_doip_sync_end(sel_ptr->event_sync);

    if (sel_ptr->notify_fd[0] > 0) {
        close(sel_ptr->notify_fd[0]);
    }

    if (sel_ptr->notify_fd[1]) {
        close(sel_ptr->notify_fd[1]);
    }

    ne_doip_sync_destroy(sel_ptr->event_sync);

    memset(sel_ptr, 0, sizeof *sel_ptr);

    free(sel_ptr);
}

DOIP_EXPORT int32_t
ne_doip_select_ctl(ne_doip_select_t *sel_ptr, int32_t type, int32_t fd, ne_doip_event_t *event)
{
    int32_t ret = -1;

    switch (type) {
    case NE_DOIP_SEL_ADD:
        ret = ne_doip_select_add(sel_ptr, fd, event);
        break;
    case NE_DOIP_SEL_MOD:
        ret = ne_doip_select_del(sel_ptr, fd);
        if (ret == 0) {
            NE_DOIP_PRINT("select_ctl add after delete successfully\n");
            ret = ne_doip_select_add(sel_ptr, fd, event);
        }
        break;
    case NE_DOIP_SEL_DEL:
        ret = ne_doip_select_del(sel_ptr, fd);
        break;
    default:
        NE_DOIP_PRINT("select_ctl invalid type:[%d], fd:[%d]\n", type, fd);
        break;
    }

    return ret;
}

DOIP_EXPORT int32_t
ne_doip_select_dispatch(ne_doip_select_t *sel_ptr, ne_doip_event_t *event, int32_t length, int32_t timeout)
{
    ne_doip_sync_start(sel_ptr->event_sync);

    int32_t nfds = sel_ptr->max_fd + 1;
    int32_t i = 0;
    int32_t count = 0;
    int32_t res = 0;

    struct timeval *tv = NULL;
    struct timeval temp;
    if (timeout >= 0) {
        temp.tv_sec = timeout / 1000;
        temp.tv_usec = (timeout % 1000) * 1000;
        tv = &temp;
    }

    memcpy(sel_ptr->event_readset_out, sel_ptr->event_readset_in, sel_ptr->fd_setsize);
    memcpy(sel_ptr->event_writeset_out, sel_ptr->event_writeset_in, sel_ptr->fd_setsize);

    ne_doip_sync_end(sel_ptr->event_sync);

    errno = 0;
    res = select(nfds, sel_ptr->event_readset_out, sel_ptr->event_writeset_out, NULL, tv);

    ne_doip_sync_start(sel_ptr->event_sync);

    if (res < 0) {
        if (errno != EINTR) {
            NE_DOIP_PRINT("select_dispatch select error\n");
            ne_doip_sync_end(sel_ptr->event_sync);
            return -1;
        }

        ne_doip_sync_end(sel_ptr->event_sync);
        return 0;
    }

    for (i = 0; i < nfds; ++i) {
        res = 0;
        if (FD_ISSET(i, sel_ptr->event_readset_out)) {
            res |= NE_DOIP_EV_READ;
        }
        if (FD_ISSET(i, sel_ptr->event_writeset_out)) {
            res |= NE_DOIP_EV_WRITE;
        }

        if (res == 0) {
            continue;
        }

        if (count >= length) {
            NE_DOIP_PRINT("select_dispatch event queue is full[i:%d][length:%d]\n", i, length);
            break;
        }

        ne_doip_event_t *ev = ne_doip_select_find(sel_ptr, i);
        if (ev == NULL) {
            NE_DOIP_PRINT("select_dispatch can not find fd[%d]\n", i);
            continue;
        }
        else {
            if (ev->ev_type == NE_DOIP_EV_INTER) {
                ne_doip_select_response(sel_ptr);
                continue;
            }

            event[count] = *ev;
            event[count].events = res;
            ++count;
        }
    }

    ne_doip_sync_end(sel_ptr->event_sync);

    return count;
}

DOIP_EXPORT int32_t
ne_doip_select_notify(ne_doip_select_t *sel_ptr)
{
    int32_t r = 0;
    if (sel_ptr == NULL) {
        return -1;
    }

    ne_doip_sync_start(sel_ptr->event_sync);

    r = ne_doip_select_notify_internal(sel_ptr);

    ne_doip_sync_end(sel_ptr->event_sync);

    return r;
}

static int32_t
ne_doip_select_add(ne_doip_select_t *sel_ptr, int32_t fd, ne_doip_event_t *event)
{
    ne_doip_sync_start(sel_ptr->event_sync);

    ne_doip_event_t *ev = ne_doip_select_find(sel_ptr, fd);
    if (ev != NULL) {
        NE_DOIP_PRINT("select_add fd[%d] has existed\n", fd);
        ne_doip_sync_end(sel_ptr->event_sync);
        return -1;
    }

    ev = malloc(sizeof *ev);
    if (ev == NULL) {
        NE_DOIP_PRINT("select_add ev == NULL\n");
        ne_doip_sync_end(sel_ptr->event_sync);
        return -1;
    }

    *ev = *event;
    ev->fd = fd;
    NE_DOIP_PRINT("ne_doip_select_add fd is [%d]\n", fd);
    ne_doip_list_insert(sel_ptr->event_list.prev, (ne_doip_list_t *)ev);

    if (sel_ptr->max_fd < fd) {
        sel_ptr->max_fd = fd;
    }

    int32_t events = event->events;
    if (events & NE_DOIP_EV_READ) {
        FD_SET(fd, sel_ptr->event_readset_in);
    }

    if (events & NE_DOIP_EV_WRITE) {
        FD_SET(fd, sel_ptr->event_writeset_in);
    }

    int32_t ret = ne_doip_select_notify_internal(sel_ptr);
    if (ret < 0) {
        NE_DOIP_PRINT("select_add failed to notify\n");
    }

    ne_doip_sync_end(sel_ptr->event_sync);

    return 0;
}

static int32_t
ne_doip_select_del(ne_doip_select_t *sel_ptr, int32_t fd)
{

    ne_doip_sync_start(sel_ptr->event_sync);

    ne_doip_event_t *ev = ne_doip_select_find(sel_ptr, fd);
    if (ev == NULL) {
        NE_DOIP_PRINT("select_del can not find fd[%d]\n", fd);
        ne_doip_sync_end(sel_ptr->event_sync);
        return -1;
    }

    int32_t events = ev->events;

    ne_doip_list_remove((ne_doip_list_t *)ev);
    free(ev);

    if (events & NE_DOIP_EV_READ) {
        FD_CLR(fd, sel_ptr->event_readset_in);
    }

    if (events & NE_DOIP_EV_WRITE) {
        FD_CLR(fd, sel_ptr->event_writeset_in);
    }

    int32_t ret = ne_doip_select_notify_internal(sel_ptr);
    if (ret < 0) {
        NE_DOIP_PRINT("select_add failed to notify\n");
    }

    ne_doip_sync_end(sel_ptr->event_sync);

    return 0;
}

static ne_doip_event_t *
ne_doip_select_find(ne_doip_select_t *sel_ptr, int32_t fd)
{
    if (fd < 0) {
        NE_DOIP_PRINT("select_find fd < 0!\n");
        return NULL;
    }

    ne_doip_event_t *iter;

    ne_doip_list_for_each(iter, &(sel_ptr->event_list), base) {
        if (iter->fd == fd) {
            return iter;
        }
    }

    return NULL;
}

static int32_t
ne_doip_select_response(ne_doip_select_t *sel_ptr)
{
    if (sel_ptr == NULL) {
        return -1;
    }

    char buf[1];
    ssize_t r;
    buf[0] = (char) 0;
    errno = 0;
    r = read(sel_ptr->notify_fd[0], buf, 1);

    if (r <= 0) {
        NE_DOIP_PRINT("select_response read error code:%d, message:%s\n", errno, strerror(errno));
        return -1;
    }

    return 0;
}

static int32_t
ne_doip_select_notify_internal(ne_doip_select_t *sel_ptr)
{
    if (sel_ptr == NULL) {
        return -1;
    }

    if (sel_ptr->notify_fd[1] < 0) {
        return -1;
    }

    char buf[1];
    ssize_t r;
    buf[0] = (char) 0;
    errno = 0;
    r = write(sel_ptr->notify_fd[1], buf, 1);
    if (r <= 0) {
        NE_DOIP_PRINT("select_notify_internal write error code:%d, message:%s\n", errno, strerror(errno));
        return -1;
    }

    return ((r < 0) && (errno != EAGAIN)) ? -1 : 0;
}

static int32_t
ne_doip_internal_socket(int32_t notify_fd[2])
{
    int32_t listener = -1;
    int32_t connector = -1;
    int32_t acceptor = -1;
    socklen_t size = 0;
    struct sockaddr_in listen_addr;
    struct sockaddr_in connect_addr;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0) {
        NE_DOIP_PRINT("internal_socket listener create error!\n");
        return -1;
    }

    size = sizeof listen_addr;
    memset(&listen_addr, 0, size);
    listen_addr.sin_family = AF_INET;
    listen_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    listen_addr.sin_port = 0;

    errno = 0;
    if (bind(listener, (struct sockaddr *)&listen_addr, size) < 0) {
        close(listener);
        listener = -1;
        NE_DOIP_PRINT("internal_socket bind error code:%d, message:%s\n", errno, strerror(errno));
        return listener;
    }

    errno = 0;
    if (listen(listener, 1) < 0) {
        close(listener);
        listener = -1;
        NE_DOIP_PRINT("internal_socket listen error code:%d, message:%s\n", errno, strerror(errno));
        return listener;
    }


    connector = socket(AF_INET, SOCK_STREAM, 0);
    if (connector < 0) {
        close(listener);
        listener = -1;
        NE_DOIP_PRINT("internal_socket connector create error!\n");
        return listener;
    }

    errno = 0;
    size = sizeof connect_addr;
    if (getsockname(listener, (struct sockaddr *)&connect_addr, &size) < 0) {
        close(listener);
        close(connector);
        listener = -1;
        connector = -1;
        NE_DOIP_PRINT("internal_socket getsockname error code:%d, message:%s\n", errno, strerror(errno));
        return -1;
    }
    char *ip = inet_ntoa(connect_addr.sin_addr);
    int32_t port = ntohs(connect_addr.sin_port);
    NE_DOIP_PRINT("internal_socket getsockname connector:[%d], addr:[%s], port:[%d]\n", connector, ip, port);

    errno = 0;
    if (connect(connector, (struct sockaddr *)&connect_addr, size) < 0) {
        close(listener);
        close(connector);
        listener = -1;
        connector = -1;
        NE_DOIP_PRINT("internal_socket connect error code:%d, message:%s\n", errno, strerror(errno));
        return -1;
    }

    errno = 0;
    size = sizeof(listen_addr);
    acceptor = accept(listener, (struct sockaddr *)&listen_addr, &size);
    if (acceptor < 0) {
        close(listener);
        close(connector);
        listener = -1;
        connector = -1;
        NE_DOIP_PRINT("internal_socket accept error code:%d, message:%s\n", errno, strerror(errno));
        return -1;
    }
    ip = inet_ntoa(listen_addr.sin_addr);
    port = ntohs(listen_addr.sin_port);
    NE_DOIP_PRINT("internal_socket getsockname acceptor:[%d], addr:[%s], port:[%d]\n", acceptor, ip, port);

    close(listener);
    notify_fd[0] = connector;
    notify_fd[1] = acceptor;

    return 0;
}

static int32_t
ne_doip_init_notify(ne_doip_select_t *sel_ptr)
{
    if (ne_doip_internal_socket(sel_ptr->notify_fd) < 0) {
        return -1;
    }

    int32_t fail = 0;
    int32_t fd0 = sel_ptr->notify_fd[0];
    int32_t fd1 = sel_ptr->notify_fd[1];

    do {
        // make two sockets nonblocking
        int32_t flags = fcntl(fd0, F_GETFL, NULL);
        if (flags < 0) {
            NE_DOIP_PRINT("init_notification fd0 fcntl(%d, F_GETFL)\n", fd0);
            fail = 1;
            break;
        }
        if (fcntl(fd0, F_SETFL, flags | O_NONBLOCK) == -1) {
            NE_DOIP_PRINT("init_notification fd0 fcntl(%d, F_SETFL)\n", fd0);
            fail = 1;
            break;
        }
        flags = fcntl(fd1, F_GETFL, NULL);
        if (flags < 0) {
            NE_DOIP_PRINT("init_notification fd1 fcntl(%d, F_GETFL)\n", fd1);
            fail = 1;
            break;
        }
        if (fcntl(fd1, F_SETFL, flags | O_NONBLOCK) == -1) {
            NE_DOIP_PRINT("init_notification fd1 fcntl(%d, F_SETFL)\n", fd1);
            fail = 1;
            break;
        }

        ne_doip_event_t event;

        ne_doip_list_init((ne_doip_list_t *)&event);
        event.ev_type = NE_DOIP_EV_INTER;
        event.data.ptr = NULL;
        event.events = NE_DOIP_EV_READ;

        if (ne_doip_select_add(sel_ptr, fd0, &event) < 0) {
            fail = 1;
            break;
        }
    } while (0);

    if (fail) {
        close(fd0);
        sel_ptr->notify_fd[0] = -1;
        close(fd1);
        sel_ptr->notify_fd[1] = -1;
        return -1;
    }

    return 0;
}
