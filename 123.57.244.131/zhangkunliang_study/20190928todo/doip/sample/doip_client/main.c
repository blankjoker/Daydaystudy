/**
 * Copyright @ 2019 iAuto (Shanghai) Co., Ltd.
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are NOT permitted except as agreed by
 * iAuto (Shanghai) Co., Ltd.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ne_doip_client.h"
#include "ne_doip_comm_def.h"

#define DOIP_NODE_1_LOGIC_ADDRESS 0x0200
#define DOIP_NODE_2_LOGIC_ADDRESS 0x0210
#define DOIP_NODE_3_LOGIC_ADDRESS 0x0220

#define DOIP_EQUIP_LOGIC_ADDRESS 0x0F11

#define DOIP_NODE_1_SUPPORT_MAX_DATA_SIZE 1024
#define DOIP_NODE_2_SUPPORT_MAX_DATA_SIZE 1024
#define DOIP_NODE_3_SUPPORT_MAX_DATA_SIZE 512

#define DOIP_NODE_1_AUTHENTICATION_INFO   0
#define DOIP_NODE_2_AUTHENTICATION_INFO   0x12345678
#define DOIP_NODE_3_AUTHENTICATION_INFO   0x12345678


void ne_uds_server_diag_indication_callback(ne_doip_diag_data_indication_t* diag_data_indication)
{
    printf("client send ne_uds_server_diag_indication_callback is enter...\n");
    if (NULL == diag_data_indication) {
        return;
    }
    /* DoIP_PDU transfer to T_PDU, Data definition reference ISO 14229-5   */
    /*                                                                     */
    // T_SA = diag_data_indication->logical_source_address;
    // T_TA = diag_data_indication->logical_target_address;
    // T_TAtype = diag_data_indication->ta_type;
    // memcpy(T_Data, diag_data_indication->data);
    // T_Length = diag_data_indication->data_length;
    // T_Result = diag_data_indication->result;
    /*                                                                     */
    /***********************************************************************/

    // The received data is transferred from the transport layer to the application layer.
}

void ne_uds_server_diag_confirm_callback(ne_doip_diag_data_confirm_t *diag_data_confirm)
{
    printf("client send ne_uds_server_diag_confirm_callback is enter...\n");
    if (NULL == diag_data_confirm) {
        return;
    }
    /*  DoIP_PDU transfer to T_PDU, Data definition reference ISO 14229-5  */
    /*                                                                     */
    // T_SA = diag_data_confirm->logical_source_address;
    // T_TA = diag_data_confirm->logical_target_address;
    // T_TAtype = diag_data_confirm->ta_type;
    // T_Result = diag_data_confirm->result;
    /*                                                                     */
    /***********************************************************************/

    // The received data is transferred from the transport layer to the application layer.
}

void ne_uds_server_send_data(uint16_t logical_source_address, uint16_t logical_target_address, uint8_t ta_type, char* data, uint32_t data_length)
{
    printf("ne_uds_data_send is enter...\n");

    ne_doip_diag_data_request_t* diag_data_request = malloc(sizeof *diag_data_request);
    if (NULL == diag_data_request) {
        return;
    }

    diag_data_request->logical_source_address = logical_source_address;
    diag_data_request->logical_target_address = logical_target_address;
    diag_data_request->ta_type = ta_type;
    diag_data_request->data = (char*)malloc(data_length);
    if (NULL == diag_data_request->data) {
        return;
    }
    memcpy(diag_data_request->data, data, data_length);
    diag_data_request->data_length = data_length;

    ne_doip_node_request_diag_data(diag_data_request);
    free(diag_data_request);
}

void ne_uds_server_user_conf_callback(uint16_t logical_source_address, uint16_t logical_target_address)
{
    printf("ne_uds_server_user_conf_callback_1 is enter...\n");
    // Passed to the upper application layer to confirm whether the route activation can pass, 
    // to ensure that the user can enter the next diagnosis sequence in a diagnostic state.
    sleep(1);

    // If the upper application layer is ready, call the following interface to send the confirmation result.
    // This case is confirmed by the user.
    ne_doip_node_send_user_conf_result(logical_target_address, logical_source_address, 1);
    // This case is did not confirmed by the user.
    // ne_doip_node_send_user_conf_result(logical_target_address, logical_source_address, 0);
}

void ne_uds_clinet_vehicle_identity_callback_func(ne_doip_vehicle_identity_resinfo_t* info)
{
    printf("ne_uds_clinet_vehicle_identity_callback_func is enter...\n");

    printf("ne_doip_vehicle_identity_resinfo_t vin is ");
    uint8_t i;
    for (i = 0; i < NE_DOIP_VIN_SIZE; ++i) {
        printf("%02X", (unsigned char)info->vin[i]);
    }
    printf("\n");
    uint8_t j;
    printf("ne_doip_vehicle_identity_resinfo_t eid is ");
    for (j = 0; j < NE_DOIP_EID_SIZE; ++j) {
        printf("%02X", (unsigned char)info->eid[j]);
    }
    printf("\n");
    uint8_t q;
    printf("ne_doip_vehicle_identity_resinfo_t gid is ");
    for (q = 0; q < NE_DOIP_GID_SIZE; ++q) {
        printf("%02X", (unsigned char)info->gid[q]);
    }
    printf("\n");
    printf("ne_doip_vehicle_identity_resinfo_t logical_address is %04X\n", info->logical_address);
}

void ne_uds_clinet_routing_active_callback_func(ne_doip_routing_active_resinfo_t* info)
{
    printf("ne_uds_clinet_routing_active_callback_func is enter...\n");

    printf("ne_doip_routing_active_resinfo_t logical_address is %04X \n", info->entity_logical_address);
    printf("ne_doip_routing_active_resinfo_t routing_active_res_code is %d \n", info->routing_active_res_code);

    char send_data[] = {0x11, 0x22, 0x33, 0x33, 0x22, 0x11};
    // ne_doip_equip_diagnostic(my_active_resinfo->entity_logical_address, NE_DOIP_TA_TYPE_PHYSICAL, send_data, sizeof send_data);
    ne_doip_equip_diagnostic(0x0130, NE_DOIP_TA_TYPE_PHYSICAL, send_data, sizeof send_data);
}

void ne_uds_clinet_entity_status_callback_func(ne_doip_entity_status_info_t* info)
{
    printf("ne_uds_clinet_entity_status_callback_func is enter...\n");
    printf("ne_doip_entity_status_info_t node_type is %d \n", info->node_type);
    printf("ne_doip_entity_status_info_t MCTS is %d \n", info->MCTS);
    printf("ne_doip_entity_status_info_t NCTS is %d \n", info->NCTS);
    printf("ne_doip_entity_status_info_t MDS is %d \n", info->MDS);
}

void ne_uds_clinet_power_mode_callback_func(uint16_t power_mode)
{
    printf("ne_uds_clinet_power_mode_callback_func is enter...\n");
    printf("power_mode is %d \n", power_mode);
}

void ne_uds_clinet_diagnostic_pack_callback_func(uint16_t logical_target_address, uint8_t positive_ack_code)
{
    printf("ne_uds_clinet_diagnostic_pack_callback_func is enter...\n");
}

void ne_uds_clinet_diagnostic_nack_callback_func(uint16_t logical_target_address, uint8_t negative_ack_code)
{
    printf("ne_uds_clinet_diagnostic_nack_callback_func is enter...\n");
}

void ne_uds_clinet_diagnostic_callback_func(uint16_t logical_target_address, unsigned char* data, uint32_t length)
{
    printf("ne_uds_clinet_diagnostic_callback_func is enter...\n");
    printf("equipment logical_target_address is [%04X]\n", logical_target_address);

    printf("recv data is ");
    uint32_t i;
    for (i = 0; i < length; ++i) {
        printf("%02X", (unsigned char)data[i]);
    }
    printf("\n");
}

int main()
{
    /*  UDS server uses the interface of ne_doip_node.h  */
    ne_doip_node_callback_register_t node_callback_register;
    memset(&node_callback_register, 0, sizeof node_callback_register);
    node_callback_register.indcation_cb = ne_uds_server_diag_indication_callback;
    node_callback_register.confirm_cb = ne_uds_server_diag_confirm_callback;
    ne_doip_node_create(DOIP_NODE_1_LOGIC_ADDRESS, NE_DOIP_INSTANCE_TYPE_ENTITY, node_callback_register);

    // If it is attached to the ECU as a gateway, it is additionally registered and the entity type is NE_DOIP_INSTANCE_TYPE_ECU.
    // ne_doip_node_callback_register_t node_callback_register2;
    // memset(&node_callback_register2, 0, sizeof node_callback_register2);
    // node_callback_register2.indcation_cb = ne_uds_server_diag_indication_callback_2;
    // node_callback_register2.confirm_cb = ne_uds_server_diag_confirm_callback_2;
    // ne_doip_node_create(DOIP_NODE_2_LOGIC_ADDRESS, NE_DOIP_INSTANCE_TYPE_ECU, node_callback_register2);
    /*******************************************************/

    /*  UDS Client uses the interface of ne_doip_client.h  */
    ne_doip_equip_callback_register_t equip_callback_register;
    equip_callback_register.vehicle_identity_cb = ne_uds_clinet_vehicle_identity_callback_func;
    equip_callback_register.routing_active_cb = ne_uds_clinet_routing_active_callback_func;
    equip_callback_register.entity_status_cb = ne_uds_clinet_entity_status_callback_func;
    equip_callback_register.power_mode_cb = ne_uds_clinet_power_mode_callback_func;
    equip_callback_register.diag_pack_cb = ne_uds_clinet_diagnostic_pack_callback_func;
    equip_callback_register.diag_nack_cb = ne_uds_clinet_diagnostic_nack_callback_func;
    equip_callback_register.diagnostic_cb = ne_uds_clinet_diagnostic_callback_func;
    ne_doip_equip_create(DOIP_EQUIP_LOGIC_ADDRESS, equip_callback_register);

    /*For the edge gateway control mode, such as the dipper project.
    Routing activation is performed without vehicle discovery, 
    and a diagnostic request is sent after receiving a positive route activation response.*/

    // 1. ne_doip_equip_routing_active(logical_source_address, 0x00, 0, NULL);
    // 2. ne_doip_equip_diagnostic(logical_target_address, NE_DOIP_TA_TYPE_PHYSICAL, data, data_length);

    /*******************************************************/

    sleep(1000000);

    /*  doip node destroy  */
    ne_doip_node_destroy(DOIP_NODE_1_LOGIC_ADDRESS);
    /*****************************/

    /*  doip equip destroy  */
    ne_doip_equip_destroy();
    /*****************************/

    exit(0);
}
