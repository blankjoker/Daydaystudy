


		
		
代码修改 case 1：{	

	if (NE_DOIP_NET_TYPE_IPV6 == global_server_manager->server->config->net_type) {
	link_data->fd = ne_doip_test_tcp6_create(global_server_manager->server,
										test_udp_table->ip, test_udp_table->port);
		printf("ipv6ipv6ipv6ipv6ipv6ipv6ipv6ipv6ipv6ipv6ipv6 fd is : [%d]\n", link_data->fd);
	}
	else if (NE_DOIP_NET_TYPE_IPV4 == global_server_manager->server->config->net_type) {
		link_data->fd = ne_doip_test_tcp_create(global_server_manager->server,
											test_udp_table->ip, test_udp_table->port);
		printf("ipv4ipv4ipv4ipv4ipv4ipv4ipv4ipv4ipv4ipv4ipv4 fd is : [%d]\n", link_data->fd);
	}
	if (-1 == link_data->fd) {
		printf("link_data->fd is >>>>>>>>>>>>>>>>:\n", link_data->fd);
		return;
	}
}


代码修改 case 2：{
	ne_doip_add_ipv6_udp_socket
	memset(&(s->addr), 0, sizeof s->addr);
    s->addr.sin6_family = AF_INET6;
    s->addr.sin6_port = htons(NE_DOIP_UDP_DISCOVERY_PORT);
    s->addr.sin6_addr = in6addr_any;
    // inet_pton(AF_INET6, "fe80::5555:6666:7777:8888", &(s->addr.sin6_addr));
    // s->addr.sin6_scope_id = if_nametoindex(server->config->ifname);
}

代码修改case 3: {//	基于VIN和EID的车辆发现请求：如若全是0或者f，直接忽略。
    if (!strcmp("000000000000", data) || !strcmp("FFFFFFFFFFFF", data)) {
        return 0;
    }

    if (!strcmp("00000000000000000", data) || !strcmp("FFFFFFFFFFFFFFFFF", data)) {
        return 0;
    }
}