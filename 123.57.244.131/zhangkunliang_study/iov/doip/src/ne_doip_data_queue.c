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

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "ne_doip_data_queue.h"
#include "ne_doip_util.h"
#include "ne_doip_def.h"

ne_doip_queue_manager_t * ne_doip_queue_init(void)
{
    ne_doip_queue_manager_t *mgr = (ne_doip_queue_manager_t*)malloc(sizeof(ne_doip_queue_manager_t));
    if (NULL == mgr) {
        return NULL;
    }
    memset(mgr, 0, sizeof(ne_doip_queue_manager_t));
    mgr->tail = NULL;
    mgr->head = NULL;
    NE_DOIP_PRINT("queue init is succeed !\n");
    return mgr;
}

uint8_t ne_doip_queue_deinit(ne_doip_queue_manager_t *mgr)
{
    if (NULL == mgr) {
        return NE_DOIP_FALSE;
    }
    ne_doip_routing_data_queue_t *free_data = mgr->head;
    while (mgr->head != NULL) {
        free_data = mgr->head->next;
        free(mgr->head->routing_data->data);
        free(mgr->head->routing_data);
        free(mgr->head);
        mgr->head = free_data;
    }
    free(mgr);
    NE_DOIP_PRINT("queue deinit is succeed !\n");
    return NE_DOIP_TRUE;
}

uint8_t ne_doip_queue_empty(ne_doip_queue_manager_t *mgr)
{
    if (NULL == mgr) {
        return NE_DOIP_TRUE;
    }
    return mgr->head == NULL ? NE_DOIP_TRUE : NE_DOIP_FALSE;
}

uint32_t ne_doip_queue_size(ne_doip_queue_manager_t *mgr)
{
    uint32_t queue_node_size = 0;
    if (NULL == mgr) {
        return queue_node_size;
    }
    ne_doip_routing_data_queue_t *num = mgr->head;
    while (num != NULL) {
        queue_node_size++;
        num = num->next;
    }
    NE_DOIP_PRINT("queue data node size is :[%d]\n", queue_node_size);
    return queue_node_size;
}

uint8_t ne_doip_inser_queue(ne_doip_queue_manager_t *mgr, ne_doip_routing_data_t* input_data)
{
    if (NULL == mgr) {
        return NE_DOIP_FALSE;
    }

    ne_doip_routing_data_queue_t *queue_node = (ne_doip_routing_data_queue_t*)malloc(sizeof(ne_doip_routing_data_queue_t));
    if (NULL == queue_node) {
        return NE_DOIP_FALSE;
    }
    memset(queue_node, 0, sizeof(ne_doip_routing_data_queue_t));

    queue_node->routing_data = (ne_doip_routing_data_t*)malloc(sizeof(ne_doip_routing_data_t));
    if (NULL == queue_node->routing_data) {
        free(queue_node);
        return NE_DOIP_FALSE;
    }
    memset(queue_node->routing_data, 0, sizeof(ne_doip_routing_data_t));

    queue_node->routing_data->fd = input_data->fd;
    queue_node->routing_data->data = (char*)malloc(input_data->data_size);
    if (NULL == queue_node->routing_data->data) {
        free(queue_node->routing_data);
        free(queue_node);
        return NE_DOIP_FALSE;
    }
    memset(queue_node->routing_data->data, 0, input_data->data_size);

    memcpy(queue_node->routing_data->data, input_data->data, input_data->data_size);
    queue_node->routing_data->data_size = input_data->data_size;
    queue_node->next = NULL;

    if (NULL == mgr->head) {
        mgr->head = mgr->tail = queue_node;
        NE_DOIP_PRINT("insert first data is succeed !\n");
        return NE_DOIP_TRUE;
    }

    mgr->tail->next = queue_node;
    mgr->tail = queue_node;
    NE_DOIP_PRINT("queue insert data is succeed !\n");
    return NE_DOIP_TRUE;
}

ne_doip_routing_data_t * ne_doip_front_queue(ne_doip_queue_manager_t *mgr)
{
    if ((NULL == mgr) || (NULL == mgr->head)) {
        return NULL;
    }
    ne_doip_routing_data_queue_t *node_data = mgr->head;
    mgr->head = mgr->head->next;

    ne_doip_routing_data_t *buff = (ne_doip_routing_data_t*)malloc(sizeof(ne_doip_routing_data_t));
    if (NULL == buff) {
        return NULL;
    }
    memset(buff, 0, sizeof(ne_doip_routing_data_t));

    buff->fd = node_data->routing_data->fd;
    buff->data_size = node_data->routing_data->data_size;

    buff->data = (char*)malloc(node_data->routing_data->data_size);
    if (NULL == buff->data) {
        free(buff);
        return NULL;
    }
    memset(buff->data, 0, node_data->routing_data->data_size);
    memcpy(buff->data, node_data->routing_data->data, node_data->routing_data->data_size);

    free(node_data->routing_data->data);
    free(node_data->routing_data);
    free(node_data);
    NE_DOIP_PRINT("queue front data is succeed !\n");
    return buff;

}

uint8_t ne_doip_queue_clear(ne_doip_queue_manager_t *mgr)
{
    NE_DOIP_PRINT("statr clean routing data queue !\n");
    if (NULL == mgr) {
        return NE_DOIP_FALSE;
    }
    ne_doip_routing_data_queue_t *clear_queue = mgr->head;
    while (clear_queue != NULL) {
        mgr->head = clear_queue->next;
        free(clear_queue->routing_data->data);
        free(clear_queue->routing_data);
        free(clear_queue);
        clear_queue = mgr->head;
    }
    NE_DOIP_PRINT("clear queue data is succeed !\n");
    return NE_DOIP_TRUE;
}
/* EOF */