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
#include <unistd.h>
#include <signal.h>

#include "ne_doip_server.h"

#define CONFIG_PATH "/system/etc/doip_server_config.xml"
#define STR_VIN_INFO "IVI88ABCD19800418"
#define STR_EID_INFO "180373CB6B6F"
#define STR_GID_INFO "180373CB6B6F"
#define STR_IFNAME "eth0"

void
signal_exit_handler(int sig)
{
    ne_doip_server_deinit();
    exit(0);
}

int main()
{
    signal(SIGTERM, signal_exit_handler);
    signal(SIGINT, signal_exit_handler);

    ne_doip_server_init(CONFIG_PATH);
    ne_doip_set_vin_info(STR_VIN_INFO);
    ne_doip_set_eid_info(STR_EID_INFO);
    ne_doip_set_gid_info(STR_GID_INFO);

    sleep(1);
    ne_doip_activation_line_switch_active();
    sleep(1);
    ne_doip_request_ip_addr_assignment(STR_IFNAME);
    sleep(1);
    ne_doip_powermode_status_change(0x01);

    sleep(100000);

    ne_doip_server_deinit();

    exit(0);
}