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

#include "ne_doip_node.h"
#include "ne_doip_comm_def.h"

#define DOIP_NODE_1_LOGIC_ADDRESS 0x0200
#define DOIP_NODE_2_LOGIC_ADDRESS 0x0210

// Callback function that accepts test device diagnostic requests
void ne_uds_server_diag_indication_callback(ne_doip_diag_data_indication_t* diag_data_indication)
{
    printf("ne_uds_server_diag_indication_callback is enter...\n");
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


// Confirmation function callback after UDS server sends diagnostic response
void ne_uds_server_diag_confirm_callback(ne_doip_diag_data_confirm_t *diag_data_confirm)
{
    printf("ne_uds_server_diag_confirm_callback is enter...\n");
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
    printf("ne_uds_server_send_data is enter...\n");

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

    ne_doip_node_diag_data_request(diag_data_request);
    free(diag_data_request);
}


// Optional registration callback function that requires user confirmation when the route is activated
void ne_uds_server_user_conf_callback(uint16_t logical_source_address, uint16_t logical_target_address)
{
    printf("ne_uds_server_user_conf_callback is enter...\n");
    // Passed to the upper application layer to confirm whether route activation can pass 
    // to ensure that the diagnostic phase can be entered.


    /* If the upper application layer is ready, call the following interface to send the confirmation result. */
    /* This case is confirmed by the user. */
    ne_doip_node_send_user_conf_result(logical_target_address, logical_source_address, NE_DOIP_USER_CON_RESLUT_PASS);
    /* This case is No need to confirm by the user. */
    // ne_doip_node_send_user_conf_result(logical_target_address, logical_source_address, NE_DOIP_USER_CON_RESLUT_NO_CON);
    /* This case is reject by the user. */
    // ne_doip_node_send_user_conf_result(logical_target_address, logical_source_address, NE_DOIP_USER_CON_RESLUT_REJECT);
}

int main()
{
    /*  UDS server uses the interface of ne_doip_node.h  */
    ne_doip_node_callback_register_t node_callback_register;
    memset(&node_callback_register, 0, sizeof node_callback_register);
    node_callback_register.indication_cb = ne_uds_server_diag_indication_callback;
    node_callback_register.confirm_cb = ne_uds_server_diag_confirm_callback;
    ne_doip_node_create(DOIP_NODE_1_LOGIC_ADDRESS, NE_DOIP_INSTANCE_TYPE_ENTITY, node_callback_register);

    // If it is attached to the ECU as a gateway, it is additionally registered and the entity type is NE_DOIP_INSTANCE_TYPE_ECU.
    // ne_doip_node_callback_register_t node_callback_register2;
    // memset(&node_callback_register2, 0, sizeof node_callback_register2);
    // node_callback_register2.indication_cb = ne_uds_server_diag_indication_callback_2;
    // node_callback_register2.confirm_cb = ne_uds_server_diag_confirm_callback_2;
    // ne_doip_node_create(DOIP_NODE_2_LOGIC_ADDRESS, NE_DOIP_INSTANCE_TYPE_ECU, node_callback_register2);
    /*******************************************************/

    sleep(1000000);

    /*  doip node destroy  */
    ne_doip_node_destroy(DOIP_NODE_1_LOGIC_ADDRESS);
    /*****************************/

    exit(0);
}