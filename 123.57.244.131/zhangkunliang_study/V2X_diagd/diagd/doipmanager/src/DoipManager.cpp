/**
 * Copyright @ 2018 - 2020 Suntec Software(Shanghai) Co., Ltd.
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are NOT permitted except as agreed by
 * Suntec Software(Shanghai) Co., Ltd.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */
#include "binder/IServiceManager.h"
#include "binder/Parcel.h"
#include "servicebase/ServiceBase.h"
#include "DoipManager.h"
#include "DoipManagerLog.h"
#include "diagd.h"
#include "ne_doip_server.h"
#include <signal.h>


void logoutput(const char *text)
{
    // __android_log_write(3, LOG_TAG, text);
    TLOGE("%s", text);
}

namespace nutshell
{

const char* DOIP_CONFIG_PATH = "/system/etc/doip_server_config.xml";
android::sp<DoipManager> DoipManager::s_instance = NULL;

DoipManager* DoipManager::instantiate(DiagD* diagd)
{
    if (s_instance == NULL)  {
        s_instance = new DoipManager(diagd);
    }

    return s_instance.get();
}

void DoipManager::destroy()
{
    if (s_instance != NULL) {
        s_instance = NULL;
    }
}

DoipManager::DoipManager(DiagD* diagd)
    : m_diagd(diagd)
{
    TLOGT("DoipManager::DoipManager");
}

DoipManager::~DoipManager()
{
    TLOGT("DoipManager::~DoipManager");
}

void DoipManager::doipServerInit()
{
    TLOGT("DoipManager::doipServerInit is enter.");
    signal(SIGPIPE, SIG_IGN);
    ne_doip_regist_logfunc_callback(logoutput);
    ne_doip_server_init(DOIP_CONFIG_PATH);
    /***************for test*******************/
    ne_doip_set_vin_info("IVI88ABCD19800418");
    ne_doip_set_eid_info("180373CB6B33");
    ne_doip_set_gid_info("180373CB6B33");

    activationLineSwitchChange(true);
    powermodeStatusChange(true);
    ne_doip_request_ip_addr_assignment("eno1");
    /***************for test*******************/
}

void DoipManager::doipServerDeInit()
{
    TLOGT("DoipManager::doipServerDeInit is enter.");
    ne_doip_server_deinit();
}

void DoipManager::activationLineSwitchChange(bool bActivationFlag)
{
    TLOGT("DoipManager::activationLineSwitchChange to %d.", bActivationFlag);
    if (bActivationFlag) {
        ne_doip_activation_line_switch_active();
    }
    else {
        ne_doip_activation_line_switch_deactive();
    }
}

void DoipManager::powermodeStatusChange(bool powermodeFlag)
{
    TLOGT("DoipManager::powermodeStatusChange to %d.", powermodeFlag);
    if (powermodeFlag) {
        ne_doip_powermode_status_change(0x01);
    }
    else {
        ne_doip_powermode_status_change(0x00);
    }
}

}
/* EOF */
