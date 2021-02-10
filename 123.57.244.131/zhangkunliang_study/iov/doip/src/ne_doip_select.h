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
 * @file ne_doip_select.h
 * @brief doip ne_doip_select
 */

#ifndef NE_DOIP_SELECT_H
#define NE_DOIP_SELECT_H

#include <sys/select.h>
#include <stdint.h>

#include "ne_doip_util.h"
#include "ne_doip_thread.h"

#define NE_DOIP_EV_READ		0x01
#define NE_DOIP_EV_WRITE	0x02

#define NE_DOIP_EV_NORML    0x00
#define NE_DOIP_EV_INTER	0x01

#define NE_DOIP_SEL_ADD     0x00
#define NE_DOIP_SEL_DEL     0x01
#define NE_DOIP_SEL_MOD     0x02

typedef union event_data {
    void *ptr;
    int32_t fd;
    uint32_t u32;
    uint64_t u64;
}event_data_t;

typedef struct ne_doip_event {
    ne_doip_list_t base;
    int32_t fd;
    int32_t ev_type;
    int32_t events;
    event_data_t data;
}ne_doip_event_t;

typedef struct ne_doip_select {
    int32_t max_fd;
    size_t fd_setsize;
    int32_t notify_fd[2];
    fd_set *event_readset_in;
    fd_set *event_writeset_in;
    fd_set *event_readset_out;
    fd_set *event_writeset_out;
    ne_doip_list_t event_list;
    ne_doip_sync_t *event_sync;
}ne_doip_select_t;


ne_doip_select_t *ne_doip_select_create(void);
void ne_doip_select_destroy(ne_doip_select_t *sel_ptr);
int32_t ne_doip_select_ctl(ne_doip_select_t *sel_ptr, int32_t type, int32_t fd, ne_doip_event_t *event);
int32_t ne_doip_select_dispatch(ne_doip_select_t *sel_ptr, ne_doip_event_t *event, int32_t length, int32_t timeout);
int32_t ne_doip_select_notify(ne_doip_select_t *sel_ptr);

#endif /* NE_DOIP_SELECT_H */
/* EOF */
