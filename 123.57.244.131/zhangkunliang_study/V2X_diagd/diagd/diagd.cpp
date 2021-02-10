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
#include "servicebase/ServiceDefine.h"
#include "diagd.h"
#include "diagdLog.h"

#include <signal.h>
#include <unistd.h>

namespace nutshell
{

android::sp<DiagD> DiagD::s_instance = NULL;
DiagD* DiagD::instantiate()
{
    if (s_instance == NULL) {
        s_instance = new DiagD;
    }

    return s_instance.get();
}

DiagD::DiagD()
    : ServiceBase(nesat::SRV_NAME_DIAGD)
    , m_doipManager(NULL)
    // , m_diag_listener(NULL)
    // , m_diag_server(NULL)
    // , m_diagd_net_server(NULL)
    // , m_NetEventListener(NULL)
    // , m_DiagDCmdCfmListener(NULL)
{
    DIAGDLOGT("DiagD::DiagD");
}

DiagD::~DiagD()
{
    DIAGDLOGT("DiagD::~DiagD");
}

void DiagD::doInitStart(int reason)
{
    DIAGDLOGT("%s, %d, reason=%d.", __FUNCTION__, __LINE__, reason);

    // These follow comment code is for a short time,when the normal function is needed, these follow code must be uncomment.by zhangkunliang,data:2019/1016
    /*
        bindService(android::String16("ucomdiagserver"), this);
    */

    // bindService(android::String16("networkmanager"), this);
    m_doipManager = DoipManager::instantiate(this);
    m_doipManager->doipServerInit();

    started();
}

void DiagD::doInitSuspend(int action)
{
    DIAGDLOGT("%s, %d, action=%d.", __FUNCTION__, __LINE__, action);

    suspended();
}

void DiagD::doInitAwake(int reason)
{
    DIAGDLOGT("%s, %d, reason=%d.", __FUNCTION__, __LINE__, reason);

    awaked();
}

void DiagD::doStart(int reason)
{
    DIAGDLOGT("%s, %d, reason=%d.", __FUNCTION__, __LINE__, reason);

    m_doipManager->doipServerInit();

    started();
}

void DiagD::doSuspend(int action)
{
    DIAGDLOGT("%s, %d, action=%d.", __FUNCTION__, __LINE__, action);

    m_doipManager->doipServerDeInit();

    suspended();
}

void DiagD::doAwake(int reason)
{
    DIAGDLOGT("%s, %d, reason=%d.", __FUNCTION__, __LINE__, reason);

    awaked();
}

void DiagD::onServiceConnected(android::sp<android::IBinder> binder, android::String16 name)
{
    DIAGDLOGT("%s, %d, %s is connected.", __FUNCTION__, __LINE__, android::String8(name).string());
    // const char* name_ch = android::String8(name).string();
    // if (0 == strcmp(name_ch, "ucomdiagserver")) {
    //     m_diag_server = android::interface_cast<nesat::IUComDiagServer>(binder);
    //     if (m_diag_server != NULL) {
    //         m_diag_listener = new DoipDiagClientListener();
    //         m_diag_server->registerListener(m_diag_listener);
    //         m_diag_server->getVinReq();
    //         m_diag_server->getEIDReq();
    //         m_diag_server->getGIDReq();
    //     }
    // }
    // else if (0 == strcmp(name_ch, "networkmanager")) {
    //     m_diagd_net_server = android::interface_cast<nesat::INetworkManager>(binder);
    //     if (m_diagd_net_server != NULL) {
    //         m_NetEventListener = new DiagDNetEventListener();
    //         m_diagd_net_server->registerObserver(android::String16("diagd_netEvent"), m_NetEventListener);
    //         m_diagd_net_server->getInterfaceConfig(android::String16("vlan3"));
    //         m_diagd_net_server->getInterfaceConfig(android::String16("vlan51"));

    //         m_DiagDCmdCfmListener = new DiagDCmdCfmListener();
    //         m_diagd_net_server->regCommandReply(android::String16("diagd_command"), m_DiagDCmdCfmListener);
    //     }
    // }
}

void DiagD::onServiceDisconnected(android::String16 name)
{
    DIAGDLOGT("%s, %d, %s is disconnected.", __FUNCTION__, __LINE__, android::String8(name).string());
}



// DiagD::DoipDiagClientListener::DoipDiagClientListener()
// {

// }

// DiagD::DoipDiagClientListener::~DoipDiagClientListener()
// {

// }

// android::binder::Status DiagD::DoipDiagClientListener::getVinCfm(const android::String16& vin, int32_t len)
// {
//     DIAGDLOGT("DoipDiagClientListener::getVinCfm is %s.", android::String8(vin).string());
//     ne_doip_set_vin_info(android::String8(vin).string());
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DoipDiagClientListener::getEIDCfm(const android::String16& eid, int32_t len)
// {
//     DIAGDLOGT("DoipDiagClientListener::getEIDCfm is %s.", android::String8(eid).string());
//     ne_doip_set_eid_info(android::String8(eid).string());
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DoipDiagClientListener::getGIDCfm(const android::String16& gid, int32_t len)
// {
//     DIAGDLOGT("DoipDiagClientListener::getGIDCfm is %s.", android::String8(gid).string());
//     ne_doip_set_gid_info(android::String8(gid).string());
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DoipDiagClientListener::activationLineInd(int32_t line)
// {
//     DIAGDLOGT("%s, %d, line=%d", __FUNCTION__, __LINE__, line);
//     if (line) {
//         ne_doip_activation_line_switch_active();
//     }
//     else {
//         ne_doip_activation_line_switch_deactive();
//     }
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DoipDiagClientListener::mcuStateInd(int32_t sts)
// {
//     DIAGDLOGT("%s, %d, sts=%d", __FUNCTION__, __LINE__, sts);
//     if (sts) {
//         ne_doip_powermode_status_change(0x00);
//     }
//     else {
//         ne_doip_powermode_status_change(0x01);
//     }
//     return android::binder::Status::ok();
// }




// DiagD::DiagDNetEventListener::DiagDNetEventListener()
// {

// }

// DiagD::DiagDNetEventListener::~DiagDNetEventListener()
// {

// }

// android::binder::Status DiagD::DiagDNetEventListener::interfaceStatusChanged(const ::android::String16& iface, bool up, const ::android::String16& ip)
// {
//     DIAGDLOGT("interfaceStatusChanged iface = %s, up = %d, ip = %s\n", android::String8(iface).string(), (int)up, android::String8(ip).string());
//     ne_doip_request_ip_addr_assignment(android::String8(iface).string());
//     return android::binder::Status::ok();
// }


// android::binder::Status DiagD::DiagDNetEventListener::interfaceLinkStateChanged(const ::android::String16& iface, bool up)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDNetEventListener::interfaceAdded(const ::android::String16& iface)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDNetEventListener::interfaceRemoved(const ::android::String16& iface)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDNetEventListener::addressUpdated(const ::android::String16& iface, const ::nesat::LinkAddress& address)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDNetEventListener::addressRemoved(const ::android::String16& iface, const ::nesat::LinkAddress& address)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDNetEventListener::limitReached(const ::android::String16& limitName, const ::android::String16& iface)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDNetEventListener::interfaceClassDataActivityChanged(const ::android::String16& label, bool active, int64_t tsNanos)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDNetEventListener::interfaceDnsServerInfo(const ::android::String16& iface, int64_t lifetime, const ::std::vector<::android::String16>& servers)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDNetEventListener::routeUpdated(const ::nesat::RouteInfo& route)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDNetEventListener::routeRemoved(const ::nesat::RouteInfo& route)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDNetEventListener::idleInterfaceInform(const ::std::vector<::android::String16>& iface)
// {
//     return android::binder::Status::ok();
// }


// DiagD::DiagDCmdCfmListener::DiagDCmdCfmListener()
// {

// }

// DiagD::DiagDCmdCfmListener::~DiagDCmdCfmListener()
// {

// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replyGetInterfaceConfig(const ::nesat::InterfaceConfiguration& ifaceCfg)
// {
//     DIAGDLOGT("replyGetInterfaceConfig[%s][%s][%d]\n", ifaceCfg.getIface().string(), (ifaceCfg.getLinkAddress()).string(), ifaceCfg.isActive());
//     if (ifaceCfg.isActive()) {
//         ne_doip_request_ip_addr_assignment(ifaceCfg.getIface().string());
//     }
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replylistInterfaces(const ::std::vector<::android::String16>& ifaceList)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replySetIpForwardingEnabled(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replyGetIpForwardingEnabled(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replyStartInterfaceForwarding(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replyStopInterfaceForwarding(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replyAddIfaceToLocalNetwork(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replyRemoveIfaceToLocalNetwork(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replyAddInterfaceToNetwork(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replyRemoveInterfaceToNetwork(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replyAddRoute(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replyRemoveRoute(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replyRemoveRoutesFrLocalNet(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replySetDefaultNetId(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replyClearDefaultNetId(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replyEnableNat(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replyDisableNat(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replySetBlackListUid(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replyGetIfQuota(int64_t result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replyGetIfQuotaAlert(int64_t result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replySetIfQuota(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replySetIfAlert(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replySetGlobalAlert(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replyRmIfQuota(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replyRmIfAlert(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replyRmGlobalAlert(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::dataConnectConfirm(bool result, int32_t errCode, int32_t apnIndex)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::dataDisconnectConfirm(bool result, int32_t errCode, int32_t apnIndex)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replySetOemRules(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replySetWhiteListUid(bool result)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replyEnableWhiteListPort(bool result, const ::nesat::WhiteListPortConfig& cfg)
// {
//     return android::binder::Status::ok();
// }

// android::binder::Status DiagD::DiagDCmdCfmListener::replyDisableWhiteListPort(bool result, const ::nesat::WhiteListPortConfig& cfg)
// {
//     return android::binder::Status::ok();
// }


}
/* EOF */
