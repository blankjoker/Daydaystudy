
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "ne_doip_diag_data_queue.h"

#define NE_DOIP_PRINT (printf("[%s][line:%u]", __FILE__, __LINE__), printf)

int main(int argc, char const *argv[])
{
	/* code */
	ne_doip_queue_manager_t *queue_list;
	queue_list = ne_doip_queue_init(queue_list);

	char buff[] = "1234567890";
	NE_DOIP_PRINT("strlen = %ld : buff = %s\n", sizeof(buff), buff);
	ne_doip_routing_data_t insert_data = {222, 
									buff, 
									sizeof(buff)};

	ne_doip_routing_data_t insert_data1 = {23, 
								buff, 
								sizeof(buff)};

	ne_doip_inser_queue(queue_list, &insert_data);	
	ne_doip_inser_queue(queue_list, &insert_data1);
	ne_doip_inser_queue(queue_list, &insert_data1);

	ne_doip_queue_size(queue_list);

	ne_doip_routing_data_t *front_data;	//= malloc(sizeof(ne_doip_routing_data_t));
	front_data = ne_doip_front_queue(queue_list);
	NE_DOIP_PRINT("fd is :%d\n", front_data->fd);
	NE_DOIP_PRINT("data is :%s\n", front_data->data);
	NE_DOIP_PRINT("data size is :%u\n", front_data->data_size);

	front_data = ne_doip_front_queue(queue_list);
	NE_DOIP_PRINT("fd is :%d\n", front_data->fd);
	NE_DOIP_PRINT("data is :%s\n", front_data->data);
	NE_DOIP_PRINT("data size is :%u\n", front_data->data_size);

	ne_doip_queue_deinit(queue_list);

	return 0;
}