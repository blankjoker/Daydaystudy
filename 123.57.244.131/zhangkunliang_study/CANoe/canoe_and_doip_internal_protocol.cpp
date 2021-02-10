
debug 9 byte
   1  1    2        4  1  
0x02 FD 0000 00000001 01	>> power mode is true
0x02 FD 0000 00000001 02	>> power mode is false

0x02 FD 0000 00000001 03	>> doip activation line is true
0x02 FD 0000 00000001 04	>> doip activation line is false

0x02 FD 0000 00000001 05	>> doip vehicle announce
0x02 FD 0000 00000001 06	>> doip vehicle announce other ports

0x02 FD 0000 00000001 07	>> doip routing activation auth
0x02 FD 0000 00000001 08	>> doip routing activation not auth

0x02 FD 0000 00000001 09	>> doip entity type change node
0x02 FD 0000 00000001 0A    >> doip entity type change gateway

0x02 FD 0000 00000001 0B    >> doip entity type change mcts 1
0x02 FD 0000 00000001 0C	>> doip entity type change mcts 255


#define NE_DPIP_TESTCASE_DEBUG_POWER_MODE_TRUE					0x01
#define NE_DPIP_TESTCASE_DEBUG_POWER_MODE_FALSE 				0x02
#define NE_DPIP_TESTCASE_DEBUG_ACTIVATION_LINE_TRUE 			0x03
#define NE_DPIP_TESTCASE_DEBUG_ACTIVATION_LINE_FALSE 			0x04
#define NE_DPIP_TESTCASE_DEBUG_VEHICLE_ANNOUNCE 				0x05
#define NE_DPIP_TESTCASE_DEBUG_VEHICLE_ANNOUNCE_OTHER_PORTS 	0x06
#define NE_DPIP_TESTCASE_DEBUG_ROUTING_ACTIVATION_AUTH_TRUE 	0x07
#define NE_DPIP_TESTCASE_DEBUG_ROUTING_ACTIVATION_AUTH_FALSE 	0x08
#define NE_DPIP_TESTCASE_DEBUG_ENTITY_TYPE_NODE					0x09
#define NE_DPIP_TESTCASE_DEBUG_ENTITY_TYPE_GATEWAY              0x0A
#define NE_DPIP_TESTCASE_DEBUG_CHANGE_MCTS                      0x0B
#define NE_DPIP_TESTCASE_DEBUG_CHANGE_MCTS_RESER				0x0C


uint8_t ne_doip_testcase_debug(ne_doip_link_data_t *link_data)
{

    // char ip[INET6_ADDRSTRLEN] = { 0 };
    // ne_doip_os_get_ip(global_server_manager->server->config->external_ifname, ip, INET6_ADDRSTRLEN);
    
    // if (0 == strcmp(link_data->ip, ip)) {
    //     NE_DOIP_PRINT("This is an internal udp message, ignored !\n");
    //     return NE_DOIP_FALSE;
    // }

    if (link_data->data_size < 9) {
        return NE_DOIP_FALSE;
    }

    uint16_t payload_type = 0x0000;
    memcpy(&payload_type, link_data->data + 2, NE_DOIP_PAYLOAD_TYPE_LENGTH);
    if (payload_type != NE_DOIP_ST_PAYLOADTYPE_HEADER_NEGTIVE_ACK) {
        return NE_DOIP_FALSE;
    }

    uint8_t testcase_type = link_data->data[8];
    NE_DOIP_PRINT("ne_doip_testcase_debug case type is >>>>>>>>>>>> [%02X]\n", link_data->data[8]);
    ne_doip_connection_t *conn = (ne_doip_connection_t*)malloc(sizeof(ne_doip_connection_t));
    if (NULL == conn) {
        return NE_DOIP_FALSE;
    }

    memset(conn, 0, sizeof(ne_doip_connection_t));
    memcpy(conn->out.data, link_data->data, link_data->data_size);
    conn->out.data_size = link_data->data_size;
    conn->fd = link_data->fd;

    switch(testcase_type) {

        case NE_DPIP_TESTCASE_DEBUG_POWER_MODE_TRUE:
        {
            NE_DOIP_PRINT("ne_doip_testcase_debug case type is[NE_DPIP_TESTCASE_DEBUG_POWER_MODE_TRUE]\n");
            ne_doip_powermode_status_change(0x01);
            ne_doip_udp_send(conn, link_data->ip, NE_DOIP_UDP_DISCOVERY_PORT);
            break;
        }
        case NE_DPIP_TESTCASE_DEBUG_POWER_MODE_FALSE:
        {
            NE_DOIP_PRINT("ne_doip_testcase_debug case type is[NE_DPIP_TESTCASE_DEBUG_POWER_MODE_FALSE]\n");
            ne_doip_powermode_status_change(0x00);
            ne_doip_udp_send(conn, link_data->ip, NE_DOIP_UDP_DISCOVERY_PORT);
            break;
        }
        case NE_DPIP_TESTCASE_DEBUG_ACTIVATION_LINE_TRUE:
        {
            NE_DOIP_PRINT("ne_doip_testcase_debug case type is[NE_DPIP_TESTCASE_DEBUG_ACTIVATION_LINE_TRUE]\n");
            ne_doip_activation_line_switch_active();
            ne_doip_udp_send(conn, link_data->ip, NE_DOIP_UDP_DISCOVERY_PORT);
            break;
        }
        case NE_DPIP_TESTCASE_DEBUG_ACTIVATION_LINE_FALSE:
        {
            NE_DOIP_PRINT("ne_doip_testcase_debug case type is[NE_DPIP_TESTCASE_DEBUG_ACTIVATION_LINE_FALSE]\n");
            ne_doip_activation_line_switch_deactive();
            ne_doip_udp_send(conn, link_data->ip, NE_DOIP_UDP_DISCOVERY_PORT);
            break;
        }
        case NE_DPIP_TESTCASE_DEBUG_VEHICLE_ANNOUNCE:
        {
            NE_DOIP_PRINT("ne_doip_testcase_debug case type is[NE_DPIP_TESTCASE_DEBUG_VEHICLE_ANNOUNCE]\n");
            ne_doip_vehicle_announce(global_server_manager->server->config->external_ifname);
            break;
        }
        case NE_DPIP_TESTCASE_DEBUG_VEHICLE_ANNOUNCE_OTHER_PORTS:
        {
            NE_DOIP_PRINT("ne_doip_testcase_debug case type is[NE_DPIP_TESTCASE_DEBUG_VEHICLE_ANNOUNCE_OTHER_PORTS]\n");
            ne_doip_vehicle_announce(global_server_manager->server->config->external_ifname);
            break;
        }
        case NE_DPIP_TESTCASE_DEBUG_ROUTING_ACTIVATION_AUTH_TRUE:
        {
            NE_DOIP_PRINT("ne_doip_testcase_debug case type is[NE_DPIP_TESTCASE_DEBUG_ROUTING_ACTIVATION_AUTH_TRUE]\n");
            global_server_manager->server->config->authen_info = 0x12345678;
            ne_doip_udp_send(conn, link_data->ip, NE_DOIP_UDP_DISCOVERY_PORT);
            break;
        }
        case NE_DPIP_TESTCASE_DEBUG_ROUTING_ACTIVATION_AUTH_FALSE:
        {
            NE_DOIP_PRINT("ne_doip_testcase_debug case type is[NE_DPIP_TESTCASE_DEBUG_ROUTING_ACTIVATION_AUTH_FALSE]\n");
            global_server_manager->server->config->authen_info = 0;
            ne_doip_udp_send(conn, link_data->ip, NE_DOIP_UDP_DISCOVERY_PORT);
            break;
        }
        case NE_DPIP_TESTCASE_DEBUG_ENTITY_TYPE_NODE:
        {
            NE_DOIP_PRINT("ne_doip_testcase_debug case type is[NE_DPIP_TESTCASE_DEBUG_ENTITY_TYPE_NODE]\n");
            global_server_manager->server->config->entity_type = NE_DOIP_ENTITY_TYPE_NODE;
            ne_doip_udp_send(conn, link_data->ip, NE_DOIP_UDP_DISCOVERY_PORT);
            break;
        }
        case NE_DPIP_TESTCASE_DEBUG_ENTITY_TYPE_GATEWAY:
        {
            NE_DOIP_PRINT("ne_doip_testcase_debug case type is[NE_DPIP_TESTCASE_DEBUG_ENTITY_TYPE_GATEWAY]\n");
            global_server_manager->server->config->entity_type = NE_DOIP_ENTITY_TYPE_GATEWAY;
            ne_doip_udp_send(conn, link_data->ip, NE_DOIP_UDP_DISCOVERY_PORT);
            break;
        }
        case NE_DPIP_TESTCASE_DEBUG_CHANGE_MCTS:
        {
            NE_DOIP_PRINT("ne_doip_testcase_debug case type is[NE_DPIP_TESTCASE_DEBUG_CHANGE_MCTS]\n");
            global_server_manager->server->config->mcts = 1;
            ne_doip_udp_send(conn, link_data->ip, NE_DOIP_UDP_DISCOVERY_PORT);
            break;
        }
        case NE_DPIP_TESTCASE_DEBUG_CHANGE_MCTS_RESER:
        {
            NE_DOIP_PRINT("ne_doip_testcase_debug case type is[NE_DPIP_TESTCASE_DEBUG_CHANGE_MCTS_RESER]\n");
            global_server_manager->server->config->mcts = 255;
            ne_doip_udp_send(conn, link_data->ip, NE_DOIP_UDP_DISCOVERY_PORT);
            break;
        }
        default:
            NE_DOIP_PRINT("unknown test case type!\n");
        break;

    }

    free(conn);
    return NE_DOIP_TRUE;

}

