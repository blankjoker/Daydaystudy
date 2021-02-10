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

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdio.h>
#include "ne_doip_util.h"

ne_doip_logfunc_callback g_logfunc = NULL;
ne_doip_dtlogfunc_callback g_equip_dtlogfunc = NULL;
ne_doip_dtlogfunc_callback g_server_dtlogfunc = NULL;
ne_doip_dtlogfunc_callback g_node_dtlogfunc = NULL;

DOIP_EXPORT void
ne_doip_list_init(ne_doip_list_t *list)
{
    list->prev = list;
    list->next = list;
}

DOIP_EXPORT void
ne_doip_list_insert(ne_doip_list_t *list, ne_doip_list_t *elm)
{
    elm->prev = list;
    elm->next = list->next;
    list->next = elm;
    elm->next->prev = elm;
}

DOIP_EXPORT void
ne_doip_list_remove(ne_doip_list_t *elm)
{
    elm->prev->next = elm->next;
    elm->next->prev = elm->prev;
    elm->next = NULL;
    elm->prev = NULL;
}

DOIP_EXPORT int32_t
ne_doip_list_length(const ne_doip_list_t *list)
{
    ne_doip_list_t *e = NULL;
    int32_t count;

    count = 0;
    e = list->next;
    while (e != list) {
        e = e->next;
        count++;
    }

    return count;
}

DOIP_EXPORT int32_t
ne_doip_list_empty(const ne_doip_list_t *list)
{
    return list->next == list;
}

DOIP_EXPORT void
ne_doip_list_insert_list(ne_doip_list_t *list, ne_doip_list_t *other)
{
    if (ne_doip_list_empty(other)) {
        return;
    }

    other->next->prev = list;
    other->prev->next = list->next;
    list->next->prev = other->prev;
    list->next = other->next;
}

DOIP_EXPORT void
ne_doip_get_timespec(struct timespec *time, int32_t msec)
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    time->tv_sec = now.tv_sec + (msec / 1000);
    time->tv_nsec = now.tv_nsec + (msec % 1000) * 1000000;

    /* bigger than one second */
    if (time->tv_nsec >= 1000000000) {
        time->tv_sec++;
        time->tv_nsec -= 1000000000;
    }
}

DOIP_EXPORT void
ne_doip_set_timespec(struct timespec *time, int32_t msec)
{
    time->tv_sec += (msec / 1000);
    time->tv_nsec += ((msec % 1000) * 1000000);

    /* bigger than one second */
    if (time->tv_nsec >= 1000000000) {
        time->tv_sec++;
        time->tv_nsec -= 1000000000;
    }
}

DOIP_EXPORT int32_t
ne_doip_subtimespec(struct timespec *time1, struct timespec *time2)
{
    int32_t ms = (time1->tv_sec * 1000) + (time1->tv_nsec / 1000000)
        - ((time2->tv_sec * 1000) + (time2->tv_nsec / 1000000));

    return ms;
}

DOIP_EXPORT uint32_t
ne_doip_get_tick_cnt(void)
{
    struct timespec time;
    ne_doip_get_timespec(&time, 0);
    return time.tv_sec * 1000 + (time.tv_nsec / 1000000);
}

/* uint16_t big end <-> small end conversion */
DOIP_EXPORT uint16_t
ne_doip_bswap_16(uint16_t x)
{
    return ((x & 0x00ff) << 8) | \
           ((x & 0xff00) >> 8) ;
}

/* uint32_t big end <-> small end conversion */
DOIP_EXPORT uint32_t
ne_doip_bswap_32(uint32_t x)
{
    return ((x & 0xff000000U) >> 24) | \
           ((x & 0x00ff0000U) >> 8) | \
           ((x & 0x0000ff00U) << 8) | \
           ((x & 0x000000ffU) << 24) ;
}

/* Convert a MAC address in the form of a string to a 6-byte structure */
DOIP_EXPORT void
ne_doip_convert_mac(char *str_out, const char *str_in)
{
    if (NULL == str_out || NULL == str_in) {
        return;
    }
    uint32_t n;
    uint8_t m = 0;
    /* Every two characters are stored as a numeric value */
    for (n = 0; n < strlen(str_in); n += 2) {
        uint8_t sum;
        /* n  0 2 4 6.... */
        if ((str_in[n] >= 'A') && (str_in[n] <= 'F')) {
            sum = (str_in[n] - 'A' + 10) * 16;
        }
        else {
            sum = (str_in[n] - '0') * 16;
        }
        /* n+1   1 3 5 7.... */
        if (str_in[n + 1] >= 'A' && str_in[n + 1] <= 'F') {
            sum += str_in[n + 1] - 'A' + 10;
        }
        else {
            sum += str_in[n + 1] - '0';
        }

        str_out[m] = sum;
        m++;
    }
}

DOIP_EXPORT void
ne_doip_log_output(const char* func_name, char* file_name, int32_t line_num, const char* fmt, ...)
{
    va_list pvar;
    va_start(pvar, fmt);
    char buf[1501] = { 0 };
    vsnprintf(buf, 1501 -1, fmt, pvar);
    va_end(pvar);

    if (g_logfunc != NULL) {
        g_logfunc(buf);
    }
    else {
        char buf_time[100] = { 0 };
        int32_t size = 100;
        tzset();
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        struct tm *timeinfo = localtime(&ts.tv_sec);

        snprintf(buf_time, size, "[%02d-%02d %02d:%02d:%02d.%05ld line:%04d]",
                timeinfo->tm_mon + 1,
                timeinfo->tm_mday,
                timeinfo->tm_hour,
                timeinfo->tm_min,
                timeinfo->tm_sec,
                ts.tv_nsec / 10000,
                line_num);

        printf("%s  %s", buf_time, buf);
    }
}

DOIP_EXPORT char*
ne_doip_diag_dtlog(uint8_t domain_type, uint8_t error_type, uint32_t error_code, uint16_t payload_type,
                   uint32_t payload_length, uint16_t source_address, uint16_t target_address)
{
    char* buf = (char*)malloc(sizeof(char) * 32);
    memset(buf, 0, 32);
    uint32_t pos = 0;
    memcpy(buf + pos, &domain_type, sizeof(domain_type));
    pos += sizeof(domain_type);
    memcpy(buf + pos, &error_type, sizeof(error_type));
    pos += sizeof(error_type);
    memcpy(buf + pos, &error_code, sizeof(error_code));
    pos += sizeof(error_code);
    memcpy(buf + pos, &payload_type, sizeof(payload_type));
    pos += sizeof(payload_type);
    memcpy(buf + pos, &payload_length, sizeof(payload_length));
    pos += sizeof(payload_length);
    memcpy(buf + pos, &source_address, sizeof(source_address));
    pos += sizeof(source_address);
    memcpy(buf + pos, &target_address, sizeof(target_address));
    // pos += sizeof(target_address);
    return buf;
}

DOIP_EXPORT char*
ne_doip_comm_dtlog(uint8_t domain_type, uint8_t error_type, uint32_t error_code)
{
    char* buf = (char*)malloc(sizeof(char) * 32);
    memset(buf, 0, 32);
    uint32_t pos = 0;
    memcpy(buf + pos, &domain_type, sizeof(domain_type));
    pos += sizeof(domain_type);
    memcpy(buf + pos, &error_type, sizeof(error_type));
    pos += sizeof(error_type);
    memcpy(buf + pos, &error_code, sizeof(error_code));
    // pos += sizeof(error_code);
    return buf;
}

DOIP_EXPORT char*
ne_doip_socket_dtlog(uint8_t domain_type, uint8_t error_type, uint32_t error_code, uint16_t soket_type, uint16_t soket_func)
{
    char* buf = (char*)malloc(sizeof(char) * 32);
    memset(buf, 0, 32);
    uint32_t pos = 0;
    memcpy(buf + pos, &domain_type, sizeof(domain_type));
    pos += sizeof(domain_type);
    memcpy(buf + pos, &error_type, sizeof(error_type));
    pos += sizeof(error_type);
    memcpy(buf + pos, &error_code, sizeof(error_code));
    pos += sizeof(error_code);
    memcpy(buf + pos, &soket_type, sizeof(soket_type));
    pos += sizeof(soket_type);
    memcpy(buf + pos, &soket_func, sizeof(soket_func));
    // pos += sizeof(soket_func);
    return buf;
}

DOIP_EXPORT char*
ne_doip_interface_dtlog(uint8_t domain_type, uint8_t error_type, uint32_t error_code, uint16_t function)
{
    char* buf = (char*)malloc(sizeof(char) * 32);
    memset(buf, 0, 32);
    uint32_t pos = 0;
    memcpy(buf + pos, &domain_type, sizeof(domain_type));
    pos += sizeof(domain_type);
    memcpy(buf + pos, &error_type, sizeof(error_type));
    pos += sizeof(error_type);
    memcpy(buf + pos, &error_code, sizeof(error_code));
    pos += sizeof(error_code);
    memcpy(buf + pos, &function, sizeof(function));
    // pos += sizeof(function);
    return buf;
}

void ne_doip_dt_log_write(char* buf)
{
    if (buf == NULL) {
        return;
    }
    ne_doip_dtlogfunc_callback g_dtlogfunc = NULL;
    uint8_t domain_type;
    memcpy(&domain_type, buf, 1);
    if (domain_type == NE_DOIP_DT_DOMAIN_TYPE_UDS_CLIENT) {
        g_dtlogfunc = g_equip_dtlogfunc;
    }
    else if (domain_type == NE_DOIP_DT_DOMAIN_TYPE_UDS_SERVER) {
        g_dtlogfunc = g_node_dtlogfunc;
    }
    else if (domain_type == NE_DOIP_DT_DOMAIN_TYPE_DOIP_SERVER) {
        g_dtlogfunc = g_server_dtlogfunc;
    }
    else {
        free(buf);
        return;
    }
    if (g_dtlogfunc == NULL) {
        free(buf);
        return;
    }

    g_dtlogfunc(buf, 32);
    free(buf);
}

DOIP_EXPORT void
ne_doip_printf_time(int32_t line)
{
    char buff[100] = { 0 };
    int32_t size = 100;
    tzset();
    struct timespec tv = { 0, 0 };
    clock_gettime(CLOCK_REALTIME, &tv);
    time_t timep = tv.tv_sec;
    struct tm ti_ptr;
    localtime_r(&timep, &ti_ptr);
    snprintf(buff, size, "[%04d/%02d/%02d %02d:%02d:%02d.%05ld line:%04d]",
    ti_ptr.tm_year + 1900,
    ti_ptr.tm_mon + 1,
    ti_ptr.tm_mday,
    ti_ptr.tm_hour,
    ti_ptr.tm_min,
    ti_ptr.tm_sec,
    tv.tv_nsec / 10000,
    line);
    printf("%s  ", buff);
}

DOIP_EXPORT void
ne_doip_set_logfunc_callback(ne_doip_logfunc_callback logfunc)
{
    g_logfunc = logfunc;
}

DOIP_EXPORT void
ne_doip_set_doip_server_dtlogfunc_callback(ne_doip_dtlogfunc_callback server_dtlogfunc)
{
    g_server_dtlogfunc = server_dtlogfunc;
}

DOIP_EXPORT void
ne_doip_set_doip_equip_dtlogfunc_callback(ne_doip_dtlogfunc_callback equip_dtlogfunc)
{
    g_equip_dtlogfunc = equip_dtlogfunc;
}

DOIP_EXPORT void
ne_doip_set_doip_node_dtlogfunc_callback(ne_doip_dtlogfunc_callback node_dtlogfunc)
{
    g_node_dtlogfunc = node_dtlogfunc;
}
/* EOF */
