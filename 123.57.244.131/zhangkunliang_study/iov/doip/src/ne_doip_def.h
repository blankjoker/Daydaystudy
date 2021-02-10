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
 * @file ne_doip_def.h
 * @brief Definition file
 */

#ifndef NE_DOIP_DEF_H
#define NE_DOIP_DEF_H

#include <sys/un.h>
#include <netinet/in.h>
#include <stdint.h>

#include "ne_doip_comm_def.h"
#include "ne_doip_event_loop.h"
#include "ne_doip_connection.h"
#include "ne_doip_thread.h"
#include "ne_doip_util.h"

// #define NE_DOIP_DEBUG

#define NE_DOIP_TRUE 1
#define NE_DOIP_FALSE 0

#define NE_DOIP_DEFAULT_VERSION 0xFFU

#define NE_DOIP_TCP_DATA_PORT       13400
#define NE_DOIP_UDP_DISCOVERY_PORT  13400
#define UDP_TEST_EQUIPMENT_REQUEST_MIN_PORT 49152
#define UDP_TEST_EQUIPMENT_REQUEST_MAX_PORT 65535
#define NE_DOIP_UDP_BROADCAST_IP    "255.255.255.255"
#define NE_DOIP_UDP6_BROADCAST_IP   "FF02::1"

#define NE_DOIP_A_DOIP_ANNOUNCE_WAIT_MAX   500U      /* 500 ms */
#define NE_DOIP_A_DOIP_ANNOUNCE_INTERVAL   500U      /* 500 ms */
#define NE_DOIP_T_TCP_INITIAL_INACTIVITY   2000U     /* 2 s    */
#define NE_DOIP_T_TCP_GENE_INACTIVITY      300000U   /* 5 min  */
#define NE_DOIP_T_TCP_ALIVE_CHECK          500U      /* 500 ms */

#define NE_DOIP_IN_PAYLOADTYPE_NODE_RGIST                0x01U
#define NE_DOIP_IN_PAYLOADTYPE_DIAG_REQUEST              0x02U
#define NE_DOIP_IN_PAYLOADTYPE_DIAG_CONFIRM              0x03U
#define NE_DOIP_IN_PAYLOADTYPE_DIAG_INDICATION           0x04U
#define NE_DOIP_IN_PAYLOADTYPE_REGIST_USER_CONF          0x05U
#define NE_DOIP_IN_PAYLOADTYPE_USER_CONF_RESULT          0x06U
#define NE_DOIP_IN_PAYLOADTYPE_EQUIP_LINK_DISCONNECTED   0x07U

#define NE_DOIP_IN_EQUIP_RGIST                0xF0U
#define NE_DOIP_IN_EQUIP_HEADER_NACK          0xF1U
#define NE_DOIP_IN_EQUIP_ANN_IDEN_RES         0xF2U
#define NE_DOIP_IN_EQUIP_IDENTITY_REQ         0xF3U
#define NE_DOIP_IN_EQUIP_IDENTITY_REQ_EID     0xF4U
#define NE_DOIP_IN_EQUIP_IDENTITY_REQ_VIN     0xF5U
#define NE_DOIP_IN_EQUIP_ROUTING_ACTIVE       0xF6U
#define NE_DOIP_IN_EQUIP_ALIVE_CHECK          0xF7U
#define NE_DOIP_IN_EQUIP_ENTITY_STATUS        0xF8U
#define NE_DOIP_IN_EQUIP_POWER_MODE           0xF9U
#define NE_DOIP_IN_EQUIP_DIAGNOSTIC_PACK      0xFAU
#define NE_DOIP_IN_EQUIP_DIAGNOSTIC_NACK      0xFBU
#define NE_DOIP_IN_EQUIP_DIAGNOSTIC           0xFCU

#define NE_DOIP_OUT_VIN_GID_SYNC              0xABABU
#define NE_DOIP_OUT_ACTIVATION_DEACTIVE       0xBCBCU

#define NE_DOIP_ST_PAYLOADTYPE_VEHICLE_INDENTIFY         0x0001U
#define NE_DOIP_ST_PAYLOADTYPE_VEHICLE_INDENTIFY_EID     0x0002U
#define NE_DOIP_ST_PAYLOADTYPE_VEHICLE_INDENTIFY_VIN     0x0003U
#define NE_DOIP_ST_PAYLOADTYPE_ROUTING_ACTIVE_REQ        0x0005U
#define NE_DOIP_ST_PAYLOADTYPE_ALIVE_CHECK_RES           0x0008U
#define NE_DOIP_ST_PAYLOADTYPE_ENTINTY_STATUS_REQ        0x4001U
#define NE_DOIP_ST_PAYLOADTYPE_POWER_MODE_REQ            0x4003U
#define NE_DOIP_ST_PAYLOADTYPE_DIAGNOSTIC_REQ            0x8001U
#define NE_DOIP_ST_PAYLOADTYPE_HEADER_NEGTIVE_ACK        0x0000U
#define NE_DOIP_ST_PAYLOADTYPE_ANNOUNCE_OR_IDENTIFYRES   0x0004U
#define NE_DOIP_ST_PAYLOADTYPE_ROUTING_ACTIVE_RES        0x0006U
#define NE_DOIP_ST_PAYLOADTYPE_ALIVE_CHECK_REQ           0x0007U
#define NE_DOIP_ST_PAYLOADTYPE_ENTINTY_STATUS_RES        0x4002U
#define NE_DOIP_ST_PAYLOADTYPE_POWER_MODE_RES            0x4004U
#define NE_DOIP_ST_PAYLOADTYPE_DIAG_POSITIVE_ACK         0x8002U
#define NE_DOIP_ST_PAYLOADTYPE_DIAG_NEGATIVE_ACK         0x8003U

#define NE_DOIP_WWH_OBD_FUNCTIANAL_ADDRESS    0xE000U
#define NE_DOIP_OEM_LOWER_FUNCTIANAL_ADDRESS  0xE400U
#define NE_DOIP_OEM_UPPER_FUNCTIANAL_ADDRESS  0xEFFFU

#define NE_DOIP_ALL_ECU_NUM           50

#define NE_DOIP_IN_COMMAND_LENGTH      1
#define NE_DOIP_IN_DATA_LENGTH         4
#define NE_DOIP_ST_COMMAND_LENGTH      2
#define NE_DOIP_LOGICAL_ADDRESS_LENGTH 2
#define NE_DOIP_INSTANCE_TYPE_LENGTH   1
#define NE_DOIP_CONF_RESULT_LENGTH     1
#define NE_DOIP_TA_TYPE_LENGTH         1
#define NE_DOIP_BLANK_2_LENGTH         2
#define NE_DOIP_FURTHER_ACTION_LENGTH  1
#define NE_DOIP_VIN_GID_SYNC_LENGTH    1
#define NE_DOIP_RA_RES_CODE_LENGTH     1
#define NE_DOIP_NODE_TYPE_LENGTH       1
#define NE_DOIP_MCTS_LENGTH            1
#define NE_DOIP_NCTS_LENGTH            1
#define NE_DOIP_MDS_LENGTH             4
#define NE_DOIP_POWERMODE_LENGTH       1
#define NE_DOIP_ACK_CODE_LENGTH        1
#define NE_DOIP_NACK_CODE_LENGTH       1
#define NE_DOIP_IFNAME_SIZE            10
#define NE_DOIP_ANNOUNCE_OR_IDENTITYRES_MAND_LENGTH  NE_DOIP_EID_SIZE + \
                                                     NE_DOIP_GID_SIZE + \
                                                     NE_DOIP_VIN_SIZE + \
                                                     NE_DOIP_LOGICAL_ADDRESS_LENGTH + \
                                                     NE_DOIP_FURTHER_ACTION_LENGTH
#define NE_DOIP_ANNOUNCE_OR_IDENTITYRES_ALL_LENGTH   NE_DOIP_EID_SIZE + \
                                                     NE_DOIP_GID_SIZE + \
                                                     NE_DOIP_VIN_SIZE + \
                                                     NE_DOIP_LOGICAL_ADDRESS_LENGTH + \
                                                     NE_DOIP_FURTHER_ACTION_LENGTH + \
                                                     NE_DOIP_VIN_GID_SYNC_LENGTH

enum NE_DOIP_DT_ERROR_CODE
{
    NE_DOIP_NO_ERROR                               = 0x00000000,
    // system error
    NE_DOIP_THREAD_POOL_NEW_FAILED                 = 0x00000001,
    NE_DOIP_THREAD_POOL_FREE_FAILED                = 0x00000002,
    NE_DOIP_THREAD_POOL_PUSH_FAILED                = 0x00000003,
    NE_DOIP_TIMER_MANAGER_CREATE_FAILED            = 0x00000004,
    NE_DOIP_TIMER_START_FAILED                     = 0x00000005,
    NE_DOIP_TIMER_STOP_FAILED                      = 0x00000006,
    NE_DOIP_TIMER_RESTART_FAILED                   = 0x00000007,
    NE_DOIP_SYNC_CREATE_FAILED                     = 0x00000008,
    // other error
    NE_DOIP_CONFIG_INIT_FAILD                      = 0x00000001,
    NE_DOIP_CONFIG_NO_FILE                         = 0x00000002,
    NE_DOIP_CONFIG_FORMAT_INVALID                  = 0x00000003,
    NE_DOIP_CONFIG_CONTENT_INVALID                 = 0x00000004,
    NE_DOIP_NODE_IPC_TABLE_NOT_FOUND               = 0x00000005,
    NE_DOIP_NODE_TCP_TABLE_NOT_FOUND               = 0x00000006,
    NE_DOIP_NODE_UDP_TABLE_NOT_FOUND               = 0x00000007,
    NE_DOIP_EQUIP_IPC_TABLE_NOT_FOUND              = 0x00000008,
    NE_DOIP_EQUIP_TCP_TABLE_NOT_FOUND              = 0x00000009,
    NE_DOIP_EQUIP_UDP_TABLE_NOT_FOUND              = 0x0000000A,
    NE_DOIP_DIAG_TIMEOUT_TABLE_NOT_FOUND           = 0x0000000B,
    NE_DOIP_ROUTING_TABLE_NOT_FOUND                = 0x0000000C,
    NE_DOIP_INVALID_PAYLOAD_LENGTH                 = 0x0000000D,
    NE_DOIP_GET_SYNC_FAILED                        = 0x0000000E,
};

enum NE_DOIP_DT_SOCKET_FUNCTION
{
    NE_DOIP_DT_EVENT_HANGUP                        = 0x0001,
    NE_DOIP_DT_EVENT_ERROR                         = 0x0002,

    NE_DOIP_SOCKET_CREATE                          = 0x0003,
    NE_DOIP_SOCKET_WRITE                           = 0x0004,
    NE_DOIP_SOCKET_READ                            = 0x0005,
    NE_DOIP_SOCKET_CONNECT                         = 0x0006,
    NE_DOIP_SOCKET_ACCEPT                          = 0x0007,
    NE_DOIP_SOCKET_BIND                            = 0x0008,
    NE_DOIP_SOCKET_LISTEN                          = 0x0009,
    NE_DOIP_SOCKET_SETOPT                          = 0x000A,
    NE_DOIP_SOCKET_READ_EOF                        = 0x000B,
    NE_DOIP_SOCKET_RECVFROM                        = 0x000C,
    NE_DOIP_SOCKET_SENDTO                          = 0x000D,
    NE_DOIP_SELECT_CREATE                          = 0x000E,

    NE_DOIP_NE_DOIP_SOURCE_CREATE                  = 0x000F,
    NE_DOIP_NE_DOIP_SOURCE_ADD                     = 0x0010,
    NE_DOIP_NE_DOIP_SOURCE_REMOVE                  = 0x0011,
};

enum NE_DOIP_DT_DOIP_EQUIP_INTERFACE
{
    NE_DOIP_EQUIP_CREATE                           = 0X0001,
    NE_DOIP_EQUIP_DESTROY                          = 0X0002,
    NE_DOIP_EQUIP_IDENTITY                         = 0X0003,
    NE_DOIP_EQUIP_ROUTING_ACTIVE                   = 0X0004,
    NE_DOIP_EQUIP_ALIVE_CHECK_RES                  = 0X0005,
    NE_DOIP_EQUIP_ENTITY_STATUS_REQ                = 0X0006,
    NE_DOIP_EQUIP_POWER_MODE_REQ                   = 0X0007,
    NE_DOIP_EQUIP_DIAGNOSTIC                       = 0X0008,
    NE_DOIP_REGIST_DOIP_EQUIP_DTLOGFUNC_CALLBACK   = 0X0009,
};

enum NE_DOIP_DT_DOIP_NODE_INTERFACE
{
    NE_DOIP_NODE_CREATE                            = 0X0001,
    NE_DOIP_NODE_DESTROY                           = 0X0002,
    NE_DOIP_NODE_DIAG_DATA_REQUEST                 = 0X0003,
    NE_DOIP_NODE_SEND_USER_CONF_RESULT             = 0X0004,
    NE_DOIP_REGIST_DOIP_NODE_DTLOGFUNC_CALLBACK    = 0X0005,
};

enum NE_DOIP_DT_DOIP_SERVER_INTERFACE
{
    NE_DOIP_SERVER_INIT                            = 0x0001,
    NE_DOIP_SERVER_DEINIT                          = 0x0002,
    NE_DOIP_SET_VIN_INFO                           = 0x0003,
    NE_DOIP_SET_EID_INFO                           = 0x0004,
    NE_DOIP_SET_GID_INFO                           = 0x0005,
    NE_DOIP_ACTIVATION_LINE_SWITCH_ACTIVE          = 0x0006,
    NE_DOIP_ACTIVATION_LINE_SWITCH_DEACTIVE        = 0x0007,
    NE_DOIP_REQUEST_IP_ADDR_ASSIGNMENT             = 0x0008,
    NE_DOIP_RELEASE_IP_ADDR_ASSIGNMENT             = 0x0009,
    NE_DOIP_POWERMODE_STATUS_CHANGE                = 0x000A,
    NE_DOIP_REGIST_LOGFUNC_CALLBACK                = 0x000B,
    NE_DOIP_REGIST_DTLOGFUNC_CALLBACK              = 0x000C,
};


enum NE_DOIP_NET_TYPE
{
    NE_DOIP_NET_TYPE_IPV4 = 0x00,
    NE_DOIP_NET_TYPE_IPV6 = 0x01
};

enum NE_DOIP_EVENT_INFO
{
    NE_DOIP_EVENT_READABLE = 0x01,
    NE_DOIP_EVENT_WRITABLE = 0x02,
    NE_DOIP_EVENT_HANGUP   = 0x04,
    NE_DOIP_EVENT_ERROR    = 0x08
};

enum NE_DOIP_SOCKET_TYPE
{
    NE_DOIP_SOCKET_TYPE_UDP       = 0x00,
    NE_DOIP_SOCKET_TYPE_IPC       = 0x01,
    NE_DOIP_SOCKET_TYPE_TCP_IN    = 0x02,
    NE_DOIP_SOCKET_TYPE_TCP_OUT   = 0x03,
    NE_DOIP_SOCKET_TYPE_UDP_UNI   = 0x04,
    NE_DOIP_SOCKET_TYPE_UDP_MOUTI = 0x05,
    NE_DOIP_SOCKET_TYPE_SELECT    = 0x06,
    NE_DOIP_SOCKET_TYPE_UNKNOWN   = 0xFF,
};

typedef enum NE_DOIP_CONNECT_STATE
{
    NE_DOIP_CONNECT_STATE_LISTEN                      = 0x00,
    NE_DOIP_CONNECT_STATE_INITIALIZED                 = 0x01,
    NE_DOIP_CONNECT_STATE_REGISTERED_PENDING_FOR_AUTH = 0x02,
    NE_DOIP_CONNECT_STATE_REGISTERED_PENDING_FOR_CONF = 0x03,
    NE_DOIP_CONNECT_STATE_REGISTERED_ROUTING_ACTIVE   = 0x04,
    NE_DOIP_CONNECT_STATE_FINALIZE                    = 0x05
}ne_doip_connect_state_t;

typedef enum NE_DOIP_ANNOUNCE_STATE
{
    NE_DOIP_IP_NOT_CONFIGURED_NOT_ANNOUNCED    = 0x00,
    NE_DOIP_IP_CONFIGURED_NOT_ANNOUNCED        = 0x01,
    NE_DOIP_IP_CONFIGURED_ANNOUNCED            = 0x02
}ne_doip_announce_state_t;

typedef enum NE_DOIP_ENTITY_TYPE
{
    NE_DOIP_ENTITY_TYPE_UNKNOWN         = 0x00,
    NE_DOIP_ENTITY_TYPE_EDGE_GATEWAY    = 0x01,
    NE_DOIP_ENTITY_TYPE_GATEWAY         = 0x02,
    NE_DOIP_ENTITY_TYPE_NODE            = 0x03
}ne_doip_entity_type_t;

typedef enum NE_DOIP_IF_TYPE
{
    NE_DOIP_IF_TYPE_INTERNAL    = 0x00,
    NE_DOIP_IF_TYPE_EXTERNAL    = 0x01
}ne_doip_if_type_t;

/* doip node information */
typedef struct ne_doip_node
{
    ne_doip_list_t base;
    int32_t fd;
    uint16_t logical_source_address;
    uint16_t logical_target_address;
    ne_doip_instence_type_t doip_instence_type;
    ne_doip_ta_type_t ta_type;
    ne_doip_thread_t *thread;
    ne_doip_connection_t *connection;
    ne_doip_diag_indication_callback indication_callback;
    ne_doip_diag_confirm_callback confirm_callback;
    ne_doip_user_conf_callback user_conf_callback;
    uint32_t diag_data_total_length;
    uint32_t diag_data_current_pos;
    char* diag_data_cach_buffer;
}ne_doip_node_t;

/* doip node list */
typedef struct ne_doip_node_list
{
    ne_doip_sync_t *node_list_sync;
    ne_doip_list_t *node_list;
}ne_doip_node_list_t;

/* internal test equipment information */
typedef struct ne_doip_test_equip
{
    int32_t fd;
    uint16_t logical_source_address;
    ne_doip_thread_t *thread;
    ne_doip_connection_t *connection;
    ne_doip_vehicle_identity_callback vehicle_identity_callback;
    ne_doip_routing_active_callback routing_active_callback;
    ne_doip_entity_status_callback entity_status_callback;
    ne_doip_power_mode_callback power_mode_callback;
    ne_doip_diag_pack_callback daig_pack_callback;
    ne_doip_diag_nack_callback daig_nack_callback;
    ne_doip_diagnostic_callback diagnostic_callback;
    ne_doip_sync_t *diag_list_sync;
    ne_doip_list_t *diag_list;
}ne_doip_test_equip_t;

/* doip equip diag req list */
typedef struct ne_doip_equip_diag_req
{
    ne_doip_list_t base;
    uint16_t logical_target_address;
    ne_doip_thread_t *thread;
    ne_doip_connection_t *connection;
}ne_doip_equip_diag_req_t;

/* Socket for interprocess communication */
typedef struct ne_doip_ipc_socket
{
    int32_t fd;
    struct sockaddr_un addr;
    ne_doip_event_source_t *source;
}ne_doip_ipc_socket_t;

/* Socket for ipv4 network communication */
typedef struct ne_doip_ipv4_socket
{
    int32_t fd;
    int32_t type;
    struct sockaddr_in addr;
    ne_doip_event_source_t *source;
}ne_doip_ipv4_socket_t;

/* Socket for ipv6 network communication */
typedef struct ne_doip_ipv6_socket
{
    int32_t fd;
    int32_t type;
    struct sockaddr_in6 addr;
    ne_doip_event_source_t *source;
}ne_doip_ipv6_socket_t;

/* IF configuration table, support priority */
typedef struct ne_doip_net_source
{
    ne_doip_list_t base;
    int32_t priority;
    char source_type[8];
    char ifname[8];
    ne_doip_if_type_t if_type;
    char prefix_if[8];
    ne_doip_announce_state_t announce_state;
    uint8_t announce_count;
    int32_t announce_wait_timeid;
    int32_t announce_interval_timeid;
}ne_doip_net_source_t;

/* Diagnostic routing table */
typedef struct ne_doip_routing_table
{
    ne_doip_list_t base;
    int32_t fd;
    char entity_type[16];
    uint16_t entity_logical_address;
    char* ip;
}ne_doip_routing_table_t;

/* Functional addressing grouping table */
typedef struct ne_doip_func_group
{
    ne_doip_list_t base;
    uint16_t group_address;
    uint16_t logical_address_array[NE_DOIP_ALL_ECU_NUM];
    uint8_t group_member_num;
}ne_doip_func_group_t;

/* doip config information */
typedef struct ne_doip_config
{
    char vin[NE_DOIP_VIN_SIZE];
    char eid[NE_DOIP_EID_SIZE];
    char gid[NE_DOIP_GID_SIZE];
    char internal_ifname[NE_DOIP_IFNAME_SIZE];
    char external_ifname[NE_DOIP_IFNAME_SIZE];
    ne_doip_entity_type_t entity_type;
    uint8_t net_type;
    uint8_t protocol_version;
    uint8_t mcts;
    uint8_t activation_line_flag;
    uint8_t egw_control;
    uint8_t need_vin_gid_sync;
    uint16_t tester_sa;
    uint16_t functianal_la;
    uint32_t mds;
    uint32_t authen_info;
    int32_t announce_interval_time;
    int32_t general_inactivity_time;
    int32_t initial_inactivity_time;
    int32_t alive_check_time;
    ne_doip_list_t *routing_list;
    ne_doip_list_t *func_group_list;
    ne_doip_list_t *net_source_list;
}ne_doip_config_t;

/* doip client information */
typedef struct ne_doip_client
{
    ne_doip_list_t base;
    struct ne_doip_server *server;
    ne_doip_connection_t *connection;
    ne_doip_event_source_t *source;
    uint8_t client_type;
}ne_doip_client_t;

/* doip server information */
typedef struct ne_doip_server
{
    int32_t ipc_run;
    int32_t net_run;
    ne_doip_select_t *sel_ipc;
    ne_doip_select_t *sel_net;
    ne_doip_sync_t *ipc_list_sync;
    ne_doip_sync_t *net_list_sync;
    ne_doip_sync_t *test_list_sync;
    ne_doip_sync_t *net_list_free_sync;
    ne_doip_config_t *config;
    // ne_doip_client_t *udp_client_internal;
    ne_doip_client_t *udp_client_external;
    ne_doip_client_t *udp6_client;
    ne_doip_list_t *ipc_client_list;
    ne_doip_list_t *net_client_list;
    ne_doip_list_t *test_client_list;
    ne_doip_list_t *client_list_free;
    ne_doip_thread_t* epoll_ipc_thread;
    ne_doip_thread_t* epoll_net_thread;
    ne_doip_ipc_socket_t *ipc_socket;
    ne_doip_ipv4_socket_t *ipv4_tcp_socket;
    ne_doip_ipv4_socket_t *ipv4_udp_socket_discovery;
    // ne_doip_ipv4_socket_t *ipv4_udp_socket_internal;
    ne_doip_ipv4_socket_t *ipv4_udp_socket_external;
    ne_doip_ipv6_socket_t *ipv6_tcp_socket;
    ne_doip_ipv6_socket_t *ipv6_udp_socket;
    uint8_t power_mode;
    uint8_t vin_gid_sync_flag;
    int32_t udp_response_port;
    ne_doip_routing_activation_res_callback route_active_res_func;
    ne_doip_all_tcp_disconnect_res_callback tcp_dis_res_func;
    uint8_t routing_active_res_count;
}ne_doip_server_t;

#endif /* NE_DOIP_DEF_H */
/* EOF */
