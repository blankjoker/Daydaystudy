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
 * @file ne_doip_timer.h
 * @brief timer module
 */

#ifndef NE_DOIP_TIMER_H
#define NE_DOIP_TIMER_H

#include "ne_doip_util.h"

#define NE_DOIP_TIMER_MAX_NUM 255

typedef void(*ne_doip_timer_callback)(void*arg1);

typedef struct ne_doip_timer
{
    ne_doip_list_t base;
    struct timespec timeout_tick;
    int32_t timeid;
    int32_t period;         /* Callback interval */
    int32_t m_bIterate;     /* Whether iterate */
    ne_doip_timer_callback callback;
}ne_doip_timer_t;

typedef struct ne_doip_timer_manager
{
    ne_doip_list_t *timer_head;
    ne_doip_thread_t *thread;
    ne_doip_sync_t *sync;
    int8_t timer_table[NE_DOIP_TIMER_MAX_NUM + 1];
    int8_t m_bSignalflg;
}ne_doip_timer_manager_t;


ne_doip_timer_manager_t *ne_doip_create_timer_manager(void);
int32_t ne_doip_timer_start(ne_doip_timer_manager_t *manager, int32_t frequency, int32_t period, ne_doip_timer_callback callback);
void ne_doip_timer_stop(ne_doip_timer_manager_t *manager, int32_t timeid);
void ne_doip_timer_restart(ne_doip_timer_manager_t *manager, int32_t frequency, int32_t period, int32_t timeid);

void ne_doip_destroy_timer_manager(ne_doip_timer_manager_t *manager);
int32_t ne_doip_get_random_value(int32_t max_value);



#endif /* NE_DOIP_TIMER_H */
/* EOF */