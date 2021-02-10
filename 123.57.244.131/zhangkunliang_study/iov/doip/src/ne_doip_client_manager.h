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
 * @file ne_doip_test_equip_manager.h
 * @brief Protocol parsing module
 */

#ifndef NE_DOIP_TEST_EQUIP_MANAGER_H
#define NE_DOIP_TEST_EQUIP_MANAGER_H

#include "ne_doip_def.h"

#define NE_DOIP_ACTIVATION_TYPE_LENGTH 1
#define NE_DOIP_RESERVED_LENGTH        4
#define NE_DOIP_OEM_SPECIFIC_LENGTH    4


ne_doip_result_t ne_doip_pack_test_equip_regist(ne_doip_connection_t *conn,
                                                uint16_t logical_source_address);
ne_doip_result_t ne_doip_pack_vehicle_identify(ne_doip_connection_t *conn);
ne_doip_result_t ne_doip_pack_vehicle_identify_eid(ne_doip_connection_t *conn, char* eid);
ne_doip_result_t ne_doip_pack_vehicle_identify_vin(ne_doip_connection_t *conn, char* vin);
ne_doip_result_t ne_doip_pack_routing_active(ne_doip_connection_t *conn, uint16_t logical_source_address,
                                             uint8_t activation_type, uint32_t oem_specific_use, char* eid);
ne_doip_result_t ne_doip_pack_alive_check_response(ne_doip_connection_t *conn,
                                                   uint16_t logical_target_address);
ne_doip_result_t ne_doip_pack_entity_status(ne_doip_connection_t *conn, char* eid);
ne_doip_result_t ne_doip_pack_power_mode(ne_doip_connection_t *conn, char* eid);
ne_doip_result_t ne_doip_pack_diagnositc_req(ne_doip_connection_t *conn,
                                             uint16_t logical_source_address,
                                             uint16_t logical_target_address,
                                             ne_doip_ta_type_t ta_type,
                                             char* data,
                                             uint32_t length);

void ne_doip_equip_unpack(ne_doip_connection_t *conn);


#endif /* NE_DOIP_TEST_EQUIP_MANAGER_H */
/* EOF */