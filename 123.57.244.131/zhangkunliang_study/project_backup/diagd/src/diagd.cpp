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

/**
 * @file DTService.h
 * @brief Implement file of class DTService.
 */

#include "diagd/diagd.h"
#include "diagd/diagdLog.h"
#include "ne_doip_comm_def.h"
#include "ne_doip_server.h"

namespace nutshell {

DiagD::DiagD()
{
    DIAGD_DG("DiagD::DiagD");
}

DiagD::~DiagD()
{
    DIAGD_DG("DiagD::~DiagD");
}

bool
DiagD::init()
{
    DIAGD_DG("DiagD::init");
    ne_doip_server_init("/etc/doip/doip_server_config.xml");
    ne_doip_set_vin_info("IVI88ABCD19800418");
    ne_doip_set_eid_info("180373CB6B33");
    ne_doip_set_gid_info("180373CB6B33");
    ne_doip_request_ip_addr_assignment("wm0");
    ne_doip_activation_line_switch_active();
    ne_doip_powermode_status_change(0x01);

    return true;
}

bool
DiagD::start()
{
    DIAGD_DG("DiagD::start");
    return true;
}

bool
DiagD::stop()
{
    DIAGD_DG("DiagD::stop");
    return true;
}

bool
DiagD::deinit()
{
    DIAGD_DG("DiagD::deinit");
    return true;
}

} // end of namespace
/* EOF */