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
#include "ne_doip_server.h"

#define CONFIG_PATH "/system/etc/doip_server_config.xml"


// Set VIN information
void notifyVINInfo(const char *vin)
{
    ne_doip_set_vin_info(vin);
}

// Set EID information
void notifyEIDInfo(const char *eid)
{
    ne_doip_set_eid_info(eid);
}

// Set GID information
void notifyGIDInfo(const char *gid)
{
    ne_doip_set_gid_info(gid);
}

// After the IP is dynamically configured, the daemon receives the notification.
void notifyRequestIPAddressAssignment(const char *ifname)
{
    ne_doip_request_ip_addr_assignment(ifname);
}

// After the IP is invalid or released, the daemon receives the notification.
void notifyReleaseIPAddressAssignment(const char *ifname)
{
    ne_doip_release_ip_addr_assignment(ifname);
}

// Receive notification after OBDII activation line is activated
void notifyActivationLineSwitchChange(uint8_t bActive) /* se bool */
{
    if (bActive) {
        ne_doip_activation_line_switch_active();
    }
    else {
        ne_doip_activation_line_switch_deactive();
    }
}

// Receive notification when the ECU is in a diagnosable state
void notifyPowermodeStatusChange(uint8_t bPowermode) /* use bool */
{
    if (bPowermode) {
        ne_doip_powermode_status_change(0x01); // 0x01: ready
    }
    else {
        ne_doip_powermode_status_change(0x00); // 0x00: not ready
    }
}

// Daemon init
void init()
{
    ne_doip_server_init(CONFIG_PATH);
}

// Daemon deinit
void deinit()
{
    ne_doip_server_deinit();
}

int main()
{
    init();

    sleep(1000000);

    deinit();

    exit(0);
}