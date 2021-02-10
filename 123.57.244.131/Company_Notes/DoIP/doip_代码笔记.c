


先在ne_doip_add_xxx_socket中创建监听的套接字,(结构体中存放套接字fd，地址簇，监听源)
当监听的套接字有连接(TCP连接)过来或数据(UDP信息)过来，创建list ne_doip_client_t监听数据源(有无数据来)，(结构体中存放server表，通信fd和数据，监听源，client list 的属性)
创建完client list之后，创建xxx_table，(结构体中存放fd，IP,端口，逻辑地址，和通信的属性)
(属性一般指IPC通信，TCP通信，UDP通信)

以下是创建socket，并监听对应的socket是否有连接(TCP)或信息(UDP)过来：{
	
    ne_doip_ipc_socket_t *ipc_socket;
    ne_doip_ipv4_socket_t *ipv4_tcp_socket;
    ne_doip_ipv4_socket_t *ipv4_udp_socket;
    ne_doip_ipv6_socket_t *ipv6_tcp_socket;
    ne_doip_ipv6_socket_t *ipv6_udp_socket;
}

当收到socket触发的时间信息时，创建如下list(ne_doip_client_t)，创建list的同时创建对应的table：{
	
    ne_doip_list_t *ipc_client_list;
    ne_doip_list_t *net_client_list;
    ne_doip_list_t *test_client_list;
    ne_doip_list_t *client_list_free;
}


内部(外部)测试设备用的表是：{
	ipc table
	test udp table
	test tcp table
	
}

server用的表是：{
	ipc table
	tcp table
	udp table
}

(server or external test equipment)ipc table 是在ne_doip_ipc_socket_data中创建的。

(server)udp table 是在外部测试设备发送车辆发现请求或车辆公告的时候。server解析的时候创建的(ne_doip_unpack_vehicle_identification_req)。

(external test equipment)test udp table 是在外部测试设备收到车辆发现回应或车辆公告的时候创建的。

(server)tcp table 是收到tcp连接的的时候创建的(ne_doip_tcp_socket_data)。

(external test equipment)test tcp table 是在外部测试设备发送路由激活请求的时候创建的(ne_doip_pack_routing_activation_req)。



ne_doip_addr_data_t主要是作为中间变量来使用的。

ne_doip_link_data_t主要用来存储要发送的数据。接收方的IP地址，fd，端口，数据，数据大小，属于那种类型的通信IPC TCP



