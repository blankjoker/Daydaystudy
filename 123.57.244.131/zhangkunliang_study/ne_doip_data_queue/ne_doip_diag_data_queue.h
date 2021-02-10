/**
 * Copyright @ 2019 iAuto (Shanghai) Co., Ltd.
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are NOT permitted except as agreed by
 * iAuto (Shanghai) Co., Ltd.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */
/**
 * @file ne_doip_diag_data.h
 * @brief doip routing data queue
 */

#ifndef NE_DOIP_DIAGDATA
#define NE_DOIP_DIAGDATA

typedef struct ne_doip_routing_data 
{
    int fd;
    char* data;
    unsigned int data_size;
}ne_doip_routing_data_t;


typedef struct ne_doip_routing_data_queue
{
	ne_doip_routing_data_t *data;
	struct ne_doip_routing_data_queue *next;
}ne_doip_routing_data_queue_t;


typedef struct ne_doip_queue_manager
{
	ne_doip_routing_data_queue_t *head;
	ne_doip_routing_data_queue_t *tail;
}ne_doip_queue_manager_t;


ne_doip_queue_manager_t * ne_doip_queue_init();
int ne_doip_queue_deinit(ne_doip_queue_manager_t *mgr);

int ne_doip_queue_empty(ne_doip_queue_manager_t *mgr);
int ne_doip_queue_size(ne_doip_queue_manager_t *mgr);

int ne_doip_inser_queue(ne_doip_queue_manager_t *mgr, ne_doip_routing_data_t* data);
ne_doip_routing_data_t* ne_doip_front_queue(ne_doip_queue_manager_t *mgr);


#endif //NE_DOIP_DIAGDATA
/* EOF */