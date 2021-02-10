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
 * @file ne_doip_server.h
 * @brief Server interface
 */

#ifndef NE_DOIP_SERVER_H
#define NE_DOIP_SERVER_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "ne_doip_comm_def.h"

/**
* @brief Initialize the doip server.
*
* @param [in] config_path : Path to the doip stack configuration file.
*
* @return The function execution returns NE_DOIP_RESULT_OK successfully.
*         If an internal error returns another code, see the file ne_doip_comm_def.h for details.
*
* @attention Synchronous I/F.
*/
ne_doip_result_t ne_doip_server_init(const char* config_path);

/**
* @brief Deinitialize the doip server.
*
* @return The function execution returns NE_DOIP_RESULT_OK successfully.
*         If an internal error returns another code, see the file ne_doip_comm_def.h for details.
*
* @attention Synchronous I/F.
*/
ne_doip_result_t ne_doip_server_deinit(void);

/**
* @brief Set doip vin information
*
* @return The function execution returns NE_DOIP_RESULT_OK successfully.
*         If an internal error returns another code, see the file ne_doip_comm_def.h for details.
*
* @attention Synchronous I/F.
*/
ne_doip_result_t ne_doip_set_vin_info(const char *vin);

/**
* @brief Set doip eid information
*
* @return The function execution returns NE_DOIP_RESULT_OK successfully.
*         If an internal error returns another code, see the file ne_doip_comm_def.h for details.
*
* @attention Synchronous I/F.
*/
ne_doip_result_t ne_doip_set_eid_info(const char *eid);

/**
* @brief Set doip gid information
*
* @return The function execution returns NE_DOIP_RESULT_OK successfully.
*         If an internal error returns another code, see the file ne_doip_comm_def.h for details.
*
* @attention Synchronous I/F.
*/
ne_doip_result_t ne_doip_set_gid_info(const char *gid);

/**
* @brief Activation line becomes active, the system calls this interface to notify the DoIP stack.
*        If there is no activation line connection, such as an OTA module, you need to call this interface to activate the doip stack.
*
* @return The function execution returns NE_DOIP_RESULT_OK successfully.
*         If an internal error returns another code, see the file ne_doip_comm_def.h for details.
*
* @attention Synchronous I/F.
*/
ne_doip_result_t ne_doip_activation_line_switch_active(void);

/**
* @brief Activation line becomes deactive, the system calls this interface to notify the DoIP stack.
*        If there is no activation line connection, such as the OTA module, if you need to release all sockets, call this interface to deactive doip stack.
*
* @return The function execution returns NE_DOIP_RESULT_OK successfully.
*         If an internal error returns another code, see the file ne_doip_comm_def.h for details.
*
* @attention Synchronous I/F.
*/
ne_doip_result_t ne_doip_activation_line_switch_deactive(void);

/**
* @brief When the valid IP address has been allocated, the system calls this interface to notify the DoIP stack.
*
* @param [in] if_name : If_name when IP is configured.
*
* @return The function execution returns NE_DOIP_RESULT_OK successfully.
*         If an internal error returns another code, see the file ne_doip_comm_def.h for details.
*
* @attention Synchronous I/F.
*/
ne_doip_result_t ne_doip_request_ip_addr_assignment(const char* if_name);

/**
* @brief When the IP address discards or invalidates its current IP address, the system calls this interface to notify the DoIP stack.
*
* @param [in] if_name : If_name when IP is released or invalid.
*
* @return The function execution returns NE_DOIP_RESULT_OK successfully.
*         If an internal error returns another code, see the file ne_doip_comm_def.h for details.
*
* @attention Synchronous I/F.
*/
ne_doip_result_t ne_doip_release_ip_addr_assignment(const char* if_name);

/**
* @brief update power mode status.
*
* @param [in] power_mode_status : [0x00: not ready; 0x01: ready; 0x02: not supported].
*
* @return The function execution returns NE_DOIP_RESULT_OK successfully.
*         If an internal error returns another code, see the file ne_doip_comm_def.h for details.
*
* @attention Synchronous I/F.
*/
ne_doip_result_t ne_doip_powermode_status_change(uint32_t power_mode_status);

/**
* @brief Register Print Log Callback Function
*
* @param [in] logfunc : Log output function of the daemon.
*
* @return The function execution returns NE_DOIP_RESULT_OK successfully.
*         If an internal error returns another code, see the file ne_doip_comm_def.h for details.
*
* @attention Synchronous I/F.
*/
ne_doip_result_t ne_doip_regist_logfunc_callback(ne_doip_logfunc_callback logfunc);

/**
* @brief Register Diag Trace Log Callback Function
*
* @param [in] logfunc : diag trace Log output function of the daemon.
*
* @return The function execution returns NE_DOIP_RESULT_OK successfully.
*         If an internal error returns another code, see the file ne_doip_comm_def.h for details.
*
* @attention Synchronous I/F.
*/
ne_doip_result_t ne_doip_regist_doip_server_dtlogfunc_callback(ne_doip_dtlogfunc_callback server_dtlogfunc);

/**
* @brief [dipper costom]Register a callback that accepts notification of the first route activation success response
*
* @param [in] route_active_res_func : diagd registered callback function for receiving route activation response notifications.
*
* @return The function execution returns NE_DOIP_RESULT_OK successfully.
*         If an internal error returns another code, see the file ne_doip_comm_def.h for details.
*
* @attention Synchronous I/F.
*/
ne_doip_result_t ne_doip_regist_ra_res_callback(ne_doip_routing_activation_res_callback route_active_res_func);

/**
* @brief [dipper costom]Register a callback function that accepts notification of all TCP connection disconnections
*
* @param [in] tcp_dis_res_func : diagd registered callback function, used to accept notification of all TCP connection disconnection.
*
* @return The function execution returns NE_DOIP_RESULT_OK successfully.
*         If an internal error returns another code, see the file ne_doip_comm_def.h for details.
*
* @attention Synchronous I/F.
*/
ne_doip_result_t ne_doip_regist_all_tcp_disconnect_callback(ne_doip_all_tcp_disconnect_res_callback tcp_dis_res_func);

#ifdef  __cplusplus
}
#endif

#endif /* NE_DOIP_SERVER_H */
/* EOF */
