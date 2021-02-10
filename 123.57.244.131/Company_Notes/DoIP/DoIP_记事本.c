
{
	界面测试流程：
	界面程序启动后，相关的初始化在构造函数里面已经完成。
	
	然后另一个服务器端会发送三个车辆发现的公告。

	1.之后进行车辆发现请求，得到车辆的VIN,EID,GID等信息，还有相关和逻辑地址等信息。
	
	2.车辆发现之后，可进行power mode和status状态信息的查看，两者随意点击。
	
	3.开始路由转发，建立TCP连接，方便之后进行诊断。
	
	4.有的gateway和node节点是没有授权的，大于16表示已经授权。否则需要进行授权，授权码12345678.授权之后才可以进行诊断。
	
	5.开始进行gateway和node的这诊断。诊断分为数据诊断和文件诊断，有相关的逻辑操作。
		
	界面端操作方案：
	{
		有些界面文本框的值是点击的时候才出现的，可以直接实现设定一些值。
		设置一个定时器，每一秒重头到尾调用相关的函数。
	}
}


先介绍三个概念：自身对齐值、指定对齐值、有效对齐值。
自身对齐值：数据类型本身的对齐值，例如char类型的自身对齐值是1，short类型是2；
指定对齐值：编译器或程序员指定的对齐值，32位单片机的指定对齐值默认是4；
有效对齐值：自身对齐值和指定对齐值中较小的那个。
对齐有两个规则：
1、不但结构体的成员有有效对齐值，结构体本身也有对齐值，这主要是考虑结构体的数组，对于结构体或者类，要将其补齐为其有效对齐值的整数倍。结构体的有效对齐值是其最大数据成员的自身对齐值；
2、存放成员的起始地址必须是该成员有效对齐值的整数倍。

cgw_control=TRUE   //TRUE方案2   FLASE方案1

IP地址分配问题：{
	Additional mechanisms might be required for vehicle network architectures containing more than one DoIP entity, 
	in order to ensure that all DoIP entities start assigning a valid IP address once the activation line is activated.
	一旦使能线插入，所有的doip node应该分配一个有效的IP地址。
}

全部基于DoIP_Stack_Stable_2.0修改
到时候三个都要整合在一起
版本修改：{
	
	加完锁的版本：DoIP_Stack_Stable_2.1 

	改epoll为select的版本：DoIP_Stack_Stable_3.0
	
	合并sync和select版本：DoIP_Stack_Stable_4.0
	
	修改routing传EID改为传逻辑地址：DoIP_Stack_Stable_5.0   (基于4.0修改)
	

}


alive check {
	node_tcp_table->connection_state = NE_DOIP_CONNECT_STATE_REGISTERED_ROUTING_ACTIVE;
	node_tcp_table->fd_regist_flag = NE_DOIP_TRUE;
	node_tcp_table->equip_logical_address = equip_logical_address;
	ne_doip_link_data_t link_data_t;
	memset(&link_data_t, 0, sizeof link_data_t);
	link_data_t.fd = node_tcp_table->fd;
	link_data_t.comm_type = NE_DOIP_SOCKET_TYPE_TCP;
	ne_doip_sync_start(global_server_manager->node_ipc_list_sync);
	ne_doip_node_ipc_table_t* ipc_entity_table = ne_doip_node_ipc_list_find_entity();
	if (ipc_entity_table != NULL) {
		ne_doip_pack_routing_activation_res(&link_data_t, equip_logical_address,
											ipc_entity_table->entity_logical_address,
											NE_DOIP_RA_RES_ROUTING_SUCCESSFULLY_ACTIVATED,
											0x00000000);
	}
	ne_doip_sync_end(global_server_manager->node_ipc_list_sync);
}

doip 版本管理规则：

1.000.000_xxx
1 ：固定
000：第一位 0 代表系统（0：linux 1：QNX 2：FreeRTOS...）， 后两位 00 代表master 版本
000：三位 000 代表分支版本
xxx: 代表项目代号，如dipper


ifconfig vlan51 192.168.50.1
ip route add table 97 192.168.50.0/24 via 192.168.50.11 dev vlan51



