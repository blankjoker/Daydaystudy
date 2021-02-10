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
 * @file ne_doip_test_util.h
 * @brief tool module
 */

#ifndef NE_DOIP_UTIL_H
#define NE_DOIP_UTIL_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "ne_doip_comm_def.h"

/* GCC visibility */
#if defined(__GNUC__) && __GNUC__ >= 4
#define DOIP_EXPORT __attribute__ ((visibility("default")))
#else
#define DOIP_EXPORT
#endif

#define ARRAY_LENGTH(a) (sizeof (a) / sizeof (a)[0])

#ifdef __GNUC__
#define  ne_doip_container_of(ptr, sample, member)                \
    (__typeof__(sample))((char *)(ptr)    -            \
         ((char *)&(sample)->member - (char *)(sample)))
#else
#define  ne_doip_container_of(ptr, sample, member)                \
    (void *)((char *)(ptr)    -                        \
         ((char *)&(sample)->member - (char *)(sample)))
#endif

#define ne_doip_list_for_each(pos, head, member)                \
    for (pos = 0, pos =  ne_doip_container_of((head)->next, pos, member);    \
         &pos->member != (head);                    \
         pos =  ne_doip_container_of(pos->member.next, pos, member))

#define ne_doip_list_for_each_safe(pos, tmp, head, member)            \
    for (pos = 0, tmp = 0,                         \
         pos =  ne_doip_container_of((head)->next, pos, member),        \
         tmp =  ne_doip_container_of((pos)->member.next, tmp, member);    \
         &pos->member != (head);                    \
         pos = tmp,                            \
         tmp =  ne_doip_container_of(pos->member.next, tmp, member))

#define ne_doip_list_for_each_reverse(pos, head, member)            \
    for (pos = 0, pos =  ne_doip_container_of((head)->prev, pos, member);    \
         &pos->member != (head);                    \
         pos =  ne_doip_container_of(pos->member.prev, pos, member))

#define ne_doip_list_for_each_reverse_safe(pos, tmp, head, member)        \
    for (pos = 0, tmp = 0,                         \
         pos =  ne_doip_container_of((head)->prev, pos, member),    \
         tmp =  ne_doip_container_of((pos)->member.prev, tmp, member);    \
         &pos->member != (head);                    \
         pos = tmp,                            \
         tmp =  ne_doip_container_of(pos->member.prev, tmp, member))


#define NE_DOIP_PRINT(...) ((void)ne_doip_log_output(__FUNCTION__, __FILE__, __LINE__, __VA_ARGS__))
#define NE_DOIP_PRINT_LARGE (ne_doip_printf_time(__LINE__), printf)

#define NE_DOIP_DT_FORMAT_STEP_EQUIP(...) (ne_doip_diag_dtlog(NE_DOIP_DT_DOMAIN_TYPE_UDS_CLIENT, NE_DOIP_DT_ERROR_TYPE_STEP, __VA_ARGS__))
#define NE_DOIP_DT_FORMAT_STEP_NODE(...) (ne_doip_diag_dtlog(NE_DOIP_DT_DOMAIN_TYPE_UDS_SERVER, NE_DOIP_DT_ERROR_TYPE_STEP, __VA_ARGS__))
#define NE_DOIP_DT_FORMAT_STEP_SERVER(...) (ne_doip_diag_dtlog(NE_DOIP_DT_DOMAIN_TYPE_DOIP_SERVER, NE_DOIP_DT_ERROR_TYPE_STEP, __VA_ARGS__))

#define NE_DOIP_DT_FORMAT_PROTOCOL_EQUIP(...) (ne_doip_diag_dtlog(NE_DOIP_DT_DOMAIN_TYPE_UDS_CLIENT, NE_DOIP_DT_ERROR_TYPE_PROTOCOL, __VA_ARGS__))
#define NE_DOIP_DT_FORMAT_PROTOCOL_NODE(...) (ne_doip_diag_dtlog(NE_DOIP_DT_DOMAIN_TYPE_UDS_SERVER, NE_DOIP_DT_ERROR_TYPE_PROTOCOL, __VA_ARGS__))
#define NE_DOIP_DT_FORMAT_PROTOCOL_SERVER(...) (ne_doip_diag_dtlog(NE_DOIP_DT_DOMAIN_TYPE_DOIP_SERVER, NE_DOIP_DT_ERROR_TYPE_PROTOCOL, __VA_ARGS__))

#define NE_DOIP_DT_FORMAT_INTERFACE_EQUIP(...) (ne_doip_interface_dtlog(NE_DOIP_DT_DOMAIN_TYPE_UDS_CLIENT, NE_DOIP_DT_ERROR_TYPE_INTERFACE, __VA_ARGS__))
#define NE_DOIP_DT_FORMAT_INTERFACE_NODE(...) (ne_doip_interface_dtlog(NE_DOIP_DT_DOMAIN_TYPE_UDS_SERVER, NE_DOIP_DT_ERROR_TYPE_INTERFACE, __VA_ARGS__))
#define NE_DOIP_DT_FORMAT_INTERFACE_SERVER(...) (ne_doip_interface_dtlog(NE_DOIP_DT_DOMAIN_TYPE_DOIP_SERVER, NE_DOIP_DT_ERROR_TYPE_INTERFACE, __VA_ARGS__))

#define NE_DOIP_DT_FORMAT_SYSTEM_EQUIP(...) (ne_doip_comm_dtlog(NE_DOIP_DT_DOMAIN_TYPE_UDS_CLIENT, NE_DOIP_DT_ERROR_TYPE_SYSTEM, __VA_ARGS__))
#define NE_DOIP_DT_FORMAT_SYSTEM_NODE(...) (ne_doip_comm_dtlog(NE_DOIP_DT_DOMAIN_TYPE_UDS_SERVER, NE_DOIP_DT_ERROR_TYPE_SYSTEM, __VA_ARGS__))
#define NE_DOIP_DT_FORMAT_SYSTEM_SERVER(...) (ne_doip_comm_dtlog(NE_DOIP_DT_DOMAIN_TYPE_DOIP_SERVER, NE_DOIP_DT_ERROR_TYPE_SYSTEM, __VA_ARGS__))

#define NE_DOIP_DT_FORMAT_SOCKET_EQUIP(...) (ne_doip_socket_dtlog(NE_DOIP_DT_DOMAIN_TYPE_UDS_CLIENT, NE_DOIP_DT_ERROR_TYPE_SOCKET, __VA_ARGS__))
#define NE_DOIP_DT_FORMAT_SOCKET_NODE(...) (ne_doip_socket_dtlog(NE_DOIP_DT_DOMAIN_TYPE_UDS_SERVER, NE_DOIP_DT_ERROR_TYPE_SOCKET, __VA_ARGS__))
#define NE_DOIP_DT_FORMAT_SOCKET_SERVER(...) (ne_doip_socket_dtlog(NE_DOIP_DT_DOMAIN_TYPE_DOIP_SERVER, NE_DOIP_DT_ERROR_TYPE_SOCKET, __VA_ARGS__))

#define NE_DOIP_DT_FORMAT_OTHER_EQUIP(...) (ne_doip_comm_dtlog(NE_DOIP_DT_DOMAIN_TYPE_UDS_CLIENT, NE_DOIP_DT_ERROR_TYPE_OTHER, __VA_ARGS__))
#define NE_DOIP_DT_FORMAT_OTHER_NODE(...) (ne_doip_comm_dtlog(NE_DOIP_DT_DOMAIN_TYPE_UDS_SERVER, NE_DOIP_DT_ERROR_TYPE_OTHER, __VA_ARGS__))
#define NE_DOIP_DT_FORMAT_OTHER_SERVER(...) (ne_doip_comm_dtlog(NE_DOIP_DT_DOMAIN_TYPE_DOIP_SERVER, NE_DOIP_DT_ERROR_TYPE_OTHER, __VA_ARGS__))

void ne_doip_dt_log_write(char* buf);

struct ne_doip_list
{
    struct ne_doip_list *prev;
    struct ne_doip_list *next;
};

typedef struct ne_doip_list ne_doip_list_t;

void ne_doip_list_init(ne_doip_list_t *list);
void ne_doip_list_insert(ne_doip_list_t *list, ne_doip_list_t *elm);
void ne_doip_list_remove(ne_doip_list_t *elm);
int32_t ne_doip_list_length(const ne_doip_list_t *list);
int32_t ne_doip_list_empty(const ne_doip_list_t *list);
void ne_doip_list_insert_list(ne_doip_list_t *list, ne_doip_list_t *other);

int32_t ne_doip_subtimespec(struct timespec *time1, struct timespec *time2);
void ne_doip_get_timespec(struct timespec *time, int32_t msec);
void ne_doip_set_timespec(struct timespec *time, int32_t msec);
uint32_t ne_doip_get_tick_cnt(void);
uint16_t ne_doip_bswap_16(uint16_t x);
uint32_t ne_doip_bswap_32(uint32_t x);
void ne_doip_convert_mac(char *str_out, const char *str_in);

void ne_doip_log_output(const char* func_name, char* file_name, int32_t line_num, const char* fmt, ...);
void ne_doip_printf_time(int32_t line);
void ne_doip_set_logfunc_callback(ne_doip_logfunc_callback logfunc);
void ne_doip_set_doip_server_dtlogfunc_callback(ne_doip_dtlogfunc_callback server_dtlogfunc);
void ne_doip_set_doip_equip_dtlogfunc_callback(ne_doip_dtlogfunc_callback equip_dtlogfunc);
void ne_doip_set_doip_node_dtlogfunc_callback(ne_doip_dtlogfunc_callback node_dtlogfunc);

enum NE_DOIP_DT_DOMAIN_TYPE
{
    NE_DOIP_DT_DOMAIN_TYPE_UDS_CLIENT   = 0x01,
    NE_DOIP_DT_DOMAIN_TYPE_UDS_SERVER   = 0x02,
    NE_DOIP_DT_DOMAIN_TYPE_DOIP_SERVER  = 0x03
};

enum NE_DOIP_DT_ERROR_TYPE
{
    NE_DOIP_DT_ERROR_TYPE_STEP          = 0x00,
    NE_DOIP_DT_ERROR_TYPE_PROTOCOL      = 0x01,
    NE_DOIP_DT_ERROR_TYPE_INTERFACE     = 0x02,
    NE_DOIP_DT_ERROR_TYPE_SYSTEM        = 0x03,
    NE_DOIP_DT_ERROR_TYPE_SOCKET        = 0X04,
    NE_DOIP_DT_ERROR_TYPE_OTHER         = 0x05
};

char* ne_doip_comm_dtlog(uint8_t domain_type, uint8_t error_type, uint32_t error_code);
char* ne_doip_socket_dtlog(uint8_t domain_type, uint8_t error_type, uint32_t error_code, uint16_t soket_type, uint16_t soket_func);
char* ne_doip_diag_dtlog(uint8_t domain_type, uint8_t error_type, uint32_t error_code, uint16_t payload_type,
                         uint32_t payload_length, uint16_t source_address, uint16_t target_address);
char* ne_doip_interface_dtlog(uint8_t domain_type, uint8_t error_type, uint32_t error_code, uint16_t function);

#ifdef  __cplusplus
}
#endif

#endif /* NE_DOIP_UTIL_H */
/* EOF */
