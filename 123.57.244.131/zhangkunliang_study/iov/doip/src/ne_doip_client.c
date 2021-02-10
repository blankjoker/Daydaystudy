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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <stddef.h>

#include "ne_doip_client.h"
#include "ne_doip_def.h"
#include "ne_doip_os.h"
#include "ne_doip_client_manager.h"
#include "ne_doip_util.h"

/*********************************************************************
    date definition
*********************************************************************/

#define NE_DOIP_IPC_PATH                    "/dev/socket/"
#define NE_DOIP_IPC_TEST_EQUIP_THREAD       "NE_DOIP_IPC_TEST_EQUIP_THREAD"
#define NE_DOIP_SERVER_NAME                 "doip"
#define NE_DOIP_SUB_THREAD_NAME_SIZE         40

#define NE_DOIP_ERRNO_SUCCESS                0
#define NE_DOIP_ERRNO_RESOURCE_UNAVAILABLE   11
#define NE_DOIP_ERRNO_ALREADYCONNECTED       106

#define NE_DOIP_CONNECT_SLEEP_TIME           100 /* 100 us */
#define NE_DOIP_CONNECT_RETRY_COUNT          10

static ne_doip_test_equip_t *g_test_equip = NULL;

/*********************************************************************
    internal interface
*********************************************************************/

uint16_t
ne_doip_get_test_equip_logical_address(void)
{
    if (g_test_equip != NULL) {
        return g_test_equip->logical_source_address;
    }
    return 0;
}

ne_doip_test_equip_t*
ne_doip_get_test_equip_instance(void)
{
    if (g_test_equip != NULL) {
        return g_test_equip;
    }
    return NULL;
}

/* main Thread function */
void*
ne_doip_equip_main_pthread_proc(ne_doip_thread_t *thread, void *arg)
{
    ne_doip_test_equip_t *test_equip = (ne_doip_test_equip_t *)arg;
    if (test_equip == NULL || test_equip->connection == NULL) {
        return NULL;
    }

    while (1) {
        int32_t num = ne_doip_connection_read(test_equip->connection);
        if ((num <= 0) && (errno != EAGAIN)) {
            if (num == 0) {
                NE_DOIP_PRINT("ne_doip_equip_pthread_proc DOIP_EVENT_HANGUP\n");
                ne_doip_dt_log_write(NE_DOIP_DT_FORMAT_SOCKET_EQUIP(errno, NE_DOIP_SOCKET_TYPE_IPC, NE_DOIP_SOCKET_READ_EOF));
            }
            else {
                NE_DOIP_PRINT("ne_doip_equip_pthread_proc read error! code:%d, message:%s\n", errno, strerror(errno));
                ne_doip_dt_log_write(NE_DOIP_DT_FORMAT_SOCKET_EQUIP(errno, NE_DOIP_SOCKET_TYPE_IPC, NE_DOIP_SOCKET_READ));
            }
            if (test_equip->connection != NULL) {
                ne_doip_connection_destroy(test_equip->connection);
                free(test_equip->connection);
                test_equip->connection = NULL;
            }
            return NULL;
        }
        else if (num > 0) {
            ne_doip_equip_unpack(test_equip->connection);
        }
        else {
            /* do nothing, continue */
        }
    }

    return NULL;
}

void*
ne_doip_equip_sub_pthread_proc(ne_doip_thread_t *thread, void *arg)
{
    ne_doip_equip_diag_req_t *diag_req = (ne_doip_equip_diag_req_t *)arg;
    if (diag_req == NULL || diag_req->connection == NULL || g_test_equip == NULL) {
        return NULL;
    }

    while (1) {
        int32_t num = ne_doip_connection_read(diag_req->connection);
        if ((num <= 0) && (errno != EAGAIN)) {
            if (num == 0) {
                NE_DOIP_PRINT("ne_doip_equip_sub_pthread_proc DOIP_EVENT_HANGUP\n");
                ne_doip_dt_log_write(NE_DOIP_DT_FORMAT_SOCKET_EQUIP(errno, NE_DOIP_SOCKET_TYPE_IPC, NE_DOIP_SOCKET_READ_EOF));
            }
            else {
                NE_DOIP_PRINT("ne_doip_equip_sub_pthread_proc read error! code:%d, message:%s\n", errno, strerror(errno));
                ne_doip_dt_log_write(NE_DOIP_DT_FORMAT_SOCKET_EQUIP(errno, NE_DOIP_SOCKET_TYPE_IPC, NE_DOIP_SOCKET_READ));
            }
            ne_doip_sync_start(g_test_equip->diag_list_sync);
            ne_doip_list_remove((ne_doip_list_t *) diag_req);

            if (diag_req->connection != NULL) {
                ne_doip_connection_destroy(diag_req->connection);
                free(diag_req->connection);
                diag_req->connection = NULL;
            }

            if (diag_req->thread) {
                ne_doip_thread_stop(diag_req->thread);
                diag_req->thread = NULL;
            }

            free(diag_req);
            diag_req = NULL;
            ne_doip_sync_end(g_test_equip->diag_list_sync);

            return NULL;
        }
        else if (num > 0) {
            ne_doip_equip_unpack(diag_req->connection);
        }
        else {
            /* do nothing, continue */
        }
    }

    return NULL;
}

/* Create main thread */
static ne_doip_result_t
ne_doip_main_thread_create(ne_doip_test_equip_t *test_equip)
{
    test_equip->thread = ne_doip_thread_create(ne_doip_equip_main_pthread_proc, test_equip, NE_DOIP_IPC_TEST_EQUIP_THREAD);
    if (NULL == test_equip->thread) {
        return NE_DOIP_RESULT_ERROR;
    }

    return NE_DOIP_RESULT_OK;
}

/* Create sub thread */
static ne_doip_result_t
ne_doip_sub_thread_create(ne_doip_equip_diag_req_t *diag_req)
{
    char thread_name[NE_DOIP_SUB_THREAD_NAME_SIZE] = { 0 };
    static uint16_t thread_num = 0;
    snprintf(thread_name, NE_DOIP_SUB_THREAD_NAME_SIZE, "NE_DOIP_IPC_TEST_EQUIP_SUB_THREAD_%d", thread_num++);
    NE_DOIP_PRINT("start sub thread.. name is %s\n", thread_name);

    diag_req->thread = ne_doip_thread_create(ne_doip_equip_sub_pthread_proc, diag_req, thread_name);
    if (NULL == diag_req->thread) {
        return NE_DOIP_RESULT_ERROR;
    }

    return NE_DOIP_RESULT_OK;
}

/* Create a socket, establish a link with the server, and return a file descriptor */
static int32_t
ne_doip_connect_to_socket(const char *name)
{
    int32_t fd;
    int32_t name_size;
    socklen_t size;
    struct sockaddr_un addr;

    fd = ne_doip_os_socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) {
        NE_DOIP_PRINT("ne_doip_connect_to_socket fd error code:%d, message:%s\n", errno, strerror(errno));
        ne_doip_dt_log_write(NE_DOIP_DT_FORMAT_SOCKET_EQUIP(errno, NE_DOIP_SOCKET_TYPE_IPC, NE_DOIP_SOCKET_CREATE));
        return -1;
    }

    addr.sun_family = AF_UNIX;
    name_size = snprintf(addr.sun_path, sizeof addr.sun_path,
                 "%s/%s", NE_DOIP_IPC_PATH, name) + 1;

    assert(name_size > 0);
    if (name_size > (int32_t)sizeof addr.sun_path) {
        NE_DOIP_PRINT("ne_doip_connect_to_socket name_size error!\n");
        close(fd);
        fd = -1;
        /* to prevent programs reporting
         * "failed to add socket: Success" */
        errno = ENAMETOOLONG;
        return fd;
    }

    size = (int32_t)offsetof(struct sockaddr_un, sun_path) + name_size;

    uint8_t retry_count = 0;
    do {
        ne_doip_os_connect(fd, (struct sockaddr *) &addr, size);
        NE_DOIP_PRINT("ne_doip_connect_to_socket error code:%d, message:%s\n", errno, strerror(errno));
        if (NE_DOIP_ERRNO_RESOURCE_UNAVAILABLE == errno) {
            usleep(NE_DOIP_CONNECT_SLEEP_TIME);
        }
        else if (NE_DOIP_ERRNO_SUCCESS == errno || NE_DOIP_ERRNO_ALREADYCONNECTED == errno) {
            break;
        }
        else {
            ne_doip_dt_log_write(NE_DOIP_DT_FORMAT_SOCKET_EQUIP(errno, NE_DOIP_SOCKET_TYPE_IPC, NE_DOIP_SOCKET_CONNECT));
            close(fd);
            fd = -1;
            return fd;
        }
        ++retry_count;
    } while (retry_count < NE_DOIP_CONNECT_RETRY_COUNT);

    return fd;
}

static ne_doip_test_equip_t *
ne_doip_test_equip_connect(void)
{
    int32_t fd = ne_doip_connect_to_socket(NE_DOIP_SERVER_NAME);
    if (fd < 0) {
        return NULL;
    }

    ne_doip_test_equip_t *test_equip = (ne_doip_test_equip_t*)malloc(sizeof *test_equip);
    if (NULL == test_equip) {
        close(fd);
        return NULL;
    }
    memset(test_equip, 0, sizeof *test_equip);

    test_equip->fd = fd;
    test_equip->connection = ne_doip_connection_create(fd);
    if (NULL == test_equip->connection) {
        free(test_equip);
        close(fd);
        return NULL;
    }

    ne_doip_result_t result = ne_doip_main_thread_create(test_equip);
    if (result != NE_DOIP_RESULT_OK) {
        free(test_equip);
        close(fd);
        return NULL;
    }

    return test_equip;
}

static ne_doip_equip_diag_req_t *
ne_doip_test_equip_diag_req_connect(void)
{
    int32_t fd = ne_doip_connect_to_socket(NE_DOIP_SERVER_NAME);
    if (fd < 0) {
        return NULL;
    }
    ne_doip_equip_diag_req_t *diag_req = (ne_doip_equip_diag_req_t*)malloc(sizeof *diag_req);
    if (NULL == diag_req) {
        close(fd);
        return NULL;
    }
    memset(diag_req, 0, sizeof *diag_req);

    diag_req->connection = ne_doip_connection_create(fd);
    if (NULL == diag_req->connection) {
        free(diag_req);
        close(fd);
        return NULL;
    }

    ne_doip_result_t result = ne_doip_sub_thread_create(diag_req);
    if (result != NE_DOIP_RESULT_OK) {
        free(diag_req);
        close(fd);
        return NULL;
    }

    return diag_req;
}

ne_doip_equip_diag_req_t *
ne_doip_diag_list_find_by_address(uint16_t logical_target_address)
{
    ne_doip_equip_diag_req_t *diag_req = NULL;
    ne_doip_list_for_each(diag_req, g_test_equip->diag_list, base) {
        if (diag_req->logical_target_address == logical_target_address) {
            return diag_req;
        }
    }
    return NULL;
}

void ne_doip_release_source(void)
{
    if (NULL == g_test_equip) {
        return;
    }

    NE_DOIP_PRINT("ne_doip_release_source start..\n");
    if (g_test_equip->thread != NULL) {
        ne_doip_thread_terminate(g_test_equip->thread);
        g_test_equip->thread = NULL;
    }

    if (g_test_equip->connection != NULL) {
        ne_doip_connection_destroy(g_test_equip->connection);
        free(g_test_equip->connection);
        g_test_equip->connection = NULL;
    }

    if (g_test_equip->diag_list_sync != NULL) {
        ne_doip_sync_destroy(g_test_equip->diag_list_sync);
        g_test_equip->diag_list_sync = NULL;
    }

    free(g_test_equip);
    g_test_equip = NULL;

    NE_DOIP_PRINT("ne_doip_release_source end..\n");
}

/************************** for doip equip I/F ********************************/

DOIP_EXPORT
ne_doip_result_t ne_doip_equip_create(uint16_t logical_source_address,
                                      ne_doip_equip_callback_register_t callback_register)
{
    NE_DOIP_PRINT("ne_doip_equip_create\n");
    if (NULL == g_test_equip) {
        g_test_equip = ne_doip_test_equip_connect();
        if (g_test_equip == NULL) {
            NE_DOIP_PRINT("ne_doip_equip_create is null\n");
            return NE_DOIP_RESULT_ERROR;
        }

        g_test_equip->diag_list_sync = ne_doip_sync_create();
        if (NULL == g_test_equip->diag_list_sync) {
            ne_doip_release_source();
            return NE_DOIP_RESULT_ERROR;
        }

        ne_doip_equip_diag_req_t *list = (ne_doip_equip_diag_req_t*)malloc(sizeof *list);
        if (NULL == list) {
            ne_doip_release_source();
            return NE_DOIP_RESULT_ERROR;
        }
        memset(list, 0, sizeof *list);
        ne_doip_list_init((ne_doip_list_t *)list);

        ne_doip_sync_start(g_test_equip->diag_list_sync);
        g_test_equip->diag_list = (ne_doip_list_t *)list;
        ne_doip_sync_end(g_test_equip->diag_list_sync);
    }

    if (0 == g_test_equip->logical_source_address) {

        ne_doip_connection_t *conn = g_test_equip->connection;
        if (NULL == conn) {
            return NE_DOIP_RESULT_ERROR;
        }
        memset(&conn->out, 0, sizeof conn->out);

        if (0 == ne_doip_pack_test_equip_regist(conn, logical_source_address)) {
            g_test_equip->logical_source_address = logical_source_address;
            g_test_equip->vehicle_identity_callback = callback_register.vehicle_identity_cb;
            g_test_equip->routing_active_callback = callback_register.routing_active_cb;
            g_test_equip->entity_status_callback = callback_register.entity_status_cb;
            g_test_equip->power_mode_callback = callback_register.power_mode_cb;
            g_test_equip->daig_pack_callback = callback_register.diag_pack_cb;
            g_test_equip->daig_nack_callback = callback_register.diag_nack_cb;
            g_test_equip->diagnostic_callback = callback_register.diagnostic_cb;

            return NE_DOIP_RESULT_OK;
        }
        else {
            return NE_DOIP_RESULT_ERROR;
        }
    }
    else {
        ne_doip_dt_log_write(NE_DOIP_DT_FORMAT_INTERFACE_EQUIP(NE_DOIP_RESULT_REPEAT_REGIST, NE_DOIP_EQUIP_CREATE));
        return NE_DOIP_RESULT_REPEAT_REGIST;
    }
}

DOIP_EXPORT
ne_doip_result_t ne_doip_equip_destroy(uint16_t logical_source_address)
{
    NE_DOIP_PRINT("ne_doip_equip_destroy is start.\n");
    if (NULL == g_test_equip) {
        NE_DOIP_PRINT("internal test equipment is already destroyed\n");
        return NE_DOIP_RESULT_ERROR;
    }

    if (g_test_equip->logical_source_address != logical_source_address) {
        ne_doip_dt_log_write(NE_DOIP_DT_FORMAT_INTERFACE_EQUIP(NE_DOIP_RESULT_UNKNOWN_SA, NE_DOIP_EQUIP_DESTROY));
        return NE_DOIP_RESULT_UNKNOWN_SA;
    }

    ne_doip_equip_diag_req_t *diag_req = NULL;
    ne_doip_equip_diag_req_t *diag_req_tmp = NULL;
    ne_doip_sync_start(g_test_equip->diag_list_sync);
    ne_doip_list_for_each_safe(diag_req, diag_req_tmp, g_test_equip->diag_list, base) {
        if (diag_req->thread) {
            ne_doip_thread_terminate(diag_req->thread);
            diag_req->thread = NULL;
        }

        if (diag_req->connection != NULL) {
            ne_doip_connection_destroy(diag_req->connection);
                free(diag_req->connection);
                diag_req->connection = NULL;
        }

        ne_doip_list_t *list_node = (ne_doip_list_t *) diag_req;
        ne_doip_list_remove(list_node);
        free(diag_req);
    }

    free(g_test_equip->diag_list);
    g_test_equip->diag_list = NULL;

    ne_doip_sync_end(g_test_equip->diag_list_sync);

    ne_doip_release_source();

    NE_DOIP_PRINT("ne_doip_equip_destroy is end.\n");

    return NE_DOIP_RESULT_OK;
}

DOIP_EXPORT
ne_doip_result_t ne_doip_equip_identity(char* data, /* default data is NULL | identification by EID data is EID array | identification by VIN data is VIN array */
                                        uint32_t length)
{
    ne_doip_result_t result = NE_DOIP_RESULT_OK;

    if (NULL == g_test_equip) {
        ne_doip_dt_log_write(NE_DOIP_DT_FORMAT_INTERFACE_EQUIP(NE_DOIP_RESULT_NOT_INITIALIZED, NE_DOIP_EQUIP_IDENTITY));
        result = NE_DOIP_RESULT_NOT_INITIALIZED;
    }
    else {
        if (NULL == data) {
            if (0 == length) {
                /* identification */
                ne_doip_connection_t *conn = g_test_equip->connection;
                if (NULL == conn) {
                    result = NE_DOIP_RESULT_ERROR;
                }
                else {
                    memset(&conn->out, 0, sizeof conn->out);
                    result = ne_doip_pack_vehicle_identify(conn);
                }
            }
            else {
                ne_doip_dt_log_write(NE_DOIP_DT_FORMAT_INTERFACE_EQUIP(NE_DOIP_RESULT_PARAMETER_ERROR, NE_DOIP_EQUIP_IDENTITY));
                result = NE_DOIP_RESULT_PARAMETER_ERROR;
            }
        }
        else {
            if (NE_DOIP_EID_SIZE == length) {
                /* identification by EID */
                ne_doip_connection_t *conn = g_test_equip->connection;
                if (NULL == conn) {
                    result = NE_DOIP_RESULT_ERROR;
                }
                else {
                    memset(&conn->out, 0, sizeof conn->out);
                    result = ne_doip_pack_vehicle_identify_eid(conn, data);
                }
            }
            else if (NE_DOIP_VIN_SIZE == length) {
                /* identification by VIN */
                ne_doip_connection_t *conn = g_test_equip->connection;
                if (NULL == conn) {
                    result = NE_DOIP_RESULT_ERROR;
                }
                else {
                    memset(&conn->out, 0, sizeof conn->out);
                    result = ne_doip_pack_vehicle_identify_vin(conn, data);
                }
            }
            else {
                ne_doip_dt_log_write(NE_DOIP_DT_FORMAT_INTERFACE_EQUIP(NE_DOIP_RESULT_PARAMETER_ERROR, NE_DOIP_EQUIP_IDENTITY));
                result = NE_DOIP_RESULT_PARAMETER_ERROR;
            }
        }
    }

    return result;
}

DOIP_EXPORT
ne_doip_result_t ne_doip_equip_routing_active(uint16_t logical_source_address, uint8_t activation_type,
                                              uint32_t oem_specific_use, char* eid)
{
    ne_doip_result_t result = NE_DOIP_RESULT_OK;

    if (NULL == g_test_equip) {
        ne_doip_dt_log_write(NE_DOIP_DT_FORMAT_INTERFACE_EQUIP(NE_DOIP_RESULT_NOT_INITIALIZED, NE_DOIP_EQUIP_ROUTING_ACTIVE));
        result = NE_DOIP_RESULT_NOT_INITIALIZED;
    }
    else {
        ne_doip_connection_t *conn = g_test_equip->connection;
        if (NULL == conn) {
            result = NE_DOIP_RESULT_ERROR;
        }
        else {
            memset(&conn->out, 0, sizeof conn->out);
            result = ne_doip_pack_routing_active(conn, logical_source_address,
                                                 activation_type, oem_specific_use, eid);
        }
    }

    return result;
}

DOIP_EXPORT
ne_doip_result_t ne_doip_equip_alive_check_res(uint16_t logical_target_address)
{
    ne_doip_result_t result = NE_DOIP_RESULT_OK;

    if (NULL == g_test_equip) {
        ne_doip_dt_log_write(NE_DOIP_DT_FORMAT_INTERFACE_EQUIP(NE_DOIP_RESULT_NOT_INITIALIZED, NE_DOIP_EQUIP_ALIVE_CHECK_RES));
        result = NE_DOIP_RESULT_NOT_INITIALIZED;
    }
    else {
        ne_doip_connection_t *conn = g_test_equip->connection;
        if (NULL == conn) {
            result = NE_DOIP_RESULT_ERROR;
        }
        else {
            memset(&conn->out, 0, sizeof conn->out);
            result = ne_doip_pack_alive_check_response(conn, logical_target_address);
        }
    }

    return result;
}

DOIP_EXPORT
ne_doip_result_t ne_doip_equip_entity_status_req(char* eid)
{
    ne_doip_result_t result = NE_DOIP_RESULT_OK;

    if (NULL == g_test_equip) {
        ne_doip_dt_log_write(NE_DOIP_DT_FORMAT_INTERFACE_EQUIP(NE_DOIP_RESULT_NOT_INITIALIZED, NE_DOIP_EQUIP_ENTITY_STATUS_REQ));
        result = NE_DOIP_RESULT_NOT_INITIALIZED;
    }
    else {
        ne_doip_connection_t *conn = g_test_equip->connection;
        if (NULL == conn) {
            result = NE_DOIP_RESULT_ERROR;
        }
        else {
            memset(&conn->out, 0, sizeof conn->out);
            result = ne_doip_pack_entity_status(conn, eid);
        }
    }

    return result;
}

DOIP_EXPORT
ne_doip_result_t ne_doip_equip_power_mode_req(char* eid)
{
    ne_doip_result_t result = NE_DOIP_RESULT_OK;

    if (NULL == g_test_equip) {
        ne_doip_dt_log_write(NE_DOIP_DT_FORMAT_INTERFACE_EQUIP(NE_DOIP_RESULT_NOT_INITIALIZED, NE_DOIP_EQUIP_POWER_MODE_REQ));
        result = NE_DOIP_RESULT_NOT_INITIALIZED;
    }
    else {
        ne_doip_connection_t *conn = g_test_equip->connection;
        if (NULL == conn) {
            result = NE_DOIP_RESULT_ERROR;
        }
        else {
            memset(&conn->out, 0, sizeof conn->out);
            result = ne_doip_pack_power_mode(conn, eid);
        }
    }

    return result;
}

DOIP_EXPORT
ne_doip_result_t ne_doip_equip_diagnostic(uint16_t logical_target_address,
                                          ne_doip_ta_type_t ta_type,
                                          char* data,
                                          uint32_t length)
{
    ne_doip_result_t result = NE_DOIP_RESULT_OK;

    if (NULL == g_test_equip) {
        ne_doip_dt_log_write(NE_DOIP_DT_FORMAT_INTERFACE_EQUIP(NE_DOIP_RESULT_NOT_INITIALIZED, NE_DOIP_EQUIP_DIAGNOSTIC));
        result = NE_DOIP_RESULT_NOT_INITIALIZED;
    }
    else if (NULL == data) {
        ne_doip_dt_log_write(NE_DOIP_DT_FORMAT_INTERFACE_EQUIP(NE_DOIP_RESULT_PARAMETER_ERROR, NE_DOIP_EQUIP_DIAGNOSTIC));
        result = NE_DOIP_RESULT_PARAMETER_ERROR;
    }
    else {
        ne_doip_equip_diag_req_t* diag_req = ne_doip_diag_list_find_by_address(logical_target_address);
        if (NULL == diag_req) {
            ne_doip_equip_diag_req_t* diag_req_t = ne_doip_test_equip_diag_req_connect();
            if (NULL == diag_req_t) {
                NE_DOIP_PRINT("ne_doip_equip_diag_req_create is null\n");
                result = NE_DOIP_RESULT_ERROR;
            }
            else {
                diag_req_t->logical_target_address = logical_target_address;
                ne_doip_sync_start(g_test_equip->diag_list_sync);
                ne_doip_list_insert(g_test_equip->diag_list->prev, (ne_doip_list_t *) diag_req_t);
                ne_doip_sync_end(g_test_equip->diag_list_sync);

                ne_doip_connection_t *conn = diag_req_t->connection;
                if (NULL == conn) {
                    result = NE_DOIP_RESULT_ERROR;
                }
                else {
                    memset(&conn->out, 0, sizeof conn->out);
                    result = ne_doip_pack_test_equip_regist(conn, g_test_equip->logical_source_address);
                    if (NE_DOIP_RESULT_OK == result) {
                        result = ne_doip_pack_diagnositc_req(conn, g_test_equip->logical_source_address,
                                                             logical_target_address, ta_type, data, length);
                    }
                }
            }
        }
        else {
            ne_doip_connection_t *conn = diag_req->connection;
            if (NULL == conn) {
                result = NE_DOIP_RESULT_ERROR;
            }
            else {
                memset(&conn->out, 0, sizeof conn->out);
                result = ne_doip_pack_diagnositc_req(conn, g_test_equip->logical_source_address,
                                                     logical_target_address, ta_type, data, length);
            }
        }
    }

    return result;
}

DOIP_EXPORT
ne_doip_result_t ne_doip_regist_doip_equip_dtlogfunc_callback(ne_doip_dtlogfunc_callback equip_dtlogfunc)
{
    NE_DOIP_PRINT("ne_doip_regist_doip_equip_dtlogfunc_callback enter!\n");

    ne_doip_result_t result = NE_DOIP_RESULT_OK;
    if (NULL == equip_dtlogfunc) {
        ne_doip_dt_log_write(NE_DOIP_DT_FORMAT_INTERFACE_EQUIP(NE_DOIP_RESULT_PARAMETER_ERROR, NE_DOIP_REGIST_DOIP_EQUIP_DTLOGFUNC_CALLBACK));
        result = NE_DOIP_RESULT_PARAMETER_ERROR;
    }
    ne_doip_set_doip_equip_dtlogfunc_callback(equip_dtlogfunc);

    return result;
}
/* EOF */
