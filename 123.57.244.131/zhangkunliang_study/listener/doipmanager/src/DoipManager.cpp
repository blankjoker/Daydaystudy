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
    ne_doip_regist_logfunc_callback(logoutput);
    ne_doip_server_init(DOIP_CONFIG_PATH);
    /***************for test*******************/
    ne_doip_set_vin_info("IVI88ABCD19800418");
    ne_doip_set_eid_info("180373CB6B33");
    ne_doip_set_gid_info("180373CB6B33");

    activationLineSwitchChange(true);
    ne_doip_request_ip_addr_assignment("eth0");
    powermodeStatusChange(true);
    /***************for test*******************/
}

void DoipManager::doipServerDeInit()
{
    TLOGT("DoipManager::doipServerDeInit is enter.");
    ne_doip_server_deinit();
}

void DoipManager::setVINInfo(const android::String16& vin)
{
    TLOGT("DoipManager::setVINInfo is %s.", vin.string());
    ne_doip_set_vin_info((const char*)vin.string());
}

void DoipManager::setEIDInfo(const android::String16& eid)
{
    TLOGT("DoipManager::setEIDInfo is %s.", eid.string());
    ne_doip_set_eid_info((const char*)eid.string());
}

void DoipManager::setGIDInfo(const android::String16& gid)
{
    TLOGT("DoipManager::setEIDInfo is %s.", gid.string());
    ne_doip_set_gid_info((const char*)gid.string());
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

void DoipManager::requestIPAddressAssignment(const android::String16& ifname)
{
    TLOGT("DoipManager::requestIPAddressAssignment is enter. ifname is %s.", ifname.string());
    ne_doip_request_ip_addr_assignment((const char*)ifname.string());
}

void DoipManager::releaseIPAddressAssignment(const android::String16& ifname)
{
    TLOGT("DoipManager::releaseIPAddressAssignment is enter. ifname is %s.", ifname.string());
    ne_doip_release_ip_addr_assignment((const char*)ifname.string());
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
