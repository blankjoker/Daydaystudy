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

#define DOIP_EQUIP_LOGIC_ADDRESS 0x0F11

// Callback function for vehicle discovery request
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

// Callback function for routing activation request
void ne_uds_clinet_routing_active_callback_func(ne_doip_routing_active_resinfo_t* info)
{
    printf("ne_uds_clinet_routing_active_callback_func is enter...\n");

    printf("ne_doip_routing_active_resinfo_t logical_address is %04X \n", info->entity_logical_address);
    printf("ne_doip_routing_active_resinfo_t routing_active_res_code is %d \n", info->routing_active_res_code);
}

// Callback function for entity status request
void ne_uds_clinet_entity_status_callback_func(ne_doip_entity_status_info_t* info)
{
    printf("ne_uds_clinet_entity_status_callback_func is enter...\n");
    printf("ne_doip_entity_status_info_t node_type is %d \n", info->node_type);
    printf("ne_doip_entity_status_info_t MCTS is %d \n", info->MCTS);
    printf("ne_doip_entity_status_info_t NCTS is %d \n", info->NCTS);
    printf("ne_doip_entity_status_info_t MDS is %d \n", info->MDS);
}

// Callback function for power mode info request
void ne_uds_clinet_power_mode_callback_func(uint16_t power_mode)
{
    printf("ne_uds_clinet_power_mode_callback_func is enter...\n");
    printf("power_mode is %d \n", power_mode);
}

// Callback function that diagnoses the request's positive response
void ne_uds_clinet_diagnostic_pack_callback_func(uint16_t logical_target_address, uint8_t positive_ack_code)
{
    printf("ne_uds_clinet_diagnostic_pack_callback_func is enter...\n");
}

// Callback function that diagnoses the request's negative response
void ne_uds_clinet_diagnostic_nack_callback_func(uint16_t logical_target_address, uint8_t negative_ack_code)
{
    printf("ne_uds_clinet_diagnostic_nack_callback_func is enter...mack_code[%u]\n", negative_ack_code);
}

// Callback function for diagnostic request
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

    /* For the edge gateway control mode, such as the dipper project.
    Routing activation is performed without vehicle discovery, 
    and a diagnostic request is sent after receiving a positive route activation response. */

    // 1. ne_doip_equip_routing_active(logical_source_address, 0x00, 0, NULL);
    // 2. ne_doip_equip_diagnostic(logical_target_address, NE_DOIP_TA_TYPE_PHYSICAL, data, data_length);

    /*******************************************************/

    sleep(1000000);

    /*  doip equip destroy  */
    ne_doip_equip_destroy();
    /*****************************/

    exit(0);
}