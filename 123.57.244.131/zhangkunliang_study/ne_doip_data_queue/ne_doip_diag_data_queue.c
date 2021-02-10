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

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "ne_doip_diag_data_queue.h"

#define NE_DOIP_PRINT (printf("[%s][line:%u]", __FILE__, __LINE__), printf)

ne_doip_queue_manager_t * ne_doip_queue_init()
{
	ne_doip_queue_manager_t *mgr = malloc(sizeof(ne_doip_queue_manager_t));
	if (NULL == mgr) {
		return 0;
	}
	memset(mgr, 0, sizeof(ne_doip_queue_manager_t));
	mgr->tail = NULL;
	mgr->head = NULL;
	NE_DOIP_PRINT("queue init is succeed !\n");
	return mgr;
}

int ne_doip_queue_deinit(ne_doip_queue_manager_t *mgr)
{
	if (NULL == mgr) {
		NE_DOIP_PRINT("start deinit 111!!!!\n");
		return 0;
	}
	ne_doip_routing_data_queue_t *free_data = mgr->head;
	while (mgr->head != NULL) {
		NE_DOIP_PRINT("start deinit 2222!!!!\n");
		free_data = mgr->head->next;
		free(mgr->head->data->data);
		free(mgr->head->data);
		free(mgr->head);
		mgr->head = free_data;
	}
	free(mgr);
	NE_DOIP_PRINT("queue deinit is succeed !\n");
	return 1;
}	

int ne_doip_queue_empty(ne_doip_queue_manager_t *mgr)
{
	return mgr->head == NULL ? 0 : 1; 
}

int ne_doip_queue_size(ne_doip_queue_manager_t *mgr)
{
	int queue_data_size = 0;
	if (NULL == mgr) {
		return 0;
	}
	ne_doip_routing_data_queue_t *num = mgr->head;
	while (num != NULL) {
		queue_data_size += num->data->data_size;
		num = num->next;
	}
	NE_DOIP_PRINT("queue data size is :[%d]\n", queue_data_size);
	return queue_data_size;

}

int ne_doip_inser_queue(ne_doip_queue_manager_t *mgr, ne_doip_routing_data_t* data)
{
	ne_doip_routing_data_queue_t *queue_node = malloc(sizeof(ne_doip_routing_data_queue_t));
	if (NULL == queue_node) {
		return 0;
	}
	memset(queue_node, 0, sizeof(ne_doip_routing_data_queue_t));

	queue_node->data = malloc(sizeof(ne_doip_routing_data_t));
	if (NULL == queue_node->data) {
		free(queue_node);
		return 0;
	}
	memset(queue_node->data, 0, sizeof(ne_doip_routing_data_t));

	queue_node->data->fd = data->fd;
	queue_node->data->data = malloc(data->data_size);
	if (NULL == queue_node->data->data) {
		return 0;
	}
	memcpy(queue_node->data->data, data->data, data->data_size);
	queue_node->data->data_size = data->data_size;
	queue_node->next = NULL;
	// memcpy(queue_node->data, data, sizeof(ne_doip_routing_data_t));

	if (mgr->head == NULL) {
		mgr->head = mgr->tail = queue_node;
		NE_DOIP_PRINT("insert first data is succeed !\n");
		NE_DOIP_PRINT("fd is :%d\n", queue_node->data->fd);
		NE_DOIP_PRINT("data is :%s\n", queue_node->data->data);
		NE_DOIP_PRINT("data size is :%u\n", queue_node->data->data_size);
		return 1;
	}

	mgr->tail->next = queue_node;
	mgr->tail = queue_node;
	NE_DOIP_PRINT("queue insert data is succeed ! \n");
	NE_DOIP_PRINT("fd is :%d\n", queue_node->data->fd);
	NE_DOIP_PRINT("data is :%s\n", queue_node->data->data);
	NE_DOIP_PRINT("data size is :%u\n", queue_node->data->data_size);
	return 1;

}

ne_doip_routing_data_t * ne_doip_front_queue(ne_doip_queue_manager_t *mgr)
{
	if (mgr->head == NULL) {
		NE_DOIP_PRINT("queue list is NULL!!!!\n");
		return 0;
	}
	ne_doip_routing_data_queue_t *node_data = mgr->head;
	mgr->head = mgr->head->next;

	ne_doip_routing_data_t *buff = malloc(sizeof(ne_doip_routing_data_t));

	buff->fd = node_data->data->fd;
	buff->data_size = node_data->data->data_size;
	buff->data = malloc(node_data->data->data_size);
	memcpy(buff->data, node_data->data->data, node_data->data->data_size);


	// ne_doip_routing_data_t buff;
	// buff.fd = node_data->data->fd;
	// buff.data_size = node_data->data->data_size;
	// memcpy(buff.data, node_data->data->data, node_data->data->data_size);

	// memcpy(buff, node_data->data, sizeof(ne_doip_routing_data_t));
	free(node_data->data->data);
	free(node_data->data);
	free(node_data);
	NE_DOIP_PRINT("queue front data is succeed ! \n");
	return buff;

}