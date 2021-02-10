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

#include "ne_doip_node_manager.h"
#include "ne_doip_util.h"

#define NE_DOIP_MINIMUM_SIZE    5


ne_doip_result_t ne_doip_pack_node_regist(ne_doip_connection_t *conn, uint16_t logical_addr,
                                          ne_doip_instence_type_t doip_instence_type)
{
    NE_DOIP_PRINT("[doip_node] ne_doip_pack_announce start ..\n");

    if (NULL == conn) {
        NE_DOIP_PRINT("[doip_node] conn is null..\n");
        return NE_DOIP_RESULT_ERROR;
    }

    uint32_t size = NE_DOIP_IN_COMMAND_LENGTH + NE_DOIP_LOGICAL_ADDRESS_LENGTH + NE_DOIP_IN_DATA_LENGTH + NE_DOIP_INSTANCE_TYPE_LENGTH;
    char* data = (char*)malloc(size);
    if (NULL == data) {
        return NE_DOIP_RESULT_ERROR;
    }
    memset(data, 0, size);

    uint32_t payload_length = NE_DOIP_LOGICAL_ADDRESS_LENGTH + NE_DOIP_INSTANCE_TYPE_LENGTH;

    uint8_t pos = 0;
    data[pos] = NE_DOIP_IN_PAYLOADTYPE_NODE_RGIST;
    pos += NE_DOIP_IN_COMMAND_LENGTH;
    memcpy(data + pos, &payload_length, NE_DOIP_IN_DATA_LENGTH);
    pos += NE_DOIP_IN_DATA_LENGTH;
    logical_addr = ne_doip_bswap_16(logical_addr);
    memcpy(data + pos, &logical_addr, NE_DOIP_LOGICAL_ADDRESS_LENGTH);
    pos += NE_DOIP_LOGICAL_ADDRESS_LENGTH;
    memcpy(data + pos, &doip_instence_type, NE_DOIP_INSTANCE_TYPE_LENGTH);

    memcpy(conn->out.data, data, size);
    conn->out.data_size = size;
    free(data);
    return NE_DOIP_RESULT_OK;
}

ne_doip_result_t ne_doip_pack_regis_confirmation(ne_doip_connection_t *conn)
{
    NE_DOIP_PRINT("[doip_node] ne_doip_pack_regis_confirmation start ..\n");

    if (NULL == conn) {
        NE_DOIP_PRINT("[doip_node] conn is null..\n");
        return NE_DOIP_RESULT_ERROR;
    }

    uint32_t size = NE_DOIP_IN_COMMAND_LENGTH + NE_DOIP_IN_DATA_LENGTH;
    char* data = (char*)malloc(size);
    if (NULL == data) {
        return NE_DOIP_RESULT_ERROR;
    }
    memset(data, 0, size);
    uint32_t payload_length = 0;

    uint8_t pos = 0;
    data[pos] = NE_DOIP_IN_PAYLOADTYPE_REGIST_USER_CONF;
    pos += NE_DOIP_IN_COMMAND_LENGTH;
    memcpy(data + pos, &payload_length, NE_DOIP_IN_DATA_LENGTH);

    memcpy(conn->out.data, data, size);
    conn->out.data_size = size;
    free(data);
    return NE_DOIP_RESULT_OK;
}

ne_doip_result_t ne_doip_pack_user_conf_result(ne_doip_connection_t *conn,
                                               uint16_t logical_source_address,
                                               uint16_t logical_target_address,
                                               ne_doip_user_con_result_t result)
{
    NE_DOIP_PRINT("[doip_node] ne_doip_pack_user_conf_result start ..\n");

    if (NULL == conn) {
        NE_DOIP_PRINT("[doip_node] conn is null..\n");
        return NE_DOIP_RESULT_ERROR;
    }

    uint32_t size = NE_DOIP_IN_COMMAND_LENGTH + NE_DOIP_IN_DATA_LENGTH + (NE_DOIP_LOGICAL_ADDRESS_LENGTH * 2) + NE_DOIP_CONF_RESULT_LENGTH;
    char* data = (char*)malloc(size);
    if (NULL == data) {
        return NE_DOIP_RESULT_ERROR;
    }
    memset(data, 0, size);

    uint32_t payload_length = NE_DOIP_LOGICAL_ADDRESS_LENGTH * 2 + NE_DOIP_CONF_RESULT_LENGTH;
    uint8_t pos = 0;
    data[pos] = NE_DOIP_IN_PAYLOADTYPE_USER_CONF_RESULT;
    pos += NE_DOIP_IN_COMMAND_LENGTH;
    memcpy(data + pos, &payload_length, NE_DOIP_IN_DATA_LENGTH);
    pos += NE_DOIP_IN_DATA_LENGTH;
    uint16_t logical_addr = ne_doip_bswap_16(logical_source_address);
    memcpy(data + pos, &logical_addr, NE_DOIP_LOGICAL_ADDRESS_LENGTH);
    pos += NE_DOIP_LOGICAL_ADDRESS_LENGTH;
    logical_addr = ne_doip_bswap_16(logical_target_address);
    memcpy(data + pos, &logical_addr, NE_DOIP_LOGICAL_ADDRESS_LENGTH);
    pos += NE_DOIP_LOGICAL_ADDRESS_LENGTH;
    memcpy(data + pos, &result, NE_DOIP_CONF_RESULT_LENGTH);

    memcpy(conn->out.data, data, size);
    conn->out.data_size = size;
    free(data);
    return NE_DOIP_RESULT_OK;
}

ne_doip_result_t ne_doip_pack_diagnositc_res(ne_doip_connection_t *conn,
                                             uint16_t logical_source_address,
                                             uint16_t logical_target_address,
                                             char* data,
                                             uint32_t length)
{
    NE_DOIP_PRINT("ne_doip_pack_diagnositc_res start ..\n");
    if (NULL == conn || NULL == data) {
        NE_DOIP_PRINT("conn or data is null ..\n");
        return NE_DOIP_RESULT_PARAMETER_ERROR;
    }

    uint32_t size = length + NE_DOIP_IN_COMMAND_LENGTH + NE_DOIP_IN_DATA_LENGTH + (NE_DOIP_LOGICAL_ADDRESS_LENGTH * 2);
    char* send_data = (char*)malloc(size);
    if (NULL == send_data) {
        return NE_DOIP_RESULT_ERROR;
    }
    memset(send_data, 0, size);

    uint32_t payload_length = NE_DOIP_LOGICAL_ADDRESS_LENGTH * 2 + length;
    uint8_t pos = 0;
    send_data[pos] = NE_DOIP_IN_PAYLOADTYPE_DIAG_REQUEST;
    pos += NE_DOIP_IN_COMMAND_LENGTH;
    memcpy(send_data + pos, &payload_length, NE_DOIP_IN_DATA_LENGTH);
    pos += NE_DOIP_IN_DATA_LENGTH;
    uint16_t logical_addr = ne_doip_bswap_16(logical_source_address);
    memcpy(send_data + pos, &logical_addr, NE_DOIP_LOGICAL_ADDRESS_LENGTH);
    pos += NE_DOIP_LOGICAL_ADDRESS_LENGTH;
    logical_addr = ne_doip_bswap_16(logical_target_address);
    memcpy(send_data + pos, &logical_addr, NE_DOIP_LOGICAL_ADDRESS_LENGTH);
    pos += NE_DOIP_LOGICAL_ADDRESS_LENGTH;
    memcpy(send_data + pos, data, length);

    memcpy(conn->out.data, send_data, size);

    conn->out.data_size = size;
    free(send_data);
    return NE_DOIP_RESULT_OK;
}

uint32_t ne_doip_node_unpack_exec(ne_doip_node_t* doip_node, uint32_t pos)
{
    ne_doip_connection_t *conn = doip_node->connection;

    if ((doip_node->diag_data_total_length - doip_node->diag_data_current_pos) > 0
        && conn->in.data_size != NE_DOIP_MINIMUM_SIZE) {
        uint32_t rest_length = doip_node->diag_data_total_length - doip_node->diag_data_current_pos;
        NE_DOIP_PRINT("rest_length is %u...\n", rest_length);
        if (rest_length > conn->in.data_size) {
            /* intermediate packet */
            doip_node->diag_data_current_pos += conn->in.data_size;
            if (NULL == doip_node->diag_data_cach_buffer) {
                return 0;
            }
            char* diag_data_cach_buffer_new = realloc(doip_node->diag_data_cach_buffer, doip_node->diag_data_current_pos - NE_DOIP_LOGICAL_ADDRESS_LENGTH * 2);
            if (NULL == diag_data_cach_buffer_new) {
                free(doip_node->diag_data_cach_buffer);
                return 0;
            }
            else {
                doip_node->diag_data_cach_buffer = diag_data_cach_buffer_new;
                int pos_t = doip_node->diag_data_current_pos - conn->in.data_size - NE_DOIP_LOGICAL_ADDRESS_LENGTH * 2;
                memcpy(doip_node->diag_data_cach_buffer + pos_t, conn->in.data, conn->in.data_size);
            }
            pos = conn->in.data_size;
        }
        else {
            /* last packet */
            doip_node->diag_data_current_pos += rest_length;
            if (NULL == doip_node->diag_data_cach_buffer) {
                return 0;
            }

            if (doip_node->indication_callback != NULL) {
                ne_doip_diag_data_indication_t* diag_data_indication = (ne_doip_diag_data_indication_t*)malloc(sizeof *diag_data_indication);
                if (NULL == diag_data_indication) {
                    return 0;
                }
                memset(diag_data_indication, 0, sizeof *diag_data_indication);

                diag_data_indication->logical_source_address = doip_node->logical_target_address;
                diag_data_indication->logical_target_address = doip_node->logical_source_address;
                diag_data_indication->ta_type = doip_node->ta_type;

                diag_data_indication->data = realloc(doip_node->diag_data_cach_buffer, doip_node->diag_data_current_pos - NE_DOIP_LOGICAL_ADDRESS_LENGTH * 2);
                if (NULL == diag_data_indication->data) {
                    free(diag_data_indication);
                    free(doip_node->diag_data_cach_buffer);
                    return 0;
                }
                else {
                    int pos_t = doip_node->diag_data_current_pos - rest_length - NE_DOIP_LOGICAL_ADDRESS_LENGTH * 2;
                    memcpy(diag_data_indication->data + pos_t, conn->in.data, rest_length);

                    diag_data_indication->data_length = doip_node->diag_data_total_length - NE_DOIP_LOGICAL_ADDRESS_LENGTH * 2;
                    diag_data_indication->result = NE_DOIP_RESULT_OK;

                    doip_node->indication_callback(diag_data_indication);
                    free(diag_data_indication->data);
                    free(diag_data_indication);
                }
            }
            pos = rest_length;
            doip_node->diag_data_total_length = 0;
            doip_node->diag_data_current_pos = 0;
        }
    }
    else {
        uint8_t res_type = conn->in.data[pos];

        if (NE_DOIP_IN_PAYLOADTYPE_DIAG_INDICATION == res_type) {
            NE_DOIP_PRINT("type is [NE_DOIP_IN_PAYLOADTYPE_DIAG_INDICATION] .\n");
            uint16_t equip_logical_address;
            uint16_t entity_logical_address;

            pos += NE_DOIP_IN_COMMAND_LENGTH;
            memcpy(&doip_node->diag_data_total_length, conn->in.data + pos, NE_DOIP_IN_DATA_LENGTH);
            pos += NE_DOIP_IN_DATA_LENGTH;
            memcpy(&doip_node->ta_type, conn->in.data + pos, NE_DOIP_TA_TYPE_LENGTH);
            pos += NE_DOIP_TA_TYPE_LENGTH;
            uint32_t payload_data_length = 0;
            if (doip_node->diag_data_total_length > conn->in.data_size - pos) {
                payload_data_length = conn->in.data_size - pos;
            }
            else {
                payload_data_length = doip_node->diag_data_total_length;
            }
            memcpy(&equip_logical_address, conn->in.data + pos, NE_DOIP_LOGICAL_ADDRESS_LENGTH);
            pos += NE_DOIP_LOGICAL_ADDRESS_LENGTH;
            memcpy(&entity_logical_address, conn->in.data + pos, NE_DOIP_LOGICAL_ADDRESS_LENGTH);
            pos += NE_DOIP_LOGICAL_ADDRESS_LENGTH;
            equip_logical_address = ne_doip_bswap_16(equip_logical_address);
            entity_logical_address = ne_doip_bswap_16(entity_logical_address);

            doip_node->diag_data_current_pos += payload_data_length;

            uint32_t uds_buffer_size = payload_data_length - NE_DOIP_LOGICAL_ADDRESS_LENGTH * 2;
            char* uds_buffer = (char*)malloc(uds_buffer_size);
            if (NULL == uds_buffer) {
                return 0;
            }

            memcpy(uds_buffer, conn->in.data + pos, uds_buffer_size);
            pos += uds_buffer_size;

            doip_node->logical_target_address = equip_logical_address;

            if (entity_logical_address != doip_node->logical_source_address
                && doip_node->ta_type != NE_DOIP_TA_TYPE_FUNCTIONAL) {
                NE_DOIP_PRINT("entity address is not match!\n");
                free(uds_buffer);
                return pos;
            }
            else {

                if (doip_node->diag_data_current_pos == doip_node->diag_data_total_length) {
                    doip_node->diag_data_total_length = 0;
                    doip_node->diag_data_current_pos = 0;

                    if (doip_node->indication_callback != NULL) {
                        ne_doip_diag_data_indication_t* diag_data_indication = (ne_doip_diag_data_indication_t*)malloc(sizeof *diag_data_indication);
                        if (NULL == diag_data_indication) {
                            free(uds_buffer);
                            return 0;
                        }
                        memset(diag_data_indication, 0, sizeof(ne_doip_diag_data_indication_t));

                        diag_data_indication->logical_source_address = doip_node->logical_target_address;
                        diag_data_indication->logical_target_address = doip_node->logical_source_address;
                        diag_data_indication->ta_type = doip_node->ta_type;
                        diag_data_indication->data = uds_buffer;
                        diag_data_indication->data_length = uds_buffer_size;
                        diag_data_indication->result = NE_DOIP_RESULT_OK;

                        doip_node->indication_callback(diag_data_indication);
                        free(uds_buffer);
                        free(diag_data_indication);
                    }
                    else {
                        free(uds_buffer);
                    }
                }
                else {
                    /* first packet */
                    doip_node->diag_data_cach_buffer = (char*)malloc(uds_buffer_size);
                    if (NULL == doip_node->diag_data_cach_buffer) {
                        free(uds_buffer);
                        return 0;
                    }

                    memcpy(doip_node->diag_data_cach_buffer, uds_buffer, uds_buffer_size);
                    free(uds_buffer);
                }
            }
        }
        else if (NE_DOIP_IN_PAYLOADTYPE_USER_CONF_RESULT == res_type) {
            NE_DOIP_PRINT("type is [NE_DOIP_IN_PAYLOADTYPE_USER_CONF_RESULT] .\n");
            pos += NE_DOIP_IN_COMMAND_LENGTH;
            uint32_t payload_data_length = 0;
            memcpy(&payload_data_length, conn->in.data + pos, NE_DOIP_IN_DATA_LENGTH);
            pos += NE_DOIP_IN_DATA_LENGTH;

            if ((pos + payload_data_length) > conn->in.data_size) {
                NE_DOIP_PRINT("Data is stuck, this case is not processed\n");
                return 0;
            }
            uint16_t equip_logical_address;
            uint16_t entity_logical_address;
            memcpy(&equip_logical_address, conn->in.data + pos, NE_DOIP_LOGICAL_ADDRESS_LENGTH);
            pos += NE_DOIP_LOGICAL_ADDRESS_LENGTH;
            memcpy(&entity_logical_address, conn->in.data + pos, NE_DOIP_LOGICAL_ADDRESS_LENGTH);
            pos = pos - NE_DOIP_LOGICAL_ADDRESS_LENGTH + payload_data_length;
            equip_logical_address = ne_doip_bswap_16(equip_logical_address);
            entity_logical_address = ne_doip_bswap_16(entity_logical_address);

            if (entity_logical_address != doip_node->logical_source_address) {
                NE_DOIP_PRINT("entity address is not match!\n");
                return pos;
            }
            else {
                if (doip_node->user_conf_callback != NULL) {
                    doip_node->user_conf_callback(equip_logical_address, entity_logical_address);
                }
            }
        }
        else if (NE_DOIP_IN_PAYLOADTYPE_DIAG_CONFIRM == res_type) {
            NE_DOIP_PRINT("type is [NE_DOIP_IN_PAYLOADTYPE_DIAG_CONFIRM] .\n");
            pos += NE_DOIP_IN_COMMAND_LENGTH;
            uint32_t payload_data_length = 0;
            memcpy(&payload_data_length, conn->in.data + pos, NE_DOIP_IN_DATA_LENGTH);
            pos += NE_DOIP_IN_DATA_LENGTH;

            if ((pos + payload_data_length) > conn->in.data_size) {
                NE_DOIP_PRINT("Data is stuck, this case is not processed\n");
                return 0;
            }
            uint16_t equip_logical_address;
            uint16_t entity_logical_address;
            memcpy(&equip_logical_address, conn->in.data + pos, NE_DOIP_LOGICAL_ADDRESS_LENGTH);
            pos += NE_DOIP_LOGICAL_ADDRESS_LENGTH;
            memcpy(&entity_logical_address, conn->in.data + pos, NE_DOIP_LOGICAL_ADDRESS_LENGTH);
            pos = pos - NE_DOIP_LOGICAL_ADDRESS_LENGTH + payload_data_length;
            equip_logical_address = ne_doip_bswap_16(equip_logical_address);
            entity_logical_address = ne_doip_bswap_16(entity_logical_address);
            if (entity_logical_address != doip_node->logical_source_address) {
                NE_DOIP_PRINT("entity address is not match!\n");
                return pos;
            }
            else {
                ne_doip_diag_data_confirm_t* diag_data_confirm = (ne_doip_diag_data_confirm_t*)malloc(sizeof *diag_data_confirm);
                if (NULL == diag_data_confirm) {
                    return 0;
                }
                memset(diag_data_confirm, 0, sizeof(ne_doip_diag_data_confirm_t));

                diag_data_confirm->logical_source_address = equip_logical_address;
                diag_data_confirm->logical_target_address = entity_logical_address;
                diag_data_confirm->ta_type = doip_node->ta_type;
                diag_data_confirm->result = NE_DOIP_RESULT_OK;

                if (doip_node->confirm_callback != NULL) {
                    doip_node->confirm_callback(diag_data_confirm);
                }
                free(diag_data_confirm);
            }
        }
        else if (NE_DOIP_IN_PAYLOADTYPE_EQUIP_LINK_DISCONNECTED == res_type) {
            NE_DOIP_PRINT("type is [NE_DOIP_IN_PAYLOADTYPE_EQUIP_LINK_DISCONNECTED] .\n");
            pos += NE_DOIP_IN_COMMAND_LENGTH + NE_DOIP_IN_DATA_LENGTH;
            doip_node->diag_data_total_length = 0;
            doip_node->diag_data_current_pos = 0;
        }
        else {
            return 0;
        }
    }

    return pos;
}

void ne_doip_node_unpack(ne_doip_node_t* doip_node)
{
    NE_DOIP_PRINT("[doip_node] ne_doip_node_unpack start ..\n");
    if (NULL == doip_node) {
        NE_DOIP_PRINT("doip_node is null ..\n");
        return;
    }

    ne_doip_connection_t *conn = doip_node->connection;
    if (NULL == conn) {
        NE_DOIP_PRINT("conn is null ..\n");
        return;
    }

#ifdef NE_DOIP_DEBUG
    printf("recv data is ");
    uint32_t i;
    for (i = 0; i < conn->in.data_size; ++i) {
        printf("%02X", (unsigned char)conn->in.data[i]);
    }
    printf("\n");
#endif

    uint32_t pos = 0;
    do {
        pos = ne_doip_node_unpack_exec(doip_node, pos);
        if (0 == pos) {
            break;
        }
    } while ((conn->in.data_size - pos) > 0);
}
/* EOF */
